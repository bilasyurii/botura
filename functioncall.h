#ifndef FUNCTIONCALL_H
#define FUNCTIONCALL_H

#include "statement.h"
#include <string>

class FunctionCall : public Statement
{
public:
    std::string name;

    FunctionCall(std::string n);

    virtual void Execute();

    virtual ~FunctionCall() {}
};

#endif // FUNCTIONCALL_H
