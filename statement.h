#ifndef STATEMENT_H
#define STATEMENT_H

class Statement
{
public:
    virtual void Execute() = 0;

    virtual ~Statement() {}
};

#endif // STATEMENT_H

