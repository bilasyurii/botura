#ifndef VARIABLE_H
#define VARIABLE_H

#include "terminalexpression.h"
#include <string>

class Data;

class Variable : public TerminalExpression
{
public:
    std::string name;

    Variable(std::string n);
    virtual Data *getData();

    virtual ~Variable() {}
};

#endif // VARIABLE_H
