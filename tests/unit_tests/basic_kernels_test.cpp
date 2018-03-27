#include <vector>

#include "gtest/gtest.h"

#include "utilities/zip.hpp"
#include "utilities/tuple_utilities.hpp"

#include "kernels/basic_kernels.hpp"
#include "kernels/detail.hpp"

namespace {

TEST(SimpleKernTest, ScalarProductKernTest) {
    std::vector<int> v1{ 1, 2, 3 };
    std::vector<int> v2{ 3, 4, 3, 9, 10 };

    projectT1::kernels::KernScalarProduct<int> kern;
    decltype(kern)::return_type ret{};

    for (auto&& a : projectT1::utilities::tuple::make_zip(v1, v2)) {
        projectT1::kernels::detail::unpack(kern, a, ret);
    }

    EXPECT_EQ(ret, 20);
}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}