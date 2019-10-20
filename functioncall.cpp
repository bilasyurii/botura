#include "functioncall.h"

#include "function.h"
#include "databank.h"
#include <iostream>

FunctionCall::FunctionCall(std::string n) : name(n) {}

void FunctionCall::Execute()
{
    if(bank.isFunctionDeclared(name))
    {
        bank.getFunction(name)->Execute();
    }
    else
    {
        std::cout << "Error: function '" << name << "' was not declared.\n";
        throw 0;
    }
}
