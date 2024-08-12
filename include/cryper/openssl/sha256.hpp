#pragma once
#include <cryper/openssl/hash.hpp>

namespace cryper::openssl
{

class Sha256 final : public Hash
{
public:
    Sha256()
        : alg_(const_cast<EVP_MD*>(EVP_get_digestbyname("sha256")))
    {
    }

    ~Sha256() = default;

    EVP_MD* getAlg() const override
    {
        return alg_;
    }

private:
    EVP_MD* alg_;
};

} // namespace cryper::openssl