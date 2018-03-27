#include <vector>

#include "gtest/gtest.h"

#include "utilities/zip.hpp"

#include "kernels/basic_kernels.hpp"
#include "kernels/detail.hpp"

namespace {

TEST(SimpleUnpackTest, ScalarProductUnpackTest) {
    std::vector<int> v1{ 1, 2, 3 };
    std::vector<int> v2{ 3, 4, 3, 9, 10 };

    projectT1::kernels::KernScalarProduct<int> kern;

    auto a = projectT1::utilities::tuple::make_zip(v1, v2);
    decltype(kern)::return_type ret{};
    projectT1::kernels::detail::unpack(kern, *a.begin(), ret);
    EXPECT_EQ(ret, 3);

}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}