/**
 * This is the Google test suite used to run all of the helgrind examples as C++
 * unit tests.
 */
 
#include "bar_trivial.h"
#include "hg01_all_ok.h"
#include "hg03_inherit.h"
#include "hg04_race.h"
#include "hg05_race2.h"
#include "hg06_readshared.h"
#include <gtest/gtest.h>

/**
 * This is a simple test that checks against helgrind returning a false
 * positive. It should always return 2 because there is no data race.
 */
TEST(NoRaceTest, BarTrivial) {
    ASSERT_EQ(2, bar_trivial::bar_trivial());
}

/**
 * This is another baseline test which can be used to test for false positives.
 * It will actually create a C string and then call free() on it. If the threads
 * are not properly synchronized, it will cause a failure.
 */
TEST(NoRaceTest, hg01AllOkay) {
    ASSERT_FALSE(hg01_all_ok::hg01_all_ok());
}

/**
 * Since the shared variable is only read, anything that is flagged is a false
 * positive.
 */
TEST(NoRaceTest, hg06ReadShared) {
   ASSERT_EQ(22, hg06_readshared::hg06_readshared());
}

/**
 * This test shows threads controlled by several sleeps that make the
 * probability of inconsistent results unlikely. This test will almost always
 * fail as the timing will return a number of 209.
 */
TEST(hgRaceTest, hg03Inherit) {
   ASSERT_EQ(627, hg03_inherit::hg03_inherit());
}

/**
 * This is another race which occurs but will not show any discernable output
 * difference as both threads join before returning, but do have a happens
 * before relationship.
 */
TEST(hgRaceTest, hg04Race) {
   ASSERT_EQ(2, hg04_race::hg04_race());
}

/**
 * This is a race where both joins will happen before exiting the main function
 * so it will be hard to detect.
 */
TEST(hgRaceTest, hg05Race2) {
   ASSERT_EQ(2, hg05_race2::hg05_race2());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

