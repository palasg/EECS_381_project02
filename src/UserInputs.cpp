#include "UserInputs.h"

namespace userin {

UserInputs::UserInputs() = default;
UserInputs::~UserInputs() = default;
std::string UserInputs::getUserInput() { return inputStr; }
void UserInputs::Process() {
  bool gotFirstResponse = false;
  bool gotValidResponse = false;
  std::cin >> userInChar;
  while (!gotFirstResponse && !gotValidResponse) {

    gotFirstResponse = true;
    gotValidResponse = true;

    switch (userInChar) {

    case 'a':

      std::cout << "Adding something" << std::endl;
      break;
    case 'p':

      std::cout << "Printing something" << std::endl;

      break;
    case 'r':
      break;
    case 'l':
      break;
    case 'd':
      break;
    case 's':
      break;

    default:
      std::cout << "Enter a valid action command " << std::endl;
      break;
      ;
    }
  }
} // namespace userin

} // namespace userin
