#include "Room.hpp"

namespace room {

void Room::add_Meeting(const Meeting& m) {
  Meetings_t::Iterator itr = meetings.find(m);
  if (itr == meetings.end()) {
    // throw exception
  } else {
    meetings.insert(m);
  }
}

void Room::add_Meeting(Meeting&& m) {
  Meeting temp_meeting = m;
  add_Meeting(m);
}

// Return true if there is a Meeting at the time, false if not.
bool Room::is_Meeting_present(int time) const {
  const Meeting probe(time);
  Meetings_t::const_Iterator find_result = meetings.find(probe);
  if (find_result == meetings.end()) {
    return false;
  } else {
    return true;
  }
}

// TODO: if the meeting is not present throw an exception
Meeting& Room::get_Meeting(int time) {
  const Meeting probe(time);
  Meetings_t::Iterator find_result = meetings.find(probe);
  if (find_result != meetings.end()) {
    return *(find_result);
  }
}

// TODO: if the meeting is not present throw an exception
const Meeting& Room::get_Meeting(int time) const {
  const Meeting probe(time);
  Meetings_t::const_Iterator find_result = meetings.find(probe);
  if (find_result != meetings.end()) {
    return *(find_result);
  }
}

}  // namespace room
