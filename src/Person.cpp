#include "Person.hpp"

namespace person {
Person::Person(const String& firstname_, const String& lastname_,
               const String& phoneno_)
    : m_first_name{firstname_}, m_last_name{lastname_}, m_phone_no{phoneno_} {
  if (debug) {
    std::cout << "from person default ctor" << std::endl;
  }
}

Person::Person(const String& lastname_)
    : m_first_name(""), m_last_name{lastname_}, m_phone_no("") {
  if (debug) {
    std::cout << "From Person ctor with only last name" << std::endl;
  }
}

// output firstname, lastname, phoneno with one separating space, NO endl
std::ostream& operator<<(std::ostream& os, const Person& person) {
  os << person.m_first_name << ", " << person.m_last_name << ", "
     << person.m_phone_no;

  return os;
}
}  // namespace  person
