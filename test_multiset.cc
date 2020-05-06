//
// Karl Goeltner
// 917006087
// ECS 36C - 05/04/2020
//
// test_multiset.cc - Unit tester for multiset.h
//

#include <gtest/gtest.h>
#include "multiset.h"

// 1) Check an empty Multiset & exception
TEST(Multiset, Empty) {
  Multiset<int> mset;

  // Should be fully empty
  EXPECT_EQ(mset.Empty(), true);
  EXPECT_EQ(mset.Size(), 0);
  EXPECT_THROW(mset.Count(42), std::exception);
}

// 2) Check Empty, Size, Min, Max, Count after 3 insertions
TEST(Multiset, OneKey) {
  Multiset<int> mset;

  // Test some insertion
  mset.Insert(23);
  mset.Insert(42);
  mset.Insert(42);
  EXPECT_EQ(mset.Empty(), false);
  EXPECT_EQ(mset.Size(), 3);
  EXPECT_EQ(mset.Min(), 23);
  EXPECT_EQ(mset.Max(), 42);
  EXPECT_EQ(mset.Count(42), 2);
}

// 3) Check Floor & Ceil after insertions
TEST(Multiset, FloorCeil) {
  Multiset<int> mset;

  // Test some insertion
  mset.Insert(2);
  mset.Insert(7);
  mset.Insert(5);
  mset.Insert(2);
  mset.Insert(6);
  mset.Insert(9);
  mset.Insert(5);
  mset.Insert(11);
  mset.Insert(4);

  // Confirm size
  EXPECT_EQ(mset.Size(), 9);

  // Check Floor of several values
  EXPECT_EQ(mset.Floor(3), 2);
  EXPECT_EQ(mset.Floor(9), 9);
  EXPECT_EQ(mset.Floor(10), 9);
  EXPECT_EQ(mset.Floor(100), 11);
  EXPECT_THROW(mset.Floor(1), std::exception);

  // Check Ceil of several values
  EXPECT_EQ(mset.Ceil(3), 4);
  EXPECT_EQ(mset.Ceil(9), 9);
  EXPECT_EQ(mset.Ceil(-100), 2);
  EXPECT_THROW(mset.Ceil(100), std::exception);
}

// 4) Check Floor & Ceil after insertions & removals
TEST(Multiset, FloorCeilRemoval) {
  Multiset<int> mset;

  // Test some insertion
  mset.Insert(52);
  mset.Insert(41);
  mset.Insert(41);
  mset.Insert(55);
  mset.Insert(28);
  mset.Insert(44);
  mset.Insert(65);
  mset.Insert(17);
  mset.Insert(17);
  mset.Insert(32);
  mset.Insert(43);
  mset.Insert(46);
  mset.Insert(46);
  mset.Insert(62);
  mset.Insert(77);

  // Confirm final size
  EXPECT_EQ(mset.Size(), 15);
  EXPECT_EQ(mset.Empty(), false);

  // Check Floor of several values
  EXPECT_EQ(mset.Floor(18), 17);
  EXPECT_EQ(mset.Floor(60), 55);
  EXPECT_EQ(mset.Floor(20), 17);
  EXPECT_EQ(mset.Floor(1000), 77);
  EXPECT_THROW(mset.Floor(10), std::exception);

  // Check Ceil of several values
  EXPECT_EQ(mset.Ceil(41), 41);
  EXPECT_EQ(mset.Ceil(25), 28);
  EXPECT_EQ(mset.Ceil(60), 62);
  EXPECT_EQ(mset.Ceil(-1000), 17);
  EXPECT_THROW(mset.Ceil(1000), std::exception);

  // Remove some values
  mset.Remove(41);
  mset.Remove(65);
  mset.Remove(17);
  mset.Remove(17);
  mset.Remove(32);
  mset.Remove(44);
  mset.Remove(55);

  // Check Floor of several values
  EXPECT_EQ(mset.Floor(29), 28);
  EXPECT_EQ(mset.Floor(60), 52);
  EXPECT_EQ(mset.Floor(70), 62);
  EXPECT_EQ(mset.Floor(1000), 77);
  EXPECT_THROW(mset.Floor(16), std::exception);

  // Check Ceil of several values
  EXPECT_EQ(mset.Ceil(41), 41);
  EXPECT_EQ(mset.Ceil(30), 41);
  EXPECT_EQ(mset.Ceil(65), 77);
  EXPECT_EQ(mset.Ceil(-1000), 28);
  EXPECT_THROW(mset.Ceil(1000), std::exception);
}

