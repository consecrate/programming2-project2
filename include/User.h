#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    int userId;
    std::string name;
    std::string email;
    std::string password;
    std::string role;

public:
    User();
    User(int userId, std::string name, std::string email, std::string password, std::string role);

    int getUserId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getRole() const;
    bool checkPassword(std::string inputPassword) const;

    virtual ~User();
};

#endif
