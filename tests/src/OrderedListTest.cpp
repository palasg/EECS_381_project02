#include <gtest/gtest.h>

#include "OrderedList.hpp"

TEST(Ordered_list_Test, constructorTest) {
  Ordered_list<int> int_list;
  int var = 5;
  int_list.insert(var);
  EXPECT_EQ(int_list.size(), 1);
  var = 10;
  int_list.insert(var);
  var = 12;
  int_list.insert(var);
  EXPECT_EQ(int_list.size(), 3);
  var = 4;
  int_list.insert(var);
  var = 6;
  int_list.insert(var);
  EXPECT_EQ(int_list.size(), 5);

  for (Ordered_list<int>::Iterator itr = int_list.begin();
       itr != int_list.end(); ++itr) {
    std::cout << *itr;
  }

  std::cout << std::endl;

  Ordered_list<int>::Iterator result = int_list.find({5});
  if (result != int_list.end()) {
    int_list.erase(result);
  }
    for (Ordered_list<int>::Iterator itr = int_list.begin();
       itr != int_list.end(); ++itr) {
    std::cout << *itr;
  }
}