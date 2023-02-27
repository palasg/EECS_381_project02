#include <iostream>
#include <string>

namespace userin {

enum class commandAction {
  p = 0, // print
  a,     // add
  r,     // reschedule
  d,     // delete
  s,     // save to file
  l,     // load from a file
};

enum class commandObject {
  i = 0, // individual person
  r,     // room
  m,     // meetings
  p,     // participants
  s,     // schedule (all meeting - print and delete command only)
  g,     // group (all people - print and delete command only )
  a,     // all for the delete commannd, allocation in the print command
  d,     // data (all people and meeting save and delete command only)
};

class UserInputs {
public:
  UserInputs();

  ~UserInputs();

  std::string getUserInput();
  char userInChar;

  void Process();

private:
  std::string inputStr = {};
};

} // namespace userin
