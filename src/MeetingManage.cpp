#include "MeetingManage.h"

bool MeetingManage::instanceFlag_ = false;
MeetingManage* MeetingManage::instance_ = NULL;

MeetingManage* MeetingManage::getInstance() {
  if (!instanceFlag_)
    instance_ = new MeetingManage();
  return instance_;
}

MeetingManage::MeetingManage() {
  instanceFlag_ = true;
  instance_ = NULL;
  meetings_.clear();
}

MeetingManage::~MeetingManage() {
  instanceFlag_ = false;
  meetings_.clear();
}

void MeetingManage::initMeetingsList(std::list<Meeting> meetings) {
  meetings_ = meetings;
}

std::list<Meeting> MeetingManage::acquireMeetingsList(void) {
  return meetings_;
}

Meeting* MeetingManage::queryMeetingByTitle(std::string title) {
  for (std::list<Meeting>::iterator iter = meetings_.begin();
      iter !=meetings_.end(); iter++)
          if ( (*iter).getTitle() == title )
              return &(*iter);
  return 0;
}

std::list<Meeting> MeetingManage::queryMeetingsByTime(std::string userName,
                                                     Date stime, Date etime) {
  std::list<Meeting> tmp;
  for (std::list<Meeting>::iterator iter = meetings_.begin();
      iter !=meetings_.end(); iter++)
          if ( (*iter).getSponsor() == userName
            && stime == (*iter).getStartDate()
            && etime == (*iter).getEndDate() )
              tmp.push_back(*iter);
  return tmp;
}

std::list<Meeting> MeetingManage::listAllMeetings(std::string userName) {
  std::list<Meeting> tmp1 = listAllSponsorMeetings(userName);
  std::list<Meeting> tmp2 = listAllParticipateMeetings(userName);

  for (std::list<Meeting>::iterator it1 = tmp1.begin();
       it1 != tmp1.end(); it1++)
  tmp2.push_back(*it1);

  return tmp2;
}

std::list<Meeting> MeetingManage::listAllSponsorMeetings(std::string userName) {
  std::list<Meeting> tmp;
  for ( std::list<Meeting>::iterator iter = meetings_.begin();
    iter != meetings_.end(); iter++)
      if (userName == (*iter).getSponsor())
          tmp.push_back(*iter);
  return tmp;
}

std::list<Meeting>
MeetingManage::listAllParticipateMeetings(std::string userName) {
  std::list<Meeting> tmp;
  for ( std::list<Meeting>::iterator iter = meetings_.begin();
    iter != meetings_.end(); iter++)
      if (userName == (*iter).getParticipator())
          tmp.push_back(*iter);
  return tmp;
}

bool MeetingManage::addMeeting(std::string sponsor, std::string participator,
                               Date stime, Date etime, std::string title) {
  if (stime >= etime)
    return false;
  if (queryMeetingByTitle(title) != NULL)
    return false;
  for (std::list<Meeting>::iterator iter = meetings_.begin();
    iter != meetings_.end(); iter++)
      if ((*iter).getTitle() == title ||
         (
         (
           (*iter).getSponsor() == sponsor ||
           (*iter).getSponsor() == participator ||
           (*iter).getParticipator() == sponsor ||
           (*iter).getParticipator() == participator)
           &&
           !( (*iter).getEndDate() < stime ||
           (*iter).getStartDate() > etime )
         )
         ) {
    return false;
  }
  Meeting* ne = new Meeting(sponsor, participator, stime, etime, title);
  meetings_.push_back(*ne);
  delete ne;
  return true;
}

bool MeetingManage::deleteMeeting(std::string userName, std::string title) {
  for (std::list<Meeting>::iterator iter = meetings_.begin();
      iter !=meetings_.end(); iter++)
          if ((*iter).getTitle() == title && (*iter).getSponsor() == userName) {
              meetings_.erase(iter);
              return true;
          }
  return false;
}

bool MeetingManage::deleteAllMeetings(std::string userName) {
  bool flag = false;
  for (std::list<Meeting>::iterator iter = meetings_.begin();
      iter !=meetings_.end(); iter++)
          if ( (*iter).getSponsor() == userName ||
               (*iter).getParticipator() == userName ) {
              meetings_.erase(iter);
              flag = true;
          }
  return flag;
}

bool MeetingManage::updateMeetingParticipator(std::string title,
                                 std::string newParticipator) {
  for (std::list<Meeting>::iterator iter = meetings_.begin();
      iter !=meetings_.end(); iter++)
          if ( (*iter).getTitle() == title ) {
              (*iter).setParticipator(newParticipator);
              return true;
          }
  return false;
}

bool MeetingManage::updateMeetingStartDate(std::string title,
     Date newStartDate) {
  for (std::list<Meeting>::iterator iter = meetings_.begin();
      iter != meetings_.end(); iter++)
          if ( (*iter).getTitle() == title ) {
              if (newStartDate > (*iter).getEndDate() )
                  return false;
              (*iter).setStartDate(newStartDate);
              return true;
          }
  return false;
}

bool MeetingManage::updateMeetingEndDate(std::string title, Date newEndDate) {
  for (std::list<Meeting>::iterator iter = meetings_.begin();
      iter !=meetings_.end(); iter++)
          if ( (*iter).getTitle() == title ) {
              if ( (*iter).getStartDate() > newEndDate )
                  return false;
              (*iter).setEndDate(newEndDate);
              return true;
          }
  return false;
}

