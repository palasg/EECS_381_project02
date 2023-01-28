#include "../../includes/String/String.hpp"
#include <cstring>
#include <memory>

using size_t = std::size_t;

char String::a_null_byte = ' ';
int String::number = 0;                   // counts number of String objects in existence
std::size_t String::total_allocation = 0; // counts total amount of memory allocated
bool String::messages_wanted = true;

size_t String::calculateMinimumAllocationSize(std::size_t free_space,
                                              std::size_t required_size,
                                              std::size_t string_length)
{
  if (free_space == 0)
  {
    return minimum_allocation > required_size ? minimum_allocation
                                              : (2 * required_size + 1);
  }
  else if (free_space > required_size)
  {
    return 0;
  }
  else
  {
    return 2 * (string_length + required_size + 1);
  }
}
/*
 * Functionality of this is to maintain all the
 * secondary info about String
 * string_length_ can be deduced
 * delta_number: if you want to increase the number of string
 * memory_length: allocated memory length
 *
 */
void String::houseKeeping()
{
  string_length_ = strlen(content_);
  number++;
  free_space_ = memory_length_ - string_length_;
}

// Swap functionality
void Swap(String &str1, String &str2)
{
  std::swap(str1.content_, str2.content_);
  std::swap(str1.free_space_, str2.free_space_);
  std::swap(str1.memory_length_, str2.memory_length_);
  std::swap(str1.string_length_, str2.string_length_);
}

// Default initialization is to contain an empty string with no allocation.
// If a non-empty C-string is supplied, this String gets minimum allocation.
String::String(const char *cstr_)
{
  if (strlen(cstr_) != 0)
  {
    // not
    if (messages_wanted)
    {
      std::cout << "From default c'tor; the input string is " << cstr_ << std::endl;
    }

    string_length_ = strlen(cstr_);
    memory_length_ = calculateMinimumAllocationSize(0, string_length_, 0);

    content_ = new char[memory_length_];
    strcpy(content_, cstr_);
    free_space_ = memory_length_ - string_length_;
  }
  else
  {
    if (messages_wanted)
    {
      std::cout << "From default c'tor; the input string is " << cstr_ << std::endl;
    }
    number++; // increase number of string
    content_ = nullptr;
    string_length_ = 0;
  }
}

// The copy constructor initializes this String with the original's data,
// and gets minimum allocation.
String::String(const String &original)
{
  size_t original_length = strlen(original.content_);
  memory_length_ = calculateMinimumAllocationSize(0, original_length, 0);
  content_ = new char[memory_length_];
  strcpy(content_, original.content_);
  number++;
  string_length_ = original_length;
  free_space_ = memory_length_ - string_length_;
}

// Assignment operators
// Left-hand side gets a copy of rhs data and gets minimum allocation.
// This operator use the copy-swap idiom for assignment.
String &String::operator=(const String &rhs)
{

  // if (this->content_!= rhs.content_) {
  //   //clear this
  //   //copy rhs
  //   //send this

  // }
  // return *this; .. This approach is having following cons
  // 1. self check 2. deallocation and then allocating memory (allocation step
  // is not exception safe so we might
  // be ending up with dangling pointer)
  String temp_string(rhs);
  Swap(*this, temp_string);
  return *this;
}

// This operator creates a temporary String object from the rhs C-string, and
// swaps the contents
String &String::operator=(const char *rhs)
{
  String intermediate(rhs);
  *this = intermediate;
  return *this;
}

// Return a reference to character i in the string.
// Throw exception if 0 <= i < size is false.
char &String::operator[](const std::size_t i)
{
  try
  {
    if (string_length_ != 0)
    {
      if (i < string_length_)
      {
        std::cout << "From non constant" << std::endl;
        return *(content_ + i);
      }
      else
      {
        String_exception e("Index out of bound");
        throw e;
      }
    }
    else
    {
      String_exception e("Index out of bound");
      throw e;
    }
  }
  catch (String_exception &e)
  {
    std::cerr << e.msg;
    return a_null_byte;
  }
}

const char &String::operator[](size_t i) const
{
  try
  {
    if (string_length_ != 0)
    {
      if (i < string_length_)
      {
        std::cout << "From +constant" << std::endl;
        return *(content_ + i);
      }
      else
      {
        String_exception e("Index out of bound");
        throw e;
      }
    }
    else
    {
      String_exception e("Index out of bound");
      throw e;
    }
  }
  catch (String_exception &e)
  {
    std::cerr << e.msg;
    return a_null_byte;
  }
} // const version for const Strings

// Modifiers
// Set to an empty string with minimum allocation by create/swap with an empty
// string.
void String::clear()
{

  String empty_string;
  Swap(*this, empty_string);
}

