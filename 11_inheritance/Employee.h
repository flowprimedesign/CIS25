#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "User.h"

// Derived from User
class Employee : public User {
public:
    void accessLevel() override;
};

#endif
