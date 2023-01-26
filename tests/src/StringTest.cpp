
#include "String.hpp"
#include<gtest/gtest.h>

TEST(StringTest, outOfBoundCheck) {
  String str("Hell Yeah");
  EXPECT_EQ(str[0], 'H');
  EXPECT_EQ(str[8],'h');
  EXPECT_EQ(str[11],' ');//return void and print Index out of bound
  str.DisplayStringInfo();
  str+='p';
  str.DisplayStringInfo();
  str.clear();
}
TEST(StringTest, operator_plus){

String str1("Hello");
String str2("world");
str1+= str2;
String result_str("Helloworld");
EXPECT_TRUE(str1==result_str);
}
