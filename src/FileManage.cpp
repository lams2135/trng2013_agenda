#include "FileManage.h"

#include <fstream>
#include <string>

bool FileManage::instanceFlag_ = false;
FileManage* FileManage::instance_ = NULL;

FileManage* FileManage::getInstance(void) {
  if (!instanceFlag_)
    instance_ = new FileManage();
  return instance_;
}

FileManage::FileManage() {
  instanceFlag_ = true;
  userFileName_ = "user.dat";
  meetingFileName_ = "meeting.dat";
}

FileManage::~FileManage() {
  instanceFlag_ = false;
}

std::list<User> FileManage::readUsersFromFile(void) {
  std::list<User> ret;
  std::string buff, tmp;
  User tmpu;
  std::ifstream fin(userFileName_.c_str());
  while (!fin.eof()) {
    std::getline(fin, buff, '\n');
    if (buff[0] == '[') {
      std::getline(fin, buff, '\n');
      tmpu.setName(buff);
      std::getline(fin, buff, '\n');
      tmpu.setPassword(buff);
      std::getline(fin, buff, '\n');
      tmpu.setEmail(buff);
      std::getline(fin, buff, '\n');
      tmpu.setPhone(buff);
      std::getline(fin, buff, '\n');
      if (buff[0] != ']')
        return ret;
      ret.push_back(tmpu);
    } else {
      if (buff == "# END") {
        fin.close();
        return ret;
      }
    }
  }
  fin.close();
  return ret;
}

void FileManage::writeUsersToFile(std::list<User> users) {
  std::ofstream fout(userFileName_.c_str());
  fout << "# START" << std::endl;
  for (std::list<User>::iterator it = users.begin();
       it != users.end(); ++it) {
    fout << "[" << std::endl;
    fout << (*it).getName() << std::endl;
    fout << (*it).getPassword() << std::endl;
    fout << (*it).getEmail() << std::endl;
    fout << (*it).getPhone() << std::endl;
    fout << "]" << std::endl;
  }
  fout << "# END" << std::endl;
  fout.close();
}

std::list<Meeting> FileManage::readMeetingsFromFile(void) {
  std::list<Meeting> ret;
  std::string buff, tmp;
  Meeting tmpu;
  std::ifstream fin(meetingFileName_.c_str());
  while (!fin.eof()) {
    std::getline(fin, buff, '\n');
    if (buff[0] == '[') {
      std::getline(fin, buff, '\n');
      tmpu.setSponsor(buff);
      std::getline(fin, buff, '\n');
      tmpu.setParticipator(buff);
      std::getline(fin, buff, '\n');
      tmpu.setStartDate(Date::stringToDate(buff));
      std::getline(fin, buff, '\n');
      tmpu.setEndDate(Date::stringToDate(buff));
      std::getline(fin, buff, '\n');
      tmpu.setTitle(buff);
      std::getline(fin, buff, '\n');
      if (buff[0] != ']')
        return ret;
      ret.push_back(tmpu);
    } else {
      if (buff == "# END") {
        fin.close();
        return ret;
      }
    }
  }
  fin.close();
  return ret;
}

void FileManage::writeMeetingsToFile(std::list<Meeting> meetings) {
  std::ofstream fout(meetingFileName_.c_str());
  fout << "# START" << std::endl;
  for (std::list<Meeting>::iterator it = meetings.begin();
       it != meetings.end(); ++it) {
    fout << "[" << std::endl;
    fout << (*it).getSponsor() << std::endl;
    fout << (*it).getParticipator() << std::endl;
    fout << Date::dateToString((*it).getStartDate()) << std::endl;
    fout << Date::dateToString((*it).getEndDate()) << std::endl;
    fout << (*it).getTitle() << std::endl;
    fout << "]" << std::endl;
  }
  fout << "# END" << std::endl;
  fout.close();
}
