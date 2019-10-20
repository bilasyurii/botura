#include "variable.h"
#include "databank.h"
#include <iostream>

Variable::Variable(std::string n) : name(n) {}

Data *Variable::getData()
{
    if(bank.isDeclared(name))
        return bank.get(name);
    else
    {
        std::cout << "Variable not found: " << name << ".\n";
        throw 0;
    }
}
