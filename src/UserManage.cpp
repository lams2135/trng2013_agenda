#include "UserManage.h"
#include <iostream>
#include <cstdlib>

bool UserManage::instanceFlag_ = false;
UserManage* UserManage::instance_ = 0;

UserManage::UserManage() {
  instanceFlag_ = true;
}

UserManage::~UserManage() {
  instanceFlag_ = false;
  instance_ = NULL;
}

UserManage *UserManage::getInstance() {
  if (!instanceFlag_)
  instance_ = new UserManage();
  return instance_;
}

void UserManage::initUsersList(std::list<User> users) {
  users_.clear();
  std::list<User>::iterator iter;
  for (iter = users.begin();
      iter != users.end(); iter++ )
           users_.push_back(*iter);
}

std::list<User> UserManage::acquireUsersList() {
  return users_;
}

User* UserManage::findUserByName(std::string userName) {
  for (std::list<User>::iterator iter = users_.begin();
      iter != users_.end(); iter++)
    if ((*iter).getName() == userName)
      return &(*iter);
  return 0;
}

bool UserManage::createUser(std::string userName, std::string userPassword,
                  std::string userEmail,
                  std::string userPhone) {
  for (std::list<User>::iterator iter = users_.begin();
       iter != users_.end(); iter++)
    if ((*iter).getName() == userName)
      return false;
  User tmp(userName, userPassword, userEmail, userPhone);
  users_.push_back(tmp);
  return true;
}

bool UserManage::deleteUser(User user) {
  for (std::list<User>::iterator iter = users_.begin();
       iter != users_.end(); iter++)
    if ((*iter).getName() == user.getName()) {
      users_.erase(iter);
      return true;
    }
  return false;
}

bool UserManage::updateUserPassword(User user, std::string newPassword) {
  for (std::list<User>::iterator iter = users_.begin();
       iter != users_.end(); iter++)
    if ((*iter).getName() == user.getName()) {
      (*iter).setPassword(newPassword);
      return true;
    }
  return false;
}

bool UserManage::updateUserEmail(User user, std::string newEmail) {
  for (std::list<User>::iterator iter = users_.begin();
       iter != users_.end(); iter++)
    if ((*iter).getName() == user.getName()) {
      (*iter).setEmail(newEmail);
      return true;
    }
  return false;
}
bool UserManage::updateUserPhone(User user, std::string newPhone) {
  for (std::list<User>::iterator iter = users_.begin();
       iter != users_.end(); iter++)
    if ((*iter).getName() == user.getName()) {
      (*iter).setPhone(newPhone);
      return true;
    }
  return false;
}

std::list<User> UserManage::listAllUsers() {
  return users_;
}

