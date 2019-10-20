#ifndef LITERAL_H
#define LITERAL_H

#include "terminalexpression.h"
#include "data.h"

class Data;

class Literal : public TerminalExpression
{
public:
    Data *data;

    Literal(Data *d);
    virtual Data *getData();

    virtual ~Literal() {
        delete data;
    }
};

#endif // LITERAL_H
