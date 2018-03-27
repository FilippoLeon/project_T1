#include <benchmark/benchmark.h>

#include <vector>
#include <iostream>

#include "kernels/apply.hpp"
#include "kernels/basic_kernels.hpp"

//static void test01(benchmark::State& state) {
int main() {
    //std::vector<int> v1{1, 2, 3};
    //std::vector<int> v2{3, 2, 4};

    std::vector<int> v1{ 1, 2, 3 };
    std::vector<double> v2{ 3, 2, 4, 5, 7, 8 };

    projectT1::kernels::apply_kern<projectT1::kernels::KernScalarProduct<int>>(v1, v2);

    std::cin.get();
}
//
//}
//BENCHMARK(test01);


//BENCHMARK_MAIN();