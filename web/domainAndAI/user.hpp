#ifndef __USER__
#define __USER__

#include <string>
#include <vector>

class User {
public:
    virtual std::string getUserName() = 0;
    virtual std::string getEmail() = 0;
protected:
    std::string username;
    std::string password;
    std::string email;
    int Id;
};

#endif