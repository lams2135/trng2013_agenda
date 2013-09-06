#include "AgendaService.h"
#include<iostream>

int AgendaService::serviceRunning_ = 0;

AgendaService::AgendaService() {
  userManage_ = UserManage::getInstance();
  meetingManage_ = MeetingManage::getInstance();
  fileManage_ = FileManage::getInstance();
  serviceRunning_++;
}

AgendaService::~AgendaService() {
  serviceRunning_--;
  if (!serviceRunning_) {
    delete userManage_;
    delete meetingManage_;
    delete fileManage_;
  }
}

void AgendaService::startAgenda(void) {
  if (serviceRunning_ == 1) {
    std::list<User> tmpa_;
    std::list<Meeting> tmpb_;
    tmpa_ = fileManage_->readUsersFromFile();
    tmpb_ = fileManage_->readMeetingsFromFile();
    userManage_->initUsersList(tmpa_);
    meetingManage_->initMeetingsList(tmpb_);
  }
}

void AgendaService::quitAgenda(void) {
  fileManage_->writeUsersToFile(userManage_->listAllUsers());
  fileManage_->writeMeetingsToFile(meetingManage_->acquireMeetingsList());
}

User* AgendaService::userLogIn(std::string userName, std::string password) {
  User* tmp_ = userManage_->findUserByName(userName);
  if (!tmp_)
    return NULL;
  if (tmp_->getPassword() != password)
    return NULL;
  else
    return tmp_;
}

bool AgendaService::userRegister(std::string userName, std::string password,
                                 std::string email, std::string phone) {
  return userManage_->createUser(userName, password, email, phone);
}

bool AgendaService::deleteUser(User user) {
  std::list<Meeting> tmp_ = meetingManage_->listAllMeetings(user.getName());
  if (!tmp_.empty())
    return false;
  return userManage_->deleteUser(user);
}

std::list<User> AgendaService::listAllUsers(void) {
  return userManage_->listAllUsers();
}

bool AgendaService::createMeeting(std::string userName, std::string title,
                                  std::string participator,
                                  std::string startDate, std::string endDate) {
  User *utmpa_ = userManage_->findUserByName(userName);
  User *utmpb_ = userManage_->findUserByName(participator);
  if (!(utmpa_ && utmpb_))
    return false;
  Date sd = Date::stringToDate(startDate);
  Date ed = Date::stringToDate(endDate);
  if (!(Date::isValid(sd) && Date::isValid(ed)))
    return false;
  return meetingManage_->addMeeting(userName, participator, sd, ed, title);
}

Meeting* AgendaService::meetingQuery(std::string title) {
  return meetingManage_->queryMeetingByTitle(title);
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName,
                                               std::string startDate,
                                               std::string endDate) {
  Date tmpa_ = Date::stringToDate(startDate);
  Date tmpb_ = Date::stringToDate(endDate);
  return meetingManage_->queryMeetingsByTime(userName, tmpa_, tmpb_);
}

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
  return meetingManage_->listAllMeetings(userName);
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
  return meetingManage_->listAllSponsorMeetings(userName);
}

std::list<Meeting>
AgendaService::listAllParticipateMeetings(std::string userName) {
  return meetingManage_->listAllParticipateMeetings(userName);
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
  return meetingManage_->deleteMeeting(userName, title);
}

bool AgendaService::deleteAllMeetings(std::string userName) {
  return meetingManage_->deleteAllMeetings(userName);
}