/* These concatenation operators add the rhs string data to the lhs object.
They do not create any temporary String objects. They either directly copy the
rhs data into the lhs space if it is big enough to hold the rhs, or allocate new
space and copy the old lhs data into it followed by the rhs data. The lhs object
retains the final memory allocation. If the rhs is a null byte or an empty
C-string or String, no change is made to lhs String. */
String &String::operator+=(char rhs)
{
  if (this->free_space_ > 1)
  {
    *(this->content_ + string_length_) = rhs;
    *(this->content_ + string_length_ + 1u) = '\0'; // null ternimated
    string_length_++;
    free_space_--;
    return *this;
  }
  else
  {
    char *temp = new char[string_length_ + 1u];
    strcpy(temp, this->content_);
    delete[] this->content_;
    this->content_ = new char[2 * string_length_ + 2u];
    strcpy(this->content_, temp);
    *(this->content_ + string_length_) = rhs;
    *(this->content_ + string_length_ + 1) = '\0';

    this->string_length_++;
    this->memory_length_ = 2 * string_length_ + 2u + 1u;
    free_space_ = this->memory_length_ - string_length_;
    total_allocation = total_allocation - strlen(temp) - +strlen(this->content_);

    delete[] temp;
    temp = nullptr;
    return *this;
  }
}

//  String &String::operator+=(const char *rhs){

//    std::size_t required_extra_space = strlen(rhs);
//    if (free_space_ > required_extra_space)
//    {
//      //just string concat
//      strcat(this->content_,rhs);
//      free_space_ = free_space_ - required_extra_space;
//      string_length_ = string_length_ + required_extra_space;

//    }

String &String::operator+=(const String &lhs)
{
  if (lhs.size() == 0)
  {
    return *this;
  }
  else
  {
    if (free_space_ > lhs.string_length_ + 1) // no change ro allocate
    {
      strcat(this->content_, lhs.content_);
      string_length_ += lhs.string_length_;
      free_space_ -= lhs.string_length_;
    }
    else
    {
      size_t required_allocation = calculateMinimumAllocationSize(free_space_, lhs.string_length_, string_length_);
      char *temp = new char[required_allocation];
      total_allocation = total_allocation - memory_length_ + required_allocation;
      String temp_str = String(content_); // std::move
      delete[] content_;
      content_ = temp;
      strcpy(content_, temp_str.content_);
      strcat(content_, lhs.content_);
      *(content_ + string_length_ + lhs.string_length_ + 1) = '\0';
      string_length_ = strlen(content_);
      free_space_ = required_allocation - string_length_;
      memory_length_ = required_allocation;
    }
  }
  return *this;
}

// }
// String &operator+=(const String &rhs);

void String::DisplayStringInfo() const
{
  std::cout << "String: " << this->content_ << std::endl;
  std::cout << "String length: " << this->string_length_ << std::endl;
  std::cout << "Allocated memory space: " << this->memory_length_ << std::endl;
  std::cout << "Free space: " << this->free_space_ << std::endl;
}

String::~String()
{
  if (messages_wanted && string_length_> 0)
  {
    std::cout << "Deleting string " << content_ << std::endl;
  }
  total_allocation -= memory_length_;
  memory_length_ = 0;
  number--;
  delete[] content_;
}

// Input and output operators
// The output operator writes the contents of the String to the stream
std::ostream &operator<<(std::ostream &os, const String &str)
{
  os << str.c_str();
  return os;
}

/* The input operator clears the supplied String, then starts reading the stream.
It skips initial whitespace, then copies characters into
the supplied str until whitespace is encountered again. The terminating
whitespace remains in the input stream, analogous to how string input normally works.
str is expanded as needed, and retains the final allocation.
If the input stream fails, str contains whatever characters were read. */
std::istream &operator>>(std::istream &is, String &str)
{
  // reading in stringstream from cin
  constexpr std::size_t kMaxBuff = 50u;
  char buff[kMaxBuff];
  std::size_t buff_free_space = kMaxBuff;
  char t;
  char *buff_ptr = buff;
  is >> t;
  // remove bigining spaces
  while (isspace(t) && !is.fail())
  {
    is >> t;
  }

  while (!is.fail() && !isspace(t) && (t != EOF) && (t != '\n'))
  {
    buff_free_space = buff_free_space - 1;
    if (buff_free_space > 0)
    {

      *buff_ptr = t;
      buff_ptr = buff_ptr + 1;
    }
    else
    {
      // extend buff
      //better use vector<char> and use pushback
    }
    is.get(t);
  }

  *buff_ptr = '\0';
  buff_ptr = buff;
  String str1 (buff_ptr);
  str = str1;
  return is;
}

// compare lhs and rhs strings; constructor will convert a C-string literal to a String.
// comparison is based on std::strcmp result compared to 0
bool operator==(const String &lhs, const String &rhs)
{

  int result = strcmp(lhs.c_str(), rhs.c_str());
  return (result == 0) ? true : false;
}
