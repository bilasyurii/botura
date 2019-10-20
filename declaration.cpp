#include "declaration.h"

#include "databank.h"
#include "data.h"
#include <iostream>

Declaration::Declaration(std::string n) : name(n) {}

void Declaration::Execute()
{
    if(!bank.isDeclared(name))
        bank.declare(name, new Data(name));
    else
    {
        std::cout << "Error: " << name << " already declared.\n";
        throw 0;
    }
}
