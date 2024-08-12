#include <memory>
#include <cryper/hash.hpp>
#include <cryper/rng.hpp>
#include <benchmark/benchmark.h>

#include <cryper/openssl/rng.hpp>
#include <cryper/openssl/sha256.hpp>

namespace cryper
{

template<class RngType, class HashType>
void HashBenchmark(benchmark::State& state)
{
    std::unique_ptr<Rng> rng = std::make_unique<RngType>();
    std::vector<uint8_t> data;

    data.resize(state.range(0));
    rng->generate(data);

    for (auto _ : state)
    {
        std::vector<uint8_t> result;
        std::unique_ptr<Hash> hash = std::make_unique<HashType>();

        if (!hash->doInit() || !hash->doUpdate(data) ||
            !hash->doFinal(result))
        {
            state.SkipWithError("hash error");
        }
    }
}

BENCHMARK(HashBenchmark<openssl::Rng, openssl::Sha256>)->Range(1, 256)->ThreadRange(1, 16);

} // namespace cryper
