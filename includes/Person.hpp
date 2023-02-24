/* A Person object simply contains Strings for a person's data.
Once created, the data cannot be modified. */

/* *** NOTE:
This is a "skeleton" for the header file. Its purpose is to specify what must be
in the correct header file while leaving you the job of creating the correct
header file. Thus there is a variety of items you will have to add to this file
to get a complete correct header file. For example, note that "class Person" is
missing below -- you have to complete the Person class declaration.

If after a function header is a comment "fill this in" remove the comment and
replace it with the proper code here in the header file.  All other functions
should be defined in the .cpp file. Comments starting with "***" are instructors
to you - remove them from your finished code. Remove this comment too. */

#ifndef PERSON_H
#define PERSON_H

#include <iostream>

#include "String.hpp"

static bool debug = true;

namespace person {

class Person {
 public:
  Person(const String& firstname_, const String& lastname_,
         const String& phoneno_);
  // construct a Person object with only a lastname
  Person(const String& lastname_);

  /* *** Disallow all forms of copy/move construction or assignment */
  // These declarations help ensure that Person objects are unique,
  // like they are in the problem domain
  // delete copy constructor
  Person(Person& other) = delete;

  // delete move constructor
  Person(const Person&& other) = delete;

  // delete assignment operator
  Person& operator=(const Person& other) = delete;

  // delete move assignment operator
  Person& operator=(const Person&& other) = delete;

  // Construct a Person object from a file stream in save format.
  // Throw Error exception if invalid data discovered in file.
  // No check made for whether the Person already exists or not.
  // Input for a member variable value is read directly into the member
  // variable.
  Person(std::ifstream& is);

  // Accessors
  const String& get_lastname() const { return m_last_name; }

  // Write a Person's data to a stream in save format with final endl.
  void save(std::ostream& os) const;

  // This operator defines the order relation between Persons, based just on the
  // last name
  bool operator<(const Person& rhs) const {
    return m_last_name < rhs.m_last_name;
  }

bool operator==(const Person& rhs) const {
    return m_last_name == rhs.m_last_name;
  }
  /* *** provide here a friend declaration for the output operator */
  friend std::ostream& operator<<(std::ostream& os, const Person& person);

 private:
  /* *** private members are your choice */

  const String m_first_name;
  const String m_last_name;
  const String m_phone_no;
};

// output firstname, lastname, phoneno with one separating space, NO endl
std::ostream& operator<<(std::ostream& os, const Person& person);

}  // end of namespace person
#endif