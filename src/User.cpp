#include "User.h"

User::User() : userId(0), name(""), email(""), password(""), role("") {}

User::User(int userId, std::string name, std::string email, std::string password, std::string role)
    : userId(userId), name(name), email(email), password(password), role(role) {}

int User::getUserId() const { return userId; }
std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }
std::string User::getPassword() const { return password; }
std::string User::getRole() const { return role; }
bool User::checkPassword(std::string inputPassword) const { return password == inputPassword; }
User::~User() {}