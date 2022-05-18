//./Build.sh -b Debug

#include <iostream>
#include "UserInputs.h"
#include"String.hpp"

using std::cout;
using std::endl;

int main(int argc, char const *argv[]) {
  if (argc == 1) {
    cout << "no input args " << endl;
  } else {
    cout << *argv[1] << endl;
  }

  return 0;
}
