#ifndef RAISE_H
#define RAISE_H

#include "statement.h"
#include <string>

class Raise : public Statement
{
public:
    std::string event;

    Raise(std::string e);

    virtual void Execute();

    virtual ~Raise() {}
};

#endif // RAISE_H
