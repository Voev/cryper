#pragma once
#include <cryper/hash.hpp>
#include <cryper/openssl/types.hpp>

namespace cryper::openssl
{

class Hash : public cryper::Hash
{
public:
    Hash()
        : ctx_(EVP_MD_CTX_new())
    {
        if (!ctx_.get())
            throw std::bad_alloc();
    }

    ~Hash() = default;

    bool doInit() override
    {
        if (!cryper::Hash::hashInit())
        {
            return false;
        }

        if (!EVP_DigestInit_ex(ctx_.get(), getAlg(), nullptr))
        {
            Hash::checkFinal();
            return false;
        }

        return true;
    }

    bool doUpdate(const std::vector<uint8_t>& data) override
    {
        if (!cryper::Hash::checkUpdate())
        {
            EVP_MD_CTX_reset(ctx_.get());
            return false;
        }

        if (data.empty())
        {
            return true;
        }

        if (!EVP_DigestUpdate(ctx_.get(), data.data(), data.size()))
        {
            EVP_MD_CTX_reset(ctx_.get());
            Hash::checkFinal();
            return false;
        }

        return true;
    }

    bool doFinal(std::vector<uint8_t>& hash) override
    {
        if (!cryper::Hash::checkFinal())
        {
            EVP_MD_CTX_reset(ctx_.get());
            return false;
        }

        hash.resize(EVP_MD_size(getAlg()));
        unsigned int outLen = hash.size();

        if (!EVP_DigestFinal_ex(ctx_.get(), hash.data(), &outLen))
        {
            EVP_MD_CTX_reset(ctx_.get());
            ctx_ = nullptr;
            return false;
        }

        hash.resize(outLen);
        EVP_MD_CTX_reset(ctx_.get());

        return true;
    }

    virtual EVP_MD* getAlg() const = 0;

private:
    EvpMdCtxPtr ctx_;
};

} // namespace cryper::openssl
