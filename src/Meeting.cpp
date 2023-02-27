#include "Meeting.hpp"

#include <algorithm>

namespace meeting {

// using Participants_t =
//     Ordered_list<const Person*, Less_than_ptr<const Person*>>;

Meeting::Meeting(int time_, const String& topic_)
    : m_time(time_), m_topic(topic_) {}
void Meeting::add_participant(const Person* person) {
  participants.insert(person);
}

bool Meeting::is_participant_present(const Person* p) const {
  // as we are dealing with pointer we cannot use ordered_list find
  // since find use object & and we should not pass pointer as reference
  //  Participants_t::const_Iterator result = participants.find(p);
  for (Participants_t::const_Iterator itr = participants.begin();
       itr != participants.end(); ++itr) {
    if (*(*itr) == *(p)) {
      return true;
    }
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

bool Meeting::operator==(const Meeting& other) const {
  if (!(*this < other) && !(other < *this)) {
    return false;
  } else {
    return true;
  }
}
// Print the Meeting data as follows:
// The meeting time and topic on one line, followed either by:
// the no-participants message with an endl
// or the partipcants, one per line, with an endl after each one
std::ostream& operator<<(std::ostream& os, const Meeting& meeting) {
  os << "Meeting time: " << meeting.m_time
     << " Meetting topic: " << meeting.m_topic << std::endl;
  if (meeting.participants.empty()) {
    os << " No participants " << std::endl;
  } else {
    os << "Participents list: " << std::endl;
    std::for_each(meeting.participants.begin(), meeting.participants.end(),
                  [&os](const Person* person_itr) {
                    os << person_itr->get_lastname() << std::endl;
                  });
  }
  return os;
}

void Meeting::copy_participants(Participants_t list_participants) {
  auto start_participant = list_participants.begin();
  auto end_participant = list_participants.end();
  for (; start_participant != end_participant; ++start_participant) {
    Person p{
        (*(start_participant))->get_firstname(),
        (*(start_participant))->get_lastname(),
        (*(start_participant))
            ->get_phone_number()}; /* *iterator returns object, here object is
                                      person pointer hence -> operator used*/
    this->add_participant(&p);
  }
}

void Meeting::clear_contents() {
  m_time = 0;
  m_topic = "";
  participants.clear();
}


}  // namespace meeting
