#ifndef DECLARATION_H
#define DECLARATION_H

#include <string>
#include "statement.h"

class Declaration : public Statement
{
public:
    std::string name;

    Declaration(std::string n);

    virtual void Execute();

    virtual ~Declaration() {}
};

#endif // DECLARATION_H
