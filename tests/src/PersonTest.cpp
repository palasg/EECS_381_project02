#include <gtest/gtest.h>

#include "Person.hpp"
#include "String.hpp"

using namespace person;
TEST(PersonTest, constructorTest) {
  Person p1("Ghosh", "Palas", "8670787487");
  Person p2("ghosh");
  EXPECT_LT(p1, p2);
  std::cout << "P1: " << p1 << std::endl;
  std::cout << "P2: " << p2 << std::endl;
}