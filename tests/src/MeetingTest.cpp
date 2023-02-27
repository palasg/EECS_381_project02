#include <gtest/gtest.h>

#include <Meeting.hpp>

using namespace meeting;

TEST(MeetingTest, Test_1) {
  Meeting m1{10, "stand up"};
  const Person p1{"kankata", "kartik", "8670787"};
  const Person p2{"lebu", "dan", "93783003"};
  const Person p3{"bishu", "kana", "244349"};

  m1.add_participant(&p1);
  m1.add_participant(&p2);
  m1.add_participant(&p3);

  EXPECT_EQ(10, m1.get_time());

  EXPECT_TRUE(m1.is_participant_present(&p1));

  m1.remove_participant(&p2);

  EXPECT_FALSE(m1.is_participant_present(&p2));

  Meeting m2 = {10,"wow"};
  m2 = m1;

  std::cout << m1;
}