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

TEST(Ordered_list_test_2, copyConstrucctor) {
  Ordered_list<int> list;
  list.insert({5});
  list.insert({5});
  list.insert({7});
  Ordered_list<int> list_2 = list;
  EXPECT_EQ(list.size(), list_2.size());
  for (auto ele : list_2) {
    std::cout << ele <<std::endl;
  }
}

TEST(Ordered_list_test_3, Swap_test) {
  Ordered_list<int> list_1;
  list_1.insert({5});
  list_1.insert({5});
  list_1.insert({7});

 Ordered_list<int> list_2;
  list_2.insert({8});
  list_2.insert({9});
  list_2.insert({10});
  list_2.insert({11});
  list_2.insert({12});
  list_1.swap(list_2);

EXPECT_EQ(list_1.size(), 5);
EXPECT_EQ(list_2.size(), 3);

std::cout << "List_1 elememnt " <<std::endl;
  for (auto ele : list_1) {
    std::cout << ele <<std::endl;
  }

std::cout << "List_2 elememnt " <<std::endl;
  for (auto ele : list_2) {
    std::cout << ele <<std::endl;
  }

}