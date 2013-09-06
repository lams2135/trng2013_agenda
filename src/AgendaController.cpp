#include "AgendaController.h"

AgendaController::AgendaController() {
  startAgenda();
}

void AgendaController::getOperation() {
  if (currentUser_ == NULL) {
    std::cout << "------------------Agenda-------------------\n";
    std::cout << "Action :\n";
    std::cout << "l  -  log in Agenda by user name and password\n";
    std::cout << "r  -  register an Agenda account\n";
    std::cout << "q  -  quit Agenda\n";
    std::cout << "-------------------------------------------\n";
  }
  executeOperation(getCmd());
}
void AgendaController::startAgenda() {
  currentUser_ = NULL;
  agendaService_.startAgenda();
}

bool AgendaController::executeOperation(std::string op) {
  // guest operations
  if (currentUser_ == NULL) {
    if (op == "l")
      userLogIn();
    else if (op == "r")
      userRegister();
    else if (op == "q")
      quitAgenda();
    else
      goto EOJP1;
  } else if (currentUser_ != NULL) {
    // signned operations
    EOJP1:
    if (op == "o")
      userLogOut();
    else if (op == "dc")
      deleteUser();
    else if (op == "lu")
      listAllUsers();
    else if (op == "cm")
      createMeeting();
    else if (op == "la")
      listAllMeetings();
    else if (op == "las")
      listAllSponsorMeetings();
    else if (op == "lap")
      listAllParticipateMeetings();
    else if (op == "qm")
      queryMeetingByTitle();
    else if (op == "qt")
      queryMeetingByTimeInterval();
    else if (op == "dm")
      deleteMeetingByTitle();
    else if (op == "da")
      deleteAllMeetings();
    else
      goto EOJP2;
  } else {
    EOJP2:
    std::cout << "invalid input, try again\n";
    getOperation();
    return false;
  }
  return true;
}

void AgendaController::userLogIn() {
  std::cout << "[log in] [user name] [password]\n";
  std::cout << "[log in] ";
  std::string urN, p;
  std::cin >> urN >> p;
  currentUser_ = agendaService_.userLogIn(urN, p);
  if (currentUser_ == NULL) {
    std::cout << "[error] log in fail!\n";
    getOperation();
  } else {
    std::cout << "[log in] succeed!\n\n";
    std::cout << "-------------------Agenda--------------------\n";
    std::cout << "Action :\n";
    std::cout << "o   - log out Agenda\n";
    std::cout << "dc  - delete Agenda account\n";
    std::cout << "lu  - list all Agenda user\n";
    std::cout << "cm  - create a meeting\n";
    std::cout << "la  - list all meetings\n";
    std::cout << "las - list all sponsor meetings\n";
    std::cout << "lap - list all participate meetings\n";
    std::cout << "qm  - query meeting by title\n";
    std::cout << "qt  - query meeting by time interval\n";
    std::cout << "dm  - delete meeting by title\n";
    std::cout << "da  - delete all meetings\n";
    std::cout << "---------------------------------------------\n";
    getOperation();
  }
}

void AgendaController::userRegister() {
  std::cout << "[register] [user name] [password] [email] [phone]\n";
  std::cout << "[register] ";
  std::string urN, pw, em, ph;
  std::cin >> urN >> pw >> em >> ph;
  if (agendaService_.userRegister(urN, pw, em, ph))
    std::cout << "[register] succeed!\n";
  else
    std::cout << "[error] register fail!\n";
  getOperation();
}
void AgendaController::quitAgenda() {
  agendaService_.quitAgenda();
}

void AgendaController::userLogOut() {
  currentUser_ = NULL;
  getOperation();
}

void AgendaController::deleteUser() {
  if (agendaService_.deleteUser(*currentUser_))
    std::cout << "[delete agenda account] succeed!\n";
  else
    std::cout << "[error] delete agenda account fail!\n";
    std::cout << std::endl;
  userLogOut();
}

void AgendaController::listAllUsers() {
  std::cout << "[list all users]\n\n";
  std::cout << "name\temail\tphone\n";
  std::list<User> tmp;
  std::list<User>::iterator pt;
  tmp = agendaService_.listAllUsers();
  for (pt = tmp.begin(); pt != tmp.end(); pt++) {
    std::cout << pt->getName() << "\t" << pt->getEmail();
    std::cout << "\t" << pt->getPhone() << std::endl;
  }
  std::cout << std::endl;
  getOperation();
}