// 5) Check Remove & Contains after insertions
TEST(Multiset, RemoveContains) {
  Multiset<int> mset;

  // Test some insertion
  mset.Insert(29);
  mset.Insert(25);
  mset.Insert(45);
  mset.Insert(21);
  mset.Insert(26);
  mset.Insert(50);
  mset.Insert(79);
  mset.Insert(27);

  // Confirm size
  EXPECT_EQ(mset.Size(), 8);

  // Check Removal of several values
  EXPECT_EQ(mset.Contains(25), true);
  mset.Remove(25);
  EXPECT_EQ(mset.Contains(25), false);

  EXPECT_EQ(mset.Contains(79), true);
  mset.Remove(79);
  EXPECT_EQ(mset.Contains(79), false);

  EXPECT_EQ(mset.Contains(29), true);
  mset.Remove(29);
  EXPECT_EQ(mset.Contains(29), false);

  EXPECT_THROW(mset.Remove(1), std::exception);
}

// 6) Check Max, Min, Contains after insertions & removals
TEST(Multiset, MaxMin) {
  Multiset<int> mset;

  // Test some insertion
  mset.Insert(58);
  mset.Insert(44);
  mset.Insert(61);
  mset.Insert(42);
  mset.Insert(48);
  mset.Insert(60);
  mset.Insert(77);
  mset.Insert(75);
  mset.Insert(80);
  mset.Insert(47);
  mset.Insert(50);
  mset.Insert(42);

  // Confirm size
  EXPECT_EQ(mset.Size(), 12);

  // Check Max & Min of several values
  EXPECT_EQ(mset.Max(), 80);
  EXPECT_EQ(mset.Min(), 42);

  mset.Remove(80);
  mset.Remove(42);
  EXPECT_EQ(mset.Contains(80), false);
  EXPECT_EQ(mset.Contains(42), true);

  EXPECT_EQ(mset.Max(), 77);
  EXPECT_EQ(mset.Min(), 42);

  mset.Remove(77);
  mset.Remove(42);
  EXPECT_EQ(mset.Contains(77), false);
  EXPECT_EQ(mset.Contains(42), false);

  EXPECT_EQ(mset.Max(), 75);
  EXPECT_EQ(mset.Min(), 44);

  mset.Remove(75);
  mset.Remove(44);
  EXPECT_EQ(mset.Contains(75), false);
  EXPECT_EQ(mset.Contains(44), false);

  EXPECT_EQ(mset.Max(), 61);
  EXPECT_EQ(mset.Min(), 47);

  mset.Remove(61);
  mset.Remove(47);
  EXPECT_EQ(mset.Contains(61), false);
  EXPECT_EQ(mset.Contains(47), false);

  mset.Remove(48);
  mset.Remove(50);
  mset.Remove(60);

  // Remove all but the last element
  EXPECT_EQ(mset.Size(), 1);

  EXPECT_EQ(mset.Max(), 58);
  EXPECT_EQ(mset.Min(), 58);
  mset.Remove(58);

  EXPECT_EQ(mset.Empty(), true);

  // Check that an empty multiset throw errors
  EXPECT_THROW(mset.Max(), std::exception);
  EXPECT_THROW(mset.Min(), std::exception);
}

// 7) Check Remove, Count, Floor, Ceil, Max, Min errors
TEST(Multiset, ErrorCheck) {
  Multiset<int> mset;

  // Test some insertion
  mset.Insert(58);
  mset.Insert(44);
  mset.Insert(61);

  // Confirm size
  EXPECT_EQ(mset.Size(), 3);

  // Check Max & Min
  EXPECT_EQ(mset.Max(), 61);
  EXPECT_EQ(mset.Min(), 44);

  // Check Floor & Ceil Errors
  EXPECT_THROW(mset.Floor(40), std::exception);
  EXPECT_THROW(mset.Ceil(100), std::exception);

  // Remove all values
  mset.Remove(58);
  mset.Remove(44);
  mset.Remove(61);

  // Check that an empty multiset throw errors
  EXPECT_THROW(mset.Remove(44), std::exception);
  EXPECT_THROW(mset.Count(58), std::exception);
  EXPECT_THROW(mset.Floor(100), std::exception);
  EXPECT_THROW(mset.Ceil(0), std::exception);
  EXPECT_THROW(mset.Max(), std::exception);
  EXPECT_THROW(mset.Min(), std::exception);
}

