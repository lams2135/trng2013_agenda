#include "User.h"

User::User() {
  name_ = "undefined";
  password_ = "123456";
  email_ = "example@abc.com";
  phone_ = "18620682135";
}

User::User(std::string userName, std::string userPassword,
           std::string userEmail, std::string userPhone) {
  name_ = userName;
  password_ = userPassword;
  email_ = userEmail;
  phone_ = userPhone;
}

bool User::isValid(void) const {
  if (userEmail)..
  if (userPhone)..
  return true;
}

void User::setName(std::string name) {
  name_ = name;
}

void User::setPassword(std::string password) {
  password_ = password;
}

void User::setEmail(std::string email) {
  email_ = email;
}

void User::setPhone(std::string phone) {
  phone_ = phone;
}

std::string User::getName() {
  return name_;
}

std::string User::getPassword() {
  return password_;
}

std::string User::getEmail() {
  return email_;
}

std::string User::getPhone() {
  return phone_;
}

