
#include "../../includes/String/String.hpp"
#include <gtest/gtest.h>

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
