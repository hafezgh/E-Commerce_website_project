#ifndef __EXCEPTIONS__
#define __EXCEPTIONS__

#include <exception>
#include <string>

class NotFoundException : public std::exception {
public:
virtual const char* what() const throw () { return "Not Found"; };
};

class BadRequestException : public std::exception {
public:
virtual const char* what() const throw () { return "Bad Request"; };
};

class PermissionDeniedException : public std::exception {
public:
virtual const char* what() const throw () { return "Permission Denied"; };
};

class PasswordsDoNotMatchException : public std::exception {
public:
virtual const char* what() const throw () {return "Passwords do not match!";};
};

class EmptyFieldsException : public std::exception {
public:
virtual const char* what() const throw () {return "You did not fill one of the required fields!";};
};

class UserNameExistsException : public std::exception{
public:
virtual const char* what() const throw () {return "Username already exists!";};
};

class EmailExistsException : public std::exception{
public:
virtual const char* what() const throw () {return "Email already exists!";};
};

class IncorrectEmailOrPassException : public std::exception{
public:
virtual const char* what() const throw () {return "Incorrect email or password!";};
};

class NoOneLoggedInException : public std::exception{
public:
virtual const char* what() const throw () {return "No one is logged in!";};
};

class NotEnoughCreditException : public std::exception{
public:
virtual const char* what() const throw () {return "Not enough credit!";};
};

#endif