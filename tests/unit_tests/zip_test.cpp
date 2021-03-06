#include <vector>

#include "gtest/gtest.h"

#include "utilities/zip.hpp"
#include "utilities/tuple_utilities.hpp"

namespace {

TEST(IteratorTest, DereferenceAndIncrementTest) {
    std::vector<int> v1{ 1, 2, 3 };
    std::vector<int> v2{ 3, 4, 3, 9, 10 };

    auto a = projectT1::utilities::tuple::make_zip(v1, v2);
    auto it = a.begin();

    EXPECT_EQ(std::get<0>(*a.begin()), 1);
    EXPECT_EQ(std::get<0>(*a.begin()++), 1);
    EXPECT_EQ(std::get<0>(*++a.begin()), 2);
    EXPECT_EQ(std::get<1>(*++a.begin()), 4);
}

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}