void AgendaController::createMeeting() {
  std::cout << "[create meeting] [title] [participator] ";
  std::cout << "[start time<yyyy-mm-dd/hh:mm>] ";
  std::cout << "[end time<yyyy-mm-dd/hh:mm>]\n";
  std::cout << "[create meeting] ";
  std::string tit, part, st, et;
  std::cin >> tit >> part >> st >> et;
  if (agendaService_.createMeeting(currentUser_->getName(), tit,
              part, st, et))
      std::cout << "[create meeting] succeed!\n";
  else
    std::cout << "[error] create meeting fail!\n";
  getOperation();
}

void AgendaController::listAllMeetings() {
  std::cout << "[list all meetings]\n\n";
  std::list<Meeting> tmp;
  tmp = agendaService_.listAllMeetings(currentUser_->getName());
  printMeetings(tmp);
  getOperation();
}

void AgendaController::listAllSponsorMeetings() {
  std::cout << "[list all sponsor meetings]\n\n";
  std::list<Meeting> tmp;
  tmp = agendaService_.listAllSponsorMeetings(currentUser_->getName());
  printMeetings(tmp);
  getOperation();
}

void AgendaController::listAllParticipateMeetings() {
  std::cout << "[list all participate meetings]\n\n";
  std::list<Meeting> tmp;
  tmp = agendaService_.listAllParticipateMeetings(currentUser_->getName());
  printMeetings(tmp);
  getOperation();
}

void AgendaController::queryMeetingByTitle() {
  std::cout << "[query meeting] [title]:\n" << "[query meeting] \n\n";
  std::string A;
  std::cin >> A;
  std::cout << "***" << A << "***" << std::endl;
  std::cout << "sponsor\tparticipator\t\t";
  std::cout << "start time\tend time\n";
  Meeting * mpt = agendaService_.meetingQuery(A);
  if (mpt == NULL) {
    std::cout << mpt->getSponsor() << "\t" << mpt->getParticipator();
    std::cout << "\t\t" << Date::dateToString(mpt->getStartDate());
    std::cout << "\t" << Date::dateToString(mpt->getEndDate());
    std::cout << std::endl;
  } else {
    std::cout << "no such meeting title!" << std::endl;
  }
  getOperation();
}

void AgendaController::queryMeetingByTimeInterval() {
  std::cout << "\n[query meetings] [start time<yyyy-mm-dd/hh:mm>] ";
  std::cout << "[end time<yyyy-mm-dd/hh:mm>]\n";
  std::cout << "[query meetings] ";
  std::string sD, eD;
  std::cin >> sD >> eD;
  std::list<Meeting> tmp;
  tmp = agendaService_.meetingQuery(currentUser_->getName(), sD, eD);
  std::cout << "\n[query meetings]\n";
  printMeetings(tmp);
  getOperation();
}

void AgendaController::deleteMeetingByTitle() {
  std::cout << "[delete meeting] [title]\n";
  std::cout << "[delete meeting] ";
  std::string A;
  std::cin >> A;
  if (agendaService_.deleteMeeting(currentUser_->getName(), A))
    std::cout << "\n[delete meeting by title] succeed!\n";
  else
    std::cout << "\n[error] delete meeting fail!\n";
  getOperation();
}

void AgendaController::deleteAllMeetings() {
  if (agendaService_.deleteAllMeetings(currentUser_->getName()))
    std::cout << "\n[delete all meetings] succeed!\n";
  else
    std::cout << "\n[delete all meetings] fail!\n";
  getOperation();
}

void AgendaController::printMeetings(std::list<Meeting> meetings) {
  std::cout << "sponsor\tparticipator\t";
  std::cout << "start time\t\tend time\n";
  std::list<Meeting>::iterator pt;
  for (pt = meetings.begin(); pt!= meetings.end(); pt++) {
    std::cout << pt->getSponsor() << "\t" << pt->getParticipator();
    std::cout << "\t\t" << Date::dateToString(pt->getStartDate());
    std::cout << "\t" << Date::dateToString(pt->getEndDate());
    std::cout << std::endl;
  }
}

std::string AgendaController::getCmd(void) {
  std::cout.clear();
  std::string tmp_ = "";
  while (tmp_.length() < 1) {
    if (currentUser_ == NULL)
      std::cout << "Agenda : ~$ ";
    else
      std::cout << "Agenda@" << currentUser_->getName() << " : # ";
    std::getline(std::cin, tmp_, '\n');
  }
  return tmp_;
}
