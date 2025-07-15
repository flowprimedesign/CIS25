#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include "Employee.h"

// Derived from Employee
class InventoryManager : public Employee {
public:
    void accessLevel() override;
};

#endif
