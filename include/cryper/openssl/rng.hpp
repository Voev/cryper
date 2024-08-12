#pragma once
#include <cryper/rng.hpp>
#include <openssl/rand.h>

namespace cryper::openssl
{

class Rng final : public cryper::Rng
{
public:
    Rng() = default;

    ~Rng() = default;

    void seed(const uint8_t* entropy, const size_t entropySize) override
    {
        RAND_seed(entropy, entropySize < INT_MAX ? static_cast<int>(entropySize)
                                                 : INT_MAX);
    }

    bool generate(uint8_t* random, const size_t randomSize) override
    {
        return 0 < RAND_bytes(random, randomSize < INT_MAX
                                          ? static_cast<int>(randomSize)
                                          : INT_MAX);
    }
};

} // namespace cryper::openssl
