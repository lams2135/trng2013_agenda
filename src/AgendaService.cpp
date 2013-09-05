#include "AgendaService.h"

int AgendaService::serviceRunning_ = 0;

AgendaService::AgendaService() {
	userManage_ = UserManage::getInstance();
	meetingManage_ = MeetingManage::getInstance();
	fileManage_ = FileManage::getInstance();
	serviceRunning_++;
}

AgendaService::~AgendaService() {
	delete userManage_;
	delete meetingManage_;
	delete fileManage_;
	serviceRunning_--;
}

User *AgendaService::userLogIn(std::string userName, std::string password) {
	User *tmp_ = userManage_->findUserByName(userName);
	if (!tmp_)
		return NULL;
	if (tmp_->getPassword() == password)
		return tmp_;
	else
		return NULL;
}

bool AgendaService::userRegister(std::string userName, std::string password,
                                 std::string email, std::string phone) {
	if (userManage_->findUserByName(userName))
		return false;
	if (!User(userName, password, email, phone).isValid())
		return false;
	userManage_->createUser(userName, password, email, phone);
	return true;
}

bool AgendaService::deleteUser(User user) {
	meetingManage_->deleteAllMeetings(user.getName());
	return userManage_->deleteUser(user);
}

std::list<User> AgendaService::listAllUsers(void) {
	return userManage_->listAllUsers();
}

bool AgendaService::createMeeting(std::string userName, std::string title,
                                  std::string participator,
                                  std::string startDate, std::string endDate) {
	Date stime = Date::stringToDate(startDate);
	Date etime = Date::stringToDate(endDate);
	return meetingManage_->addMeeting(userName, participator,
	                                            stime, etime, title);
}

Meeting* AgendaService::meetingQuery(std::string title) {
	return meetingManage_->queryMeetingByTitle(title);
}

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
	return meetingManage_->listAllMeetings(userName);
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
	return meetingManage_->listAllSponsorMeetings(userName);
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(std::string userName) {
	return meetingManage_->listAllParticipateMeetings(userName);
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
	return meetingManage_->deleteMeeting(userName, title);
}

bool AgendaService::deleteAllMeetings(std::string userName) {
	return meetingManage_->deleteAllMeetings(userName);
}

void AgendaService::startAgenda(void) {
	if (serviceRunning_ > 1) // LamsPatch_0
		return;
	userManage_->initUsersList(fileManage_->readUsersFromFile());
	meetingManage_->initMeetingsList(fileManage_->readMeetingsFromFile());
}

void AgendaService::quitAgenda(void) {
	fileManage_->writeUsersToFile(userManage_->acquireUsersList());
	fileManage_->writeMeetingsToFile(meetingManage_->acquireMeetingsList());
}

