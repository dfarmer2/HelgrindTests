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
#include "locked_vs_unlocked1.h"
#include "locked_vs_unlocked2.h"
#include "locked_vs_unlocked3.h"
#include "pth_destroy_cond.h"
#include "tc01_simple_race.h"
#include "tc02_simple_tls.h"
#include "tc05_simple_race.h"
#include "tc06_two_races.h"
#include "tc16_byterace.h"
#include "tc21_pthonce.h"
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
 * This test has a join before the main thread changes the shared memory so does
 * not actually have a race.
 */
TEST(NoRaceTest, tc02_simple_tls) {
   ASSERT_EQ(3, tc02_simple_tls::tc02_simple_tls());
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

/**
 * This is a race where the end result is the memory in question is being set to
 * a constant. That fact will mean that regardless of what happens it should
 * return 1.
 */
TEST(lockedUnlockedTest, lockedVsUnlocked1) {
   ASSERT_EQ(1, locked_vs_unlocked1::locked_vs_unlocked1());
}

/**
 * This is a race where the end result is the memory in question is being set to
 * a constant. That fact will mean that regardless of what happens it should
 * return 1.
 */
TEST(lockedUnlockedTest, lockedVsUnlocked2) {
   ASSERT_EQ(1, locked_vs_unlocked2::locked_vs_unlocked2());
}

/**
 * This is a race where the end result is the memory in question is being set to
 * a constant. That fact will mean that regardless of what happens it should
 * return 1.
 */
TEST(lockedUnlockedTest, lockedVsUnlocked3) {
   ASSERT_EQ(1, locked_vs_unlocked3::locked_vs_unlocked3());
}

/**
 * This is a race where the end result is the memory in question is being set to
 * a constant. That fact will mean that regardless of what happens it should
 * return 1.
 */
TEST(pthDestroyTest, pthDestroyCond) {
   ASSERT_EQ(1, pth_destroy_cond::pth_destroy_cond());
}

/**
 * This test should always return 2, but could possible return 1.
 */
TEST(tcRaceTest, tc01SimpleRace) {
   ASSERT_EQ(2, tc01_simple_race::tc01_simple_race());
}

/**
 * This test should return 2, but may not depending on when a join happens.
 */
TEST(tcRaceTest, tc05SimpleRace) {
   ASSERT_EQ(2, tc05_simple_race::tc05_simple_race());
}

/**
 * This test should return 2, but may not depending on when a join happens.
 */
TEST(tcRaceTest, tc06TwoRaces) {
   ASSERT_EQ(2, tc06_two_races::tc06_two_races());
}

/**
 * This test should return 2, but may not depending on when a join happens.
 */
TEST(tcRaceTest, tc16ByteRace) {
   ASSERT_EQ(2, tc16_byterace::tc16_byterace());
}

/**
 * This test should return 2, but may not depending on when a join happens.
 */
TEST(tcRaceTest, tc21PthOnce) {
   ASSERT_EQ(2, tc21_pthonce::tc21_pthonce());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

