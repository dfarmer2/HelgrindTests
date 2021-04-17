/**
 * This is the Google test suite used to run all of the helgrind examples as C++
 * unit tests.
 */
 
#include "bar_trivial.h"
#include <gtest/gtest.h>

/**
 * This is a simple test that checks against helgrind returning a false
 * positive. It should always return 2 because there is no data race.
 */
TEST(SquareRootTest, PositiveNos) {
    ASSERT_EQ(2, bar_trivial::bar_trivial());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

