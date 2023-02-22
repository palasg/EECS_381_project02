#include "Meeting.hpp"

namespace meeting {

Meeting::Meeting(int time_, const String& topic_)
    : m_time(time_), m_topic(topic_) {}
void Meeting::add_participant(const Person* person) {
  participants.insert(person);
}

bool Meeting::is_participant_present(const Person* p) const {
  Participants_t::const_Iterator result = participants.find(p);
  if (result != participants.end()) {
    return true;
  } else {
    return false;
  }
}

void Meeting::remove_participant(const Person* p) {
  Participants_t::const_Iterator result = participants.find(p);
  if (result != participants.end()) {
    participants.erase(result);
  }
}

bool Meeting::operator<(const Meeting& other) const {
  return m_time < other.m_time;
}

}  // namespace meeting
