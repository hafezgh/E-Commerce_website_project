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

#endif