#include"Room.hpp"


namespace room
{

void Room::add_Meeting(const Meeting& m){
  Meetings_t::Iterator itr= meetings.find(m);
  if(itr == meetings.end()){ 
    //throw exception
  }
  else{
    meetings.insert(m);
  }
}

void Room::add_Meeting(Meeting&& m){
    Meeting temp_meeting = m;
    add_Meeting(temp_meeting);
}

    
} // namespace room
