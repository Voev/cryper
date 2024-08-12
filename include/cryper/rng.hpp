#pragma once
#include <cstdint>
#include <cstddef>
#include <vector>
#include <cryper/utils/noncopyable.hpp>

namespace cryper
{

class Rng : public utils::NonCopyable
{
public:
    Rng() = default;

    virtual ~Rng() = default;

    virtual void seed(const uint8_t* entropy, const size_t entropySize) = 0;

    virtual bool generate(uint8_t* random, const size_t randomSize) = 0;

    virtual void seed(const std::vector<uint8_t>& entropy)
    {
        seed(entropy.data(), entropy.size());
    }

    virtual bool generate(std::vector<uint8_t>& data)
    {
        return generate(data.data(), data.size());
    }
};

} // namespace cryper
