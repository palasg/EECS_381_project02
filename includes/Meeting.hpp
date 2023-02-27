/* Meeting class - this class represents a Meeting in terms of a time, topic,
and list of participants. Note: Meeting's interface and I/O functions assume
that the time is expressed in 12-hour format.

Public functions provide for maintaining the list of participants,
but no direct access to it is allowed.

An overloaded operator< is provided to simplify constructing a list of Meetings
in order by time, and an output operator to simplify printing the Meeting
information.

We let the compiler supply the destructor and the copy/move constructors and
assignment operators.
*/

/* *** NOTE:
This is a "skeleton" for the header file. Its purpose is to specify what must be
in the correct header file while leaving you the job of creating the correct
header file. Thus there is a variety of items you will have to add to this file
to get a complete correct header file. For example, note that "class Meeting" is
missing below -- you have to complete the Meeting class declaration.

If after a function header is a comment "fill this in" remove the comment and
replace it with the proper code here in the header file.  All other functions
should be defined in the .cpp file. Comments starting with "***" are
instructions to you - remove them from your finished code. Remove this comment
too. */

#ifndef MEETING_H
#define MEETING_H

#include <iostream>

#include "OrderedList.hpp"
#include "Person.hpp"

using namespace person;

namespace meeting {

class Meeting {
 public:
  Meeting(int time_, const String& topic_);

  // construct a Meeting with only a time
  Meeting(int time_) : m_time(time_) {}
  /*fill this in*/
  // Construct a Meeting from an input file stream in save format
  // Throw Error exception if invalid data discovered in file.
  // No check made for whether the Meeting already exists or not.
  // Person list is needed to resolve references to meeting participants
  // Input for a member variable value is read directly into the member
  // variable.
  Meeting(
      std::ifstream& is,
      const Ordered_list<const Person*, Less_than_ptr<const Person*>>& people);

  // accessors
  int get_time() const { return m_time; }
  void set_time(int time_) { m_time = time_; }

  // Meeting objects manage their own participant list. Participants
  // are identified by a pointer to that individual's Person object.

  // Add to the list, throw exception if participant was already there.
  void add_participant(const Person* p);
  // Return true if the person is a participant, false if not.
  bool is_participant_present(const Person* p) const;
  // Remove from the list, throw exception if participant was not found.
  void remove_participant(const Person* p);

  // Write a Meeting's data to a stream in save format with final endl.
  void save(std::ostream& os) const;

  // This operator defines the order relation between meetings, based just on
  // the time
  bool operator<(const Meeting& other) const;

  bool operator==(const Meeting& other) const;

  /* *** provide a friend declaration for the output operator */

  friend std::ostream& operator<<(std::ostream& os, const Meeting& meeting);

  /* meeting assignment operator: */
  /*This is added for work around in ordered_list insert function assignment
  operator The assignment operator is not available for person list: Probably
  this is not good*/
  Meeting operator=(const Meeting& m) {
    // clear current meeting
    // check for self assignment
    // then copy it

    if (!(*this == m)) {
      this->clear_contents();
      this->m_time = m.m_time;
      this->m_topic = m.m_topic;
      this->copy_participants(m.participants);
      return *this;
    }
  }

  // copy assignments
  Meeting(const Meeting& m) {
    this->clear_contents();
    this->m_time = m.m_time;
    this->m_topic = m.m_topic;
    this->copy_participants(m.participants);
  }

  // destructor
  ~Meeting() { this->participants.clear(); }

 private:
  int m_time;
  String m_topic;
  using Participants_t =
      Ordered_list<const Person*, Less_than_ptr<const Person*>>;
  Participants_t participants;
  void copy_participants(Participants_t participants_list);
  void clear_contents();
};

// Print the Meeting data as follows:
// The meeting time and topic on one line, followed either by:
// the no-participants message with an endl
// or the partipcants, one per line, with an endl after each one
std::ostream& operator<<(std::ostream& os, const Meeting& meeting);

}  // end of namespace meeting
#endif