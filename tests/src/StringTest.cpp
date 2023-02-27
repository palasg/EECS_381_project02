
#include "String.hpp"
#include<gtest/gtest.h>

TEST(StringTest_1, outOfBoundCheck) {
  String str("Hell Yeah");
  EXPECT_EQ(str[0], 'H');
  EXPECT_EQ(str[8],'h');
  EXPECT_EQ(str[11],' ');//return void and print Index out of bound
  str.DisplayStringInfo();
  str+='p';
  str.DisplayStringInfo();
  str.clear();
}
TEST(StringTest_2, operator_plus){
 
String str1("Hello");
String str2("world");
str1+= str2;
String result_str("Helloworld");
EXPECT_TRUE(str1==result_str);
}

TEST(StringTest3, copyMove){
  String temp_str{"Hello"}; 
  String str(std::move(temp_str)); 
}

TEST(StringTest4, operator_concatinate_assignment){

String str1 {"hello"};
String str2{"world"};
str1+= str2; 
std::cout << str1 <<std::endl;

}

// TEST(StringTest_3, operator_inputstream){
//   String str;
//   std::cin >> str; 
//   str.DisplayStringInfo();

// }

// TEST(StringTest_4, input_operator){
//   String str; 
//   std::cin >> str;
//   std::cout <<str; 
// }
