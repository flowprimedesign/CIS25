#ifndef USER_H
#define USER_H

#include <iostream>
using namespace std;

// Base class
class User {
public:
    virtual void accessLevel();
    virtual ~User() {} // Virtual destructor for proper cleanup
};

#endif
