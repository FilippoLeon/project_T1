#include <benchmark/benchmark.h>

#include <vector>
#include <iostream>

#include "kernels/apply.hpp"
#include "kernels/basic_kernels.hpp"

static void scalar_product_benchmark(benchmark::State& state) {
    std::vector<int> v1(state.range(0));
    std::vector<int> v2(state.range(0));
    for (auto _ : state) {
        benchmark::DoNotOptimize(projectT1::kernels::apply_kern<projectT1::kernels::KernScalarProduct<int>>(v1, v2));
    }
    state.SetComplexityN(state.range(0));
    // state.SetBytesProcessed(int64_t(state.iterations()) *
    //                        int64_t(state.range(0)));
}
BENCHMARK(scalar_product_benchmark)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(8 << 10)->Complexity(benchmark::oN);

BENCHMARK_MAIN();