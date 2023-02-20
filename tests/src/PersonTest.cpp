#include "Person.hpp"
#include"String.hpp"
#include<gtest/gtest.h>

using namespace person;
TEST(PersonTest, constructorTest){
    Person p1("Ghosh", "Palas", "8670787487");
    Person p2("ghosh");
    EXPECT_LT(p1,p2);
    
}