// 8) Check Count after insertions & removals
TEST(Multiset, MultipleCount) {
  Multiset<int> mset;

  // Test duplicate insertion
  for (int i = 0; i < 5; i++)
    mset.Insert(50);

  for (int i = 0; i < 4; i++)
    mset.Insert(40);

  for (int i = 0; i < 3; i++)
    mset.Insert(30);

  for (int i = 0; i < 2; i++)
    mset.Insert(20);

  for (int i = 0; i < 1; i++)
    mset.Insert(10);

  // Confirm size
  EXPECT_EQ(mset.Size(), 15);

  // Check initial count
  EXPECT_EQ(mset.Count(50), 5);
  EXPECT_EQ(mset.Count(40), 4);
  EXPECT_EQ(mset.Count(30), 3);
  EXPECT_EQ(mset.Count(20), 2);
  EXPECT_EQ(mset.Count(10), 1);

  // Remove all but 1 value
  for (int i = 0; i < 4; i++)
    mset.Remove(50);

  for (int i = 0; i < 3; i++)
    mset.Remove(40);

  for (int i = 0; i < 2; i++)
    mset.Remove(30);

  for (int i = 0; i < 1; i++)
    mset.Remove(20);

  mset.Remove(10);

  // Confirm final size
  EXPECT_EQ(mset.Size(), 4);
  EXPECT_EQ(mset.Empty(), false);

  // Check final count
  EXPECT_EQ(mset.Count(50), 1);
  EXPECT_EQ(mset.Count(40), 1);
  EXPECT_EQ(mset.Count(30), 1);
  EXPECT_EQ(mset.Count(20), 1);
  EXPECT_THROW(mset.Count(10), std::exception);
}

// 9) Check Count, Contains, Max, Min after insertions & removals
TEST(Multiset, RandomCount) {
  Multiset<int> mset;

  // Insertion of duplicates
  for (int i = 0; i < 5; i++)
    mset.Insert(5);

  // Check contents
  EXPECT_EQ(mset.Max(), 5);
  EXPECT_EQ(mset.Min(), 5);
  EXPECT_EQ(mset.Count(5), 5);
  EXPECT_EQ(mset.Contains(5), true);

  // Insertion & removal of more values
  for (int i = 0; i < 2; i++)
    mset.Remove(5);

  mset.Insert(4);
  mset.Insert(2);
  mset.Insert(9);
  mset.Insert(9);

  // Check contents
  EXPECT_EQ(mset.Max(), 9);
  EXPECT_EQ(mset.Min(), 2);
  EXPECT_EQ(mset.Count(9), 2);
  EXPECT_EQ(mset.Count(5), 3);
  EXPECT_EQ(mset.Count(4), 1);
  EXPECT_THROW(mset.Count(11), std::exception);
  EXPECT_EQ(mset.Contains(2), true);
  EXPECT_EQ(mset.Contains(11), false);
  EXPECT_EQ(mset.Contains(5), true);
}

// 10) Check Floor, Ceil, Count, Contains,
// Max, Min after ordered insertions & removals
TEST(Multiset, OrderedDuplicates) {
  Multiset<int> mset;

  // Confirm an empty set
  EXPECT_EQ(mset.Empty(), true);

  // Ordered insertion
  for (int i = 10; i <= 100; i += 10)
    mset.Insert(i);

  // Duplicate ordered insertion
  for (int i = 10; i <= 100; i += 10)
    mset.Insert(i);

  // Duplicate ordered insertion
  for (int i = 10; i <= 100; i += 10)
    mset.Insert(i);

  // Remove ordered insertion
  for (int i = 10; i <= 100; i += 10)
    mset.Remove(i);

  // Check contents
  EXPECT_EQ(mset.Max(), 100);
  EXPECT_EQ(mset.Min(), 10);

  EXPECT_EQ(mset.Size(), 20);
  EXPECT_EQ(mset.Empty(), false);

  EXPECT_EQ(mset.Count(10), 2);
  EXPECT_EQ(mset.Count(30), 2);
  EXPECT_THROW(mset.Count(5), std::exception);

  EXPECT_EQ(mset.Floor(85), 80);
  EXPECT_EQ(mset.Floor(110), 100);
  EXPECT_THROW(mset.Floor(5), std::exception);

  EXPECT_EQ(mset.Ceil(-10), 10);
  EXPECT_EQ(mset.Contains(85), false);
  EXPECT_EQ(mset.Contains(100), true);
  EXPECT_THROW(mset.Ceil(110), std::exception);

  // Remove ordered insertion
  for (int i = 10; i <= 100; i += 10)
    mset.Remove(i);

  // Remove ordered insertion
  for (int i = 10; i <= 100; i += 10)
    mset.Remove(i);

  // Check an empty set
  EXPECT_EQ(mset.Size(), 0);
  EXPECT_EQ(mset.Empty(), true);

  EXPECT_THROW(mset.Count(10), std::exception);
  EXPECT_THROW(mset.Count(100), std::exception);
  EXPECT_THROW(mset.Floor(10), std::exception);
  EXPECT_THROW(mset.Ceil(100), std::exception);
  EXPECT_THROW(mset.Max(), std::exception);
  EXPECT_THROW(mset.Min(), std::exception);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

