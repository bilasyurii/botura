#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <math.h>
#include "rendering.h"
#include "helper.h"

struct Token
{
    enum TokenType
    {
        IDENTIFIER,
        KEYWORD,
        NUMBER,
        FLOAT,
        STRING,
        OPERATOR,
        PUNCTUAL,
        BOOLEAN,
        PNULL
    };
    TokenType type;
    std::string data;
};

int StringToInt(std::string s)
{
    return std::stoi(s);
}

bool StringToBoolean(std::string s)
{
    if(s == "true")
        return true;
    else if(s == "false")
        return false;
    std::cout << "Error: can't convert '" << s << "' to boolean.\n";
    throw 0;
}

float StringToFloat(std::string s)
{
    return std::stof(s);
}

std::string BooleanToString(bool b)
{
    if(b)
        return "true";
    else
        return "false";
}

int BooleanToInt(bool b)
{
    if(b)
        return 1;
    else
        return 0;
}

float BooleanToFloat(bool b)
{
    if(b)
        return 1.0f;
    else
        return 0.0f;
}

std::string FloatToString(float f)
{
    return std::to_string(f);
}

bool FloatToBool(float f)
{
    if(f == 0.0)
        return false;
    else
        return true;
}

int FloatToInt(float f)
{
    return (int) f;
}

std::string IntToString(int i)
{
    return std::to_string(i);
}

float IntToFloat(int i)
{
    return (float) i;
}

bool IntToBoolean(int i)
{
    return (bool) i;
}

std::string StringMinusInt(std::string s, int n)
{
    int strSize = s.size();
    if(n >= strSize)
        return "";
    if(n == 0)
        return s;
    if(n > 0)
        return s.substr(0, strSize - n);
    else
    {
        for(int i = n; i < 0; ++i)
            s += ' ';
        return s;
    }
}

std::string IntMinusString(int n, std::string s)
{
    int strSize = s.size();
    if(n >= strSize)
        return "";
    if(n == 0)
        return s;
    if(n > 0)
        return s.substr(n, strSize - n);
    else
    {
        for(int i = n; i < 0; ++i)
            s.insert(0, " ");
        return s;
    }
}

std::string StringMinusString(std::string a, std::string b)
{
    unsigned bSize = b.size();
    for(std::string::size_type i = a.find(b); i != std::string::npos; i = a.find(b))
        a.erase(i, bSize);
    return a;
}

int findStr(std::string a, std::string b)
{
    std::string::size_type i = a.find(b);
    if(i == std::string::npos)
        return -1;
    else
        return i;
}

std::string StringMulInteger(std::string s, int n)
{
    if(n <= 0)
        return "";
    if(n == 0)
        return s;
    std::string res = "";
    for(int i = 0; i < n; ++i)
        res += s;
    return res;
}

bool Less(Data *l, Data *r)
{
    switch(l->type)
    {
    case VarType::BOOLEAN:
        {
            bool b = *(l->getBoolean());
            switch(r->type)
            {
            case VarType::BOOLEAN:
                return BooleanToInt(b) < BooleanToInt(*(r->getBoolean()));
            case VarType::FLOAT:
                return BooleanToFloat(b) < *(r->getFloat());
            case VarType::INTEGER:
                return BooleanToInt(b) < *(r->getInt());
            case VarType::PNULL:
                return false;
            case VarType::STRING:
                return BooleanToInt(b) < BooleanToInt(r->getString()->size() != 0);
            }
        }
        break;
    case VarType::FLOAT:
        {
            float f = *(l->getFloat());
            switch(r->type)
            {
            case VarType::BOOLEAN:
                return f < BooleanToFloat(*(r->getBoolean()));
            case VarType::FLOAT:
                return f < *(r->getFloat());
            case VarType::INTEGER:
                return f < ((float)*(r->getInt()));
            case VarType::PNULL:
                return false;
            case VarType::STRING:
                return f < BooleanToFloat(r->getString()->size() != 0);
            }
        }
        break;
    case VarType::INTEGER:
        {
            int i = *(l->getInt());
            switch(r->type)
            {
            case VarType::BOOLEAN:
                return i < BooleanToInt(*(r->getBoolean()));
            case VarType::FLOAT:
                return ((float) i) < *(r->getFloat());
            case VarType::INTEGER:
                return i < *(r->getInt());
            case VarType::PNULL:
                return false;
            case VarType::STRING:
                return i < BooleanToInt(r->getString()->size() != 0);
            }
        }
        break;
    case VarType::PNULL:
            return r->type != VarType::PNULL;
        break;
    case VarType::STRING:
        {
            std::string s = *(l->getString());
            switch(r->type)
            {
            case VarType::BOOLEAN:
                return BooleanToInt(s.size() != 0) < BooleanToInt(*(r->getBoolean()));
            case VarType::FLOAT:
                return BooleanToFloat(s.size() != 0) < *(r->getFloat());
            case VarType::INTEGER:
                return BooleanToInt(s.size() != 0) < *(r->getInt());
            case VarType::PNULL:
                return false;
            case VarType::STRING:
                return s.compare(*(r->getString())) < 0;
            }
        }
        break;
    }
    return false;
}

bool Greater(Data *l, Data *r)
{
    switch(l->type)
    {
    case VarType::BOOLEAN:
        {
            bool b = *(l->getBoolean());
            switch(r->type)
            {
            case VarType::BOOLEAN:
                return BooleanToInt(b) > BooleanToInt(*(r->getBoolean()));
            case VarType::FLOAT:
                return BooleanToFloat(b) > *(r->getFloat());
            case VarType::INTEGER:
                return BooleanToInt(b) > *(r->getInt());
            case VarType::PNULL:
                return true;
            case VarType::STRING:
                return BooleanToInt(b) > BooleanToInt(r->getString()->size() != 0);
            }
        }
        break;
    case VarType::FLOAT:
        {
            float f = *(l->getFloat());
            switch(r->type)
            {
            case VarType::BOOLEAN:
                return f > BooleanToFloat(*(r->getBoolean()));
            case VarType::FLOAT:
                return f > *(r->getFloat());
            case VarType::INTEGER:
                return f > ((float)*(r->getInt()));
            case VarType::PNULL:
                return true;
            case VarType::STRING:
                return f > BooleanToFloat(r->getString()->size() != 0);
            }
        }
        break;
    case VarType::INTEGER:
        {
            int i = *(l->getInt());
            switch(r->type)
            {
            case VarType::BOOLEAN:
                return i > BooleanToInt(*(r->getBoolean()));
            case VarType::FLOAT:
                return ((float) i) > *(r->getFloat());
            case VarType::INTEGER:
                return i > *(r->getInt());
            case VarType::PNULL:
                return true;
            case VarType::STRING:
                return i > BooleanToInt(r->getString()->size() != 0);
            }
        }
        break;
    case VarType::PNULL:
            return r->type != VarType::PNULL;
        break;
    case VarType::STRING:
        {
            std::string s = *(l->getString());
            switch(r->type)
            {
            case VarType::BOOLEAN:
                return BooleanToInt(s.size() != 0) > BooleanToInt(*(r->getBoolean()));
            case VarType::FLOAT:
                return BooleanToFloat(s.size() != 0) > *(r->getFloat());
            case VarType::INTEGER:
                return BooleanToInt(s.size() != 0) > *(r->getInt());
            case VarType::PNULL:
                return true;
            case VarType::STRING:
                return s.compare(*(r->getString())) > 0;
            }
        }
        break;
    }
    return false;
}

bool Equals(Data *l, Data *r)
{
    switch(l->type)
    {
    case VarType::BOOLEAN:
        {
            bool b = *(l->getBoolean());
            switch(r->type)
            {
            case VarType::BOOLEAN:
                return b == *(r->getBoolean());
            case VarType::FLOAT:
                if(b)
                    return *(r->getFloat()) == 1.0f;
                else
                    return *(r->getFloat()) == 0.0f;
            case VarType::INTEGER:
                if(b)
                    return *(r->getInt()) == 1;
                else
                    return *(r->getInt()) == 0;
            case VarType::PNULL:
                return false;
            case VarType::STRING:
                return b == (r->getString()->size() != 0);
            }
        }
        break;
    case VarType::FLOAT:
        {
            float f = *(l->getFloat());
            switch(r->type)
            {
            case VarType::BOOLEAN:
                if(*(r->getBoolean()))
                    return f == 1.0f;
                else
                    return f == 0.0f;
            case VarType::FLOAT:
                return f == *(r->getFloat());
            case VarType::INTEGER:
                return f == ((float)*(r->getInt()));
            case VarType::PNULL:
                return false;
            case VarType::STRING:
                return false;
            }
        }
        break;
    case VarType::INTEGER:
        {
            int i = *(l->getInt());
            switch(r->type)
            {
            case VarType::BOOLEAN:
                if(*(r->getBoolean()))
                    return i == 1;
                else
                    return i == 0;
            case VarType::FLOAT:
                return ((float) i) == *(r->getFloat());
            case VarType::INTEGER:
                return i == *(r->getInt());
            case VarType::PNULL:
                return false;
            case VarType::STRING:
                return false;
            }
        }
        break;
    case VarType::PNULL:
            return r->type == VarType::PNULL;
        break;
    case VarType::STRING:
        {
            std::string s = *(l->getString());
            switch(r->type)
            {
            case VarType::BOOLEAN:
                return (s.size() == 0) == *(r->getBoolean());
            case VarType::FLOAT:
                return false;
            case VarType::INTEGER:
                return false;
            case VarType::PNULL:
                return false;
            case VarType::STRING:
                return s == *(r->getString());
            }
        }
        break;
    }
    return false;
}

class Expression
{
public:
    virtual Expression *evaluate() = 0;
};

class TerminalExpression : public Expression
{
public:
    virtual Expression *evaluate()
    {
        return this;
    }

    virtual Data *getData() = 0;
};

class Literal : public TerminalExpression
{
public:
    Data *data;

    Literal(Data *d) : data(d) {}

    virtual Data *getData()
    {
        return data;
    }
};

class Variable : public TerminalExpression
{
public:
    std::string name;

    Variable(std::string n) : name(n) {}

    virtual Data *getData()
    {
        if(bank.isDeclared(name))
            return bank.get(name);
        else
        {
            std::cout << "Variable not found: " << name << ".\n";
            throw 0;
        }
    }
};

class NonTerminalExpression : public Expression
{
public:
    virtual Expression *evaluate() = 0;
};

class UnaryOperator : public NonTerminalExpression
{
public:
    Expression *expr;

    UnaryOperator(Expression *e) : expr(e) {}

    virtual Expression *evaluate() = 0;
};

class LogicalNot : public UnaryOperator
{
public:
    LogicalNot(Expression *e) : UnaryOperator(e) {}

    virtual Expression *evaluate()
    {
        Data *e = static_cast<TerminalExpression*>(expr->evaluate())->getData();
        switch(e->type)
        {
        case VarType::BOOLEAN:
            return new Literal(new Data("", !(*(e->getBoolean()))));
        case VarType::FLOAT:
            return new Literal(new Data("", *(e->getFloat()) == 0.0f));
        case VarType::INTEGER:
            return new Literal(new Data("", *(e->getInt()) == 0));
        case VarType::PNULL:
            return new Literal(new Data(""));
        case VarType::STRING:
            return new Literal(new Data("", *(e->getString()) == ""));
        }
        return nullptr;
    }
};

class UnaryMinus : public UnaryOperator
{
public:
    UnaryMinus(Expression *e) : UnaryOperator(e) {}

    virtual Expression *evaluate()
    {
        Data *e = static_cast<TerminalExpression*>(expr->evaluate())->getData();
        switch(e->type)
        {
        case VarType::BOOLEAN:
            return new Literal(new Data(""));
        case VarType::FLOAT:
            return new Literal(new Data("", -*(e->getFloat())));
        case VarType::INTEGER:
            return new Literal(new Data("", -*(e->getInt())));
        case VarType::PNULL:
            return new Literal(new Data(""));
        case VarType::STRING:
            return new Literal(new Data(""));
        }
        return nullptr;
    }
};

class BinaryOperator : public NonTerminalExpression
{
public:
    Expression *left;
    Expression *right;

    BinaryOperator(Expression *l, Expression *r) : left(l), right(r) {}

    virtual Expression *evaluate() = 0;
};

class AndOperator : public BinaryOperator
{
public:
    AndOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

    virtual Expression *evaluate()
    {
        bool l = static_cast<TerminalExpression*>(left->evaluate())->
                getData()->CastToBoolean();
        if(!l)
            return new Literal(new Data("", false));
        bool r = static_cast<TerminalExpression*>(right->evaluate())->
                getData()->CastToBoolean();
        return new Literal(new Data("", r));
    }
};

class OrOperator : public BinaryOperator
{
public:
    OrOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

    virtual Expression *evaluate()
    {
        bool l = static_cast<TerminalExpression*>(left->evaluate())->
                getData()->CastToBoolean();
        if(l)
            return new Literal(new Data("", true));
        bool r = static_cast<TerminalExpression*>(right->evaluate())->
                getData()->CastToBoolean();
        return new Literal(new Data("", r));
    }
};

class EqualsOperator : public BinaryOperator
{
public:
    EqualsOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

    virtual Expression *evaluate()
    {
        Data *l = static_cast<TerminalExpression*>(left->evaluate())->getData();
        Data *r = static_cast<TerminalExpression*>(right->evaluate())->getData();
        return new Literal(new Data("", Equals(l, r)));
    }
};

class LessThanOperator : public BinaryOperator
{
public:
    LessThanOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

    virtual Expression *evaluate()
    {
        Data *l = static_cast<TerminalExpression*>(left->evaluate())->getData();
        Data *r = static_cast<TerminalExpression*>(right->evaluate())->getData();
        return new Literal(new Data("", Less(l, r)));
    }
};

class GreaterThanOperator : public BinaryOperator
{
public:
    GreaterThanOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

    virtual Expression *evaluate()
    {
        Data *l = static_cast<TerminalExpression*>(left->evaluate())->getData();
        Data *r = static_cast<TerminalExpression*>(right->evaluate())->getData();
        return new Literal(new Data("", Greater(l, r)));
    }
};

class LessEqualsOperator : public BinaryOperator
{
public:
    LessEqualsOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

    virtual Expression *evaluate()
    {
        Data *l = static_cast<TerminalExpression*>(left->evaluate())->getData();
        Data *r = static_cast<TerminalExpression*>(right->evaluate())->getData();
        return new Literal(new Data("", Less(l, r) || Equals(l, r)));
    }
};

class GreaterEqualsOperator : public BinaryOperator
{
public:
    GreaterEqualsOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

    virtual Expression *evaluate()
    {
        Data *l = static_cast<TerminalExpression*>(left->evaluate())->getData();
        Data *r = static_cast<TerminalExpression*>(right->evaluate())->getData();
        return new Literal(new Data("", Greater(l, r) || Equals(l, r)));
    }
};

class NotEqualsOperator : public BinaryOperator
{
public:
    NotEqualsOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

    virtual Expression *evaluate()
    {
        Data *l = static_cast<TerminalExpression*>(left->evaluate())->getData();
        Data *r = static_cast<TerminalExpression*>(right->evaluate())->getData();
        return new Literal(new Data("", !Equals(l, r)));
    }
};

class PlusOperator : public BinaryOperator
{
public:
    PlusOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

    virtual Expression *evaluate()
    {
        Data *l, *r;
        l = static_cast<TerminalExpression*>(left->evaluate())->getData();
        r = static_cast<TerminalExpression*>(right->evaluate())->getData();
        Literal *res = nullptr;
        switch(l->type)
        {
        case VarType::BOOLEAN:
            switch(r->type)
            {
            case VarType::BOOLEAN:
                res = new Literal(new Data("", BooleanToInt(*(l->getBoolean())) +
                                               BooleanToInt(*(r->getBoolean()))));
                break;
            case VarType::FLOAT:
                res = new Literal(new Data("", BooleanToFloat(*(l->getBoolean())) +
                                               *(r->getFloat())));
                break;
            case VarType::STRING:
                res = new Literal(new Data("", BooleanToString(*(l->getBoolean())) +
                                               *(r->getString())));
                break;
            case VarType::INTEGER:
                res = new Literal(new Data("", BooleanToInt(*(l->getBoolean())) +
                                               *(r->getInt())));
                break;
            case VarType::PNULL:
                res = new Literal(new Data(""));
                break;
            }
            break;
        case VarType::FLOAT:
            switch(r->type)
            {
            case VarType::BOOLEAN:
                res = new Literal(new Data("", *(l->getFloat()) +
                                               BooleanToFloat(*(r->getBoolean()))));
                break;
            case VarType::FLOAT:
                res = new Literal(new Data("", *(l->getFloat()) +
                                               *(r->getFloat())));
                break;
            case VarType::STRING:
                res = new Literal(new Data("", FloatToString(*(l->getFloat())) +
                                               *(r->getString())));
                break;
            case VarType::INTEGER:
                res = new Literal(new Data("", *(l->getFloat()) +
                                               *(r->getInt())));
                break;
            case VarType::PNULL:
                res = new Literal(new Data(""));
                break;
            }
            break;
        case VarType::STRING:
            switch(r->type)
            {
            case VarType::BOOLEAN:
                res = new Literal(new Data("", *(l->getString()) +
                                               BooleanToString(*(r->getBoolean()))));
                break;
            case VarType::FLOAT:
                res = new Literal(new Data("", *(l->getString()) +
                                               FloatToString(*(r->getFloat()))));
                break;
            case VarType::STRING:
                res = new Literal(new Data("", *(l->getString()) +
                                               *(r->getString())));
                break;
            case VarType::INTEGER:
                res = new Literal(new Data("", *(l->getString()) +
                                               IntToString(*(r->getInt()))));
                break;
            case VarType::PNULL:
                res = new Literal(new Data("", *(l->getString()) +
                                               "null"));
                break;
            }
            break;
        case VarType::INTEGER:
            switch(r->type)
            {
            case VarType::BOOLEAN:
                res = new Literal(new Data("", *(l->getInt()) +
                                               BooleanToInt(*(r->getBoolean()))));
                break;
            case VarType::FLOAT:
                res = new Literal(new Data("", *(l->getInt()) +
                                               *(r->getFloat())));
                break;
            case VarType::STRING:
                res = new Literal(new Data("", IntToString(*(l->getInt())) +
                                               *(r->getString())));
                break;
            case VarType::INTEGER:
                res = new Literal(new Data("", *(l->getInt()) +
                                               *(r->getInt())));
                break;
            case VarType::PNULL:
                res = new Literal(new Data(""));
                break;
            }
            break;
        case VarType::PNULL:
            if(r->type == VarType::STRING)
                res = new Literal(new Data("", "null" + *(r->getString())));
            else
                res = new Literal(new Data(""));
            break;
        }
        return res;
    }
};

class MinusOperator : public BinaryOperator
{
public:
    MinusOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

    virtual Expression *evaluate()
    {
        Data *l, *r;
        l = static_cast<TerminalExpression*>(left->evaluate())->getData();
        r = static_cast<TerminalExpression*>(right->evaluate())->getData();
        Literal *res = nullptr;
        switch(l->type)
        {
        case VarType::BOOLEAN:
            switch(r->type)
            {
            case VarType::BOOLEAN:
                res = new Literal(new Data("", BooleanToInt(*(l->getBoolean())) -
                                               BooleanToInt(*(r->getBoolean()))));
                break;
            case VarType::FLOAT:
                res = new Literal(new Data("", BooleanToFloat(*(l->getBoolean())) -
                                               *(r->getFloat())));
                break;
            case VarType::STRING:
                res = new Literal(new Data("", IntMinusString(BooleanToInt(*(l->getBoolean())),
                                               *(r->getString()))));
                break;
            case VarType::INTEGER:
                res = new Literal(new Data("", BooleanToInt(*(l->getBoolean())) -
                                               *(r->getInt())));
                break;
            case VarType::PNULL:
                res = new Literal(new Data(""));
                break;
            }
            break;
        case VarType::FLOAT:
            switch(r->type)
            {
            case VarType::BOOLEAN:
                res = new Literal(new Data("", *(l->getFloat()) -
                                               BooleanToFloat(*(r->getBoolean()))));
                break;
            case VarType::FLOAT:
                res = new Literal(new Data("", *(l->getFloat()) -
                                               *(r->getFloat())));
                break;
            case VarType::STRING:
                res = new Literal(new Data("", IntMinusString(FloatToInt(*(l->getFloat())),
                                               *(r->getString()))));
                break;
            case VarType::INTEGER:
                res = new Literal(new Data("", *(l->getFloat()) -
                                               *(r->getInt())));
                break;
            case VarType::PNULL:
                res = new Literal(new Data(""));
                break;
            }
            break;
        case VarType::STRING:
            switch(r->type)
            {
            case VarType::BOOLEAN:
                res = new Literal(new Data("", StringMinusInt(*(l->getString()),
                                               BooleanToInt(*(r->getBoolean())))));
                break;
            case VarType::FLOAT:
                res = new Literal(new Data("", StringMinusInt(*(l->getString()),
                                               FloatToInt(*(r->getFloat())))));
                break;
            case VarType::STRING:
                res = new Literal(new Data("", StringMinusString(*(l->getString()),
                                               *(r->getString()))));
                break;
            case VarType::INTEGER:
                res = new Literal(new Data("", StringMinusInt(*(l->getString()),
                                               *(r->getInt()))));
                break;
            case VarType::PNULL:
                res = new Literal(new Data(""));
                break;
            }
            break;
        case VarType::INTEGER:
            switch(r->type)
            {
            case VarType::BOOLEAN:
                res = new Literal(new Data("", *(l->getInt()) -
                                               BooleanToInt(*(r->getBoolean()))));
                break;
            case VarType::FLOAT:
                res = new Literal(new Data("", *(l->getInt()) -
                                               *(r->getFloat())));
                break;
            case VarType::STRING:
                res = new Literal(new Data("", IntMinusString(*(l->getInt()),
                                               *(r->getString()))));
                break;
            case VarType::INTEGER:
                res = new Literal(new Data("", *(l->getInt()) -
                                               *(r->getInt())));
                break;
            case VarType::PNULL:
                res = new Literal(new Data(""));
                break;
            }
            break;
        case VarType::PNULL:
            res = new Literal(new Data(""));
            break;
        }
        return res;
    }
};

class MultiplyOperator : public BinaryOperator
{
public:
    MultiplyOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

    virtual Expression *evaluate()
    {
        Data *l, *r;
        l = static_cast<TerminalExpression*>(left->evaluate())->getData();
        r = static_cast<TerminalExpression*>(right->evaluate())->getData();
        Literal *res = nullptr;
        switch(l->type)
        {
        case VarType::BOOLEAN:
            switch(r->type)
            {
            case VarType::BOOLEAN:
                res = new Literal(new Data("", *(l->getBoolean()) &&
                                               *(r->getBoolean())));
                break;
            case VarType::FLOAT:
                res = new Literal(new Data("", BooleanToInt(*(l->getBoolean())) *
                                               *(r->getFloat())));
                break;
            case VarType::STRING:
                res = new Literal(new Data("", StringMulInteger(*(r->getString()),
                                               BooleanToInt(*(l->getBoolean())))));
                break;
            case VarType::INTEGER:
                res = new Literal(new Data("", BooleanToInt(*(l->getBoolean())) *
                                               *(r->getInt())));
                break;
            case VarType::PNULL:
                res = new Literal(new Data(""));
                break;
            }
            break;
        case VarType::FLOAT:
            switch(r->type)
            {
            case VarType::BOOLEAN:
                res = new Literal(new Data("", *(l->getFloat()) *
                                               BooleanToInt(*(r->getBoolean()))));
                break;
            case VarType::FLOAT:
                res = new Literal(new Data("", *(l->getFloat()) *
                                               *(r->getFloat())));
                break;
            case VarType::STRING:
                res = new Literal(new Data("", StringMulInteger(*(r->getString()),
                                               FloatToInt(*(l->getFloat())))));
                break;
            case VarType::INTEGER:
                res = new Literal(new Data("", *(l->getFloat()) *
                                               *(r->getInt())));
                break;
            case VarType::PNULL:
                res = new Literal(new Data(""));
                break;
            }
            break;
        case VarType::STRING:
            switch(r->type)
            {
            case VarType::BOOLEAN:
                res = new Literal(new Data("", StringMulInteger(*(l->getString()),
                                               BooleanToInt(*(r->getBoolean())))));
                break;
            case VarType::FLOAT:
                res = new Literal(new Data("", StringMulInteger(*(l->getString()),
                                               FloatToInt(*(r->getFloat())))));
                break;
            case VarType::STRING:
                res = new Literal(new Data("", findStr(*(l->getString()),
                                               *(r->getString()))));
                break;
            case VarType::INTEGER:
                res = new Literal(new Data("", StringMulInteger(*(l->getString()),
                                               *(r->getInt()))));
                break;
            case VarType::PNULL:
                res = new Literal(new Data(""));
                break;
            }
            break;
        case VarType::INTEGER:
            switch(r->type)
            {
            case VarType::BOOLEAN:
                res = new Literal(new Data("", *(l->getInt()) *
                                               BooleanToInt(*(r->getBoolean()))));
                break;
            case VarType::FLOAT:
                res = new Literal(new Data("", *(l->getInt()) *
                                               *(r->getFloat())));
                break;
            case VarType::STRING:
                res = new Literal(new Data("", StringMulInteger(*(r->getString()),
                                               *(l->getInt()))));
                break;
            case VarType::INTEGER:
                res = new Literal(new Data("", *(l->getInt()) *
                                               *(r->getInt())));
                break;
            case VarType::PNULL:
                res = new Literal(new Data(""));
                break;
            }
            break;
        case VarType::PNULL:
            res = new Literal(new Data(""));
            break;
        }
        return res;
    }
};

class DivideOperator : public BinaryOperator
{
public:
    DivideOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

    virtual Expression *evaluate()
    {
        Data *l, *r;
        l = static_cast<TerminalExpression*>(left->evaluate())->getData();
        r = static_cast<TerminalExpression*>(right->evaluate())->getData();
        Literal *res = nullptr;
        switch(l->type)
        {
        case VarType::BOOLEAN:
            switch(r->type)
            {
            case VarType::BOOLEAN:
                res = new Literal(new Data(""));
                break;
            case VarType::FLOAT:
                res = new Literal(new Data(""));
                break;
            case VarType::STRING:
                res = new Literal(new Data(""));
                break;
            case VarType::INTEGER:
                res = new Literal(new Data(""));
                break;
            case VarType::PNULL:
                res = new Literal(new Data(""));
                break;
            }
            break;
        case VarType::FLOAT:
            switch(r->type)
            {
            case VarType::BOOLEAN:
                res = new Literal(new Data(""));
                break;
            case VarType::FLOAT:
                if(*(r->getFloat()) == 0.0f)
                    res = new Literal(new Data(""));
                else
                    res = new Literal(new Data("", *(l->getFloat()) /
                                                   *(r->getFloat())));
                break;
            case VarType::STRING:
                res = new Literal(new Data(""));
                break;
            case VarType::INTEGER:
                if(*(r->getInt()) == 0)
                    res = new Literal(new Data(""));
                else
                    res = new Literal(new Data("", *(l->getFloat()) /
                                                   *(r->getInt())));
                break;
            case VarType::PNULL:
                res = new Literal(new Data(""));
                break;
            }
            break;
        case VarType::STRING:
            switch(r->type)
            {
            case VarType::BOOLEAN:
                res = new Literal(new Data(""));
                break;
            case VarType::FLOAT:
                res = new Literal(new Data(""));
                break;
            case VarType::STRING:
                res = new Literal(new Data(""));
                break;
            case VarType::INTEGER:
                res = new Literal(new Data(""));
                break;
            case VarType::PNULL:
                res = new Literal(new Data(""));
                break;
            }
            break;
        case VarType::INTEGER:
            switch(r->type)
            {
            case VarType::BOOLEAN:
                res = new Literal(new Data(""));
                break;
            case VarType::FLOAT:
                if(*(r->getFloat()) == 0.0f)
                    res = new Literal(new Data(""));
                else
                    res = new Literal(new Data("", *(l->getInt()) /
                                                   *(r->getFloat())));
                break;
            case VarType::STRING:
                res = new Literal(new Data(""));
                break;
            case VarType::INTEGER:
                if(*(r->getInt()) == 0)
                    res = new Literal(new Data(""));
                else
                    res = new Literal(new Data("", *(l->getInt()) /
                                                   *(r->getInt())));
                break;
            case VarType::PNULL:
                res = new Literal(new Data(""));
                break;
            }
            break;
        case VarType::PNULL:
            res = new Literal(new Data(""));
            break;
        }
        return res;
    }
};

class ModuloOperator : public BinaryOperator
{
public:
    ModuloOperator(Expression *l, Expression *r) : BinaryOperator(l, r) {}

    virtual Expression *evaluate()
    {
        Data *l, *r;
        l = static_cast<TerminalExpression*>(left->evaluate())->getData();
        r = static_cast<TerminalExpression*>(right->evaluate())->getData();
        Literal *res = nullptr;
        switch(l->type)
        {
        case VarType::BOOLEAN:
            res = new Literal(new Data(""));
            break;
        case VarType::FLOAT:
            switch(r->type)
            {
            case VarType::BOOLEAN:
                res = new Literal(new Data(""));
                break;
            case VarType::FLOAT:
                res = new Literal(new Data("", (float) fmod(*(l->getFloat()),
                                                            *(r->getFloat()))));
                break;
            case VarType::STRING:
                res = new Literal(new Data(""));
                break;
            case VarType::INTEGER:
                res = new Literal(new Data("", (float) fmod(*(l->getFloat()),
                                                            *(r->getInt()))));
                break;
            case VarType::PNULL:
                res = new Literal(new Data(""));
                break;
            }
            break;
        case VarType::STRING:
            res = new Literal(new Data(""));
            break;
        case VarType::INTEGER:
            switch(r->type)
            {
            case VarType::BOOLEAN:
                res = new Literal(new Data(""));
                break;
            case VarType::FLOAT:
                if(*(r->getFloat()) == 0.0f)
                    res = new Literal(new Data(""));
                else
                    res = new Literal(new Data("", (float) fmod(*(l->getInt()),
                                                                *(r->getFloat()))));
                break;
            case VarType::STRING:
                res = new Literal(new Data(""));
                break;
            case VarType::INTEGER:
                res = new Literal(new Data("", *(l->getInt()) %
                                               *(r->getInt())));
                break;
            case VarType::PNULL:
                res = new Literal(new Data(""));
                break;
            }
            break;
        case VarType::PNULL:
            res = new Literal(new Data(""));
            break;
        }
        return res;
    }
};

class Condition : public Statement
{
public:
    Expression *exp;
    Statement *positive;
    Statement *negative;

    virtual void Execute()
    {
        bool result = static_cast<TerminalExpression*>(exp->evaluate())->
                getData()->CastToBoolean();
        if(result)
            positive->Execute();
        else
            negative->Execute();
    }
};

class WhileLoop : public Statement
{
public:
    Expression *exp;
    Statement *action;

    virtual void Execute()
    {
        bool result;
        while(true)
        {
            result = static_cast<TerminalExpression*>(exp->evaluate())->
                getData()->CastToBoolean();
            if(!result)
                return;
            action->Execute();
        }
    }
};

class Assignment : public Statement
{
public:
    Expression *left;
    Expression *right;

    Assignment(Expression *l, Expression *r) : left(l), right(r) {}

    virtual void Execute()
    {
        std::string name = static_cast<Variable*>(left)->getData()->name;
        TerminalExpression *result = static_cast<TerminalExpression*>(right->evaluate());
        bank.get(name)->copyFrom(result->getData());
    }
};
//TODO scope creation and deleting
class Declaration : public Statement
{
public:
    std::string name;

    Declaration(std::string n) : name(n) {}

    virtual void Execute()
    {
        if(!bank.isDeclared(name))
            bank.declare(name, new Data(name));
        else
        {
            std::cout << "Error: " << name << " already declared.\n";
            throw 0;
        }
    }
};

class Initialization : public Declaration
{
public:
    Expression *exp;

    Initialization(std::string n, Expression *e) : Declaration(n), exp(e) {}

    virtual void Execute()
    {
        Declaration::Execute();
        TerminalExpression *result = static_cast<TerminalExpression*>(exp->evaluate());
        bank.get(name)->copyFrom(result->getData());
    }
};

class Print : public Statement
{
public:
    Expression *exp;

    Print(Expression *e) : exp(e) {}

    virtual void Execute()
    {
        Data *d = static_cast<TerminalExpression*>(exp->evaluate())->getData();
        switch(d->type)
        {
        case VarType::PNULL:
            std::cout << "null";
            break;
        case VarType::INTEGER:
            std::cout << *(d->getInt());
            break;
        case VarType::FLOAT:
            std::cout << *(d->getFloat());
            break;
        case VarType::STRING:
            std::cout << *(d->getString());
            break;
        case VarType::BOOLEAN:
            std::cout << BooleanToString(*(d->getBoolean()));
            break;
        }
    }
};

class BotControl : public Statement
{
public:
    static World *world;
    World::Action action;

    BotControl(World::Action a) : action(a) {}

    virtual void Execute()
    {
        world->actionSlot = action;
        world->used = false;
        world->mutex.unlock();
        do
        {
            sf::sleep(sf::microseconds(10));
            world->mutex.lock();
            if(world->used)
                break;
            world->mutex.unlock();
        } while(true);
        for(unsigned i = 0; i < world->events.size(); ++i)
            bank.raiseEvent(world->events[i]);
    }
};

World *BotControl::world;

class ScopeControl : public Statement
{
public:
    enum ScopeAction
    {
        CREATE,
        DELETE
    };
    ScopeAction action;
    ScopeControl(ScopeAction a) : action(a) {}

    virtual void Execute()
    {
        switch(action)
        {
        case CREATE:
            bank.newScope();
            break;
        case DELETE:
            bank.deleteScope();
            break;
        }
    }
};

class FunctionCall : public Statement
{
public:
    std::string name;

    FunctionCall(std::string n) : name(n) {}

    virtual void Execute()
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
};

class Raise : public Statement
{
public:
    std::string event;

    Raise(std::string e) : event(e) {}

    virtual void Execute()
    {
        bank.raiseEvent(event);
    }
};

inline bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool isLetter(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool isOperator(char c)
{
    return c == '=' || c == '!' ||
           c == '<' || c == '>' ||
           c == '+' || c == '-' ||
           c == '*' || c == '/' ||
           c == '&' || c == '|' ||
           c == '%';
}

bool isPunctual(char c)
{
    return c == '(' || c == ')' ||
           c == '{' || c == '}' ||
           c == ';';
}

class Parser
{
    unsigned current;
    unsigned size;
    unsigned braceCount;
    void splitToTokens(std::string str);
    World &world;
    sf::Mutex &mutex;
    StatementList *parseToTree();
    Expression *parseExpression();
    Statement *parseSingleCommand();
    Condition *parseIf();
    WhileLoop *parseWhile();
    BotControl *parseMove();
    BotControl *parseTurnLeft();
    BotControl *parseTurnRight();
    BotControl *parseJump();
    BotControl *parseStand();
    Statement *parseVar();
    Print *parsePrint();
    Raise *parseRaise();
    void parseFunction();
    unsigned getPrecedence(std::string op) const;
    void addNodeToTree(std::vector<Expression*> &tree, std::string op);
    void checkToken(Token t);
public:
    std::vector<Token> tokens;
    StatementList *first;
    Parser(World &w);
    void analyse(std::string str);
    void Execute();
};

Parser::Parser(World &w) : world(w), mutex(w.mutex)
{
    world.mutex.lock();
}

void Parser::Execute()
{
    try
    {
        first->Execute();
    }
    catch(...)
    {
        std::cout << "\nThere were errors during execution.\n";
    }
    world.actionSlot = World::END;
    world.mutex.unlock();
}

void Parser::analyse(std::string str)
{
    current = 0;
    splitToTokens(str);
    size = tokens.size();
    first = parseToTree();
    first->statements.push_back(new Raise("END"));
}

unsigned Parser::getPrecedence(std::string op) const
{
    if(op == "u-" || op == "!")
        return 0;
    if(op == "*" || op == "/" || op == "%")
        return 1;
    if(op == "+" || op == "-")
        return 2;
    if(op == "<" || op == ">" || op == "<=" || op == ">=")
        return 3;
    if(op == "==" || op == "!=")
        return 4;
    if(op == "&&")
        return 5;
    if(op == "||")
        return 6;
    if(op == "=")
        return 7;
    return 99;
}

void Parser::addNodeToTree(std::vector<Expression*>& tree, std::string op)
{
    Expression *one, *two, *result;
    if(op == "+")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new PlusOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "-")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new MinusOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "*")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new MultiplyOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "/")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new DivideOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "%")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new ModuloOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "&&")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new AndOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "||")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new OrOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "==")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new EqualsOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "<")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new LessThanOperator(one, two);
        tree.push_back(result);
    }
    else if(op == ">")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new GreaterThanOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "!=")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new NotEqualsOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "<=")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new LessEqualsOperator(one, two);
        tree.push_back(result);
    }
    else if(op == ">=")
    {
        two = tree.back();
        tree.pop_back();
        one = tree.back();
        tree.pop_back();
        result = new GreaterEqualsOperator(one, two);
        tree.push_back(result);
    }
    else if(op == "!")
    {
        one = tree.back();
        tree.pop_back();
        result = new LogicalNot(one);
        tree.push_back(result);
    }
    else if(op == "u-")
    {
        one = tree.back();
        tree.pop_back();
        result = new UnaryMinus(one);
        tree.push_back(result);
    }
}

Expression *Parser::parseExpression()
{
    Token token;
    std::vector<Expression*> tree;
    std::vector<std::string> operators;
    unsigned parenthesesCount = 0;
    bool possibleUnaryMinus = true;
    while(current < size)
    {
        token = tokens[current];
        if(token.type == Token::OPERATOR)
        {
            if(possibleUnaryMinus && token.data == "-")
            {
                possibleUnaryMinus = false;
                token.data = "u-";
            }
            else
                possibleUnaryMinus = true;
            while(!operators.empty())
            {
                if(operators.back() != "(" && getPrecedence(token.data) >=
                                              getPrecedence(operators.back()))
                {
                    addNodeToTree(tree, operators.back());
                    operators.pop_back();
                }
                else
                    break;
            }
            operators.push_back(token.data);
        }
        else if(token.type == Token::PUNCTUAL)
        {
            if(token.data == ";")
            {
                while(!operators.empty())
                {
                    addNodeToTree(tree, operators.back());
                    operators.pop_back();
                }
                return tree[0];
            }
            else if(token.data == "(")
            {
                operators.push_back(token.data);
                ++parenthesesCount;
                possibleUnaryMinus = true;
            }
            else if(token.data == ")")
            {
                if(parenthesesCount == 0)
                {
                    while(!operators.empty())
                    {
                        addNodeToTree(tree, operators.back());
                        operators.pop_back();
                    }
                    return tree[0];
                }
                --parenthesesCount;
                possibleUnaryMinus = false;
                while(operators.back() != "(")
                {
                    addNodeToTree(tree, operators.back());
                    operators.pop_back();
                }
                operators.pop_back();
            }
        }
        else
        {
            if(token.type == Token::IDENTIFIER)
                tree.push_back(new Variable(token.data));
            else if(token.type == Token::NUMBER)
                tree.push_back(new Literal(new Data("", StringToInt(token.data))));
            else if(token.type == Token::BOOLEAN)
                tree.push_back(new Literal(new Data("", StringToBoolean(token.data))));
            else if(token.type == Token::FLOAT)
                tree.push_back(new Literal(new Data("", StringToFloat(token.data))));
            else if(token.type == Token::STRING)
                tree.push_back(new Literal(new Data("", token.data)));
            else if(token.type == Token::PNULL)
                tree.push_back(new Literal(new Data("")));
            else
            {
                std::cout << "Error: not expected keyword.\n";
                throw 0;
            }
            possibleUnaryMinus = false;
        }
        ++current;
    }
    std::cout << "Error: not expected end of file.\n";
    throw 0;
}

void Parser::checkToken(Token t)
{
    Token token = tokens[current];
    if(token.type == t.type && token.data == t.data)
        ++current;
    else
    {
        std::cout << "Error: '" << t.data << "' expected.\n";
        throw 0;
    }
}

Statement *Parser::parseVar()
{
    ++current;
    Token name = tokens[current];
    if(name.type != Token::IDENTIFIER)
    {
        std::cout << "Error: identifier expected.\n";
        throw 0;
    }
    if(bank.isDeclared(name.data))
    {
        std::cout << "Error: redeclaration of" << name.data << ".\n";
        throw 0;
    }
    ++current;
    Token nextToken = tokens[current];
    if(nextToken.type == Token::PUNCTUAL && nextToken.data == ";")
    {
        ++current;
        return new Declaration(name.data);
    }
    else if(nextToken.type == Token::OPERATOR && nextToken.data == "=")
    {
        Statement *stat = new Initialization(name.data, parseExpression());
        checkToken(Token { Token::PUNCTUAL, ";" });
        return stat;
    }
    else
    {
        std::cout << "Error: expected '=' or ';' after declaration.\n";
        throw 0;
    }
}

Print *Parser::parsePrint()
{
    ++current;
    checkToken(Token { Token::PUNCTUAL, "(" });
    Print *statement = new Print(parseExpression());
    checkToken(Token { Token::PUNCTUAL, ")" });
    checkToken(Token { Token::PUNCTUAL, ";" });
    return statement;
}

Raise *Parser::parseRaise()
{
    ++current;
    checkToken(Token { Token::PUNCTUAL, "(" });
    Token token = tokens[current];
    if(token.type != Token::IDENTIFIER)
    {
        std::cout << "Error: event identifier expected after keyword 'raise'.\n";
        throw 0;
    }
    Raise *raise = new Raise(token.data);
    ++current;
    checkToken(Token { Token::PUNCTUAL, ")" });
    checkToken(Token { Token::PUNCTUAL, ";" });
    return raise;
}

void Parser::parseFunction()
{
    ++current;
    Token token = tokens[current];
    if(token.type != Token::IDENTIFIER)
    {
        std::cout << "Error: identifier expected after keyword 'function'.\n";
        throw 0;
    }
    ++current;
    Token tok = tokens[current];
    Function *func;
    if(tok.type == Token::PUNCTUAL && tok.data == "{")
    {
        ++braceCount;
        ++current;
        if(bank.isFunctionDeclared(token.data))
        {
            std::cout << "Error: function " << token.data << " was already declared.\n";
            throw 0;
        }
        func = new Function(token.data, parseToTree());
    }
    else if(tok.type == Token::KEYWORD && tok.data == "listen")
    {
        ++current;
        tok = tokens[current];
        if(tok.type != Token::IDENTIFIER)
        {
            std::cout << "Error: event identifier expected after keyword 'listen'.\n";
            throw 0;
        }
        ++current;
        checkToken(Token { Token::PUNCTUAL, "{" });
        ++braceCount;
        if(bank.isFunctionDeclared(token.data))
        {
            std::cout << "Error: function " << token.data << " was already declared.\n";
            throw 0;
        }
        func = new Function(token.data, parseToTree());
        if(!bank.isEventDeclared(tok.data))
            bank.declare(tok.data, new Event);
        bank.getEvent(tok.data)->listeners.push_back(func);    }
    bank.declare(token.data, func);
}

Statement *Parser::parseSingleCommand()
{
    Token token;
    Statement *statement = nullptr;
    token = tokens[current];
    switch(token.type)
    {
    case Token::IDENTIFIER:
        {
            ++current;
            Token tok = tokens[current];
            if(tok.type == Token::OPERATOR)
            {
                if(tok.data == "=")
                {
                    ++current;
                    //TODO check if variable is created already;
                    statement = new Assignment(new Variable(token.data),
                                               parseExpression());
                    checkToken(Token { Token::PUNCTUAL, ";" });
                }
                else
                {
                    std::cout << "Error: operator expected.\n";
                    throw 0;
                }
            }
            else if(tok.type == Token::PUNCTUAL && tok.data == "(")
            {
                ++current;
                checkToken(Token { Token::PUNCTUAL, ")" });
                checkToken(Token { Token::PUNCTUAL, ";" });
                statement = new FunctionCall(token.data);
            }
            else
            {
                std::cout << "Error: operator expected.\n";
                throw 0;
            }
            break;
        }
    case Token::KEYWORD:
        {
            if(token.data == "var")
            {
                std::cout << "Error: single command can't be declaration or initialization.\n";
                throw 0;
            }//TODO forbid to create functions not in global scope
            else if(token.data == "if")
                statement = parseIf();
            else if(token.data == "while")
                statement = parseWhile();
            else if(token.data == "move")
                statement = parseMove();
            else if(token.data == "turnLeft")
                statement = parseTurnLeft();
            else if(token.data == "turnRight")
                statement = parseTurnRight();
            else if(token.data == "jump")
                statement = parseJump();
            else if(token.data == "stand")
                statement = parseStand();
            else if(token.data == "print")
                statement = parsePrint();
            else if(token.data == "raise")
                statement = parseRaise();
            break;
        }
    default:
        {
            std::cout << "Error: identifier or keyword expected.\n";
            throw 0;
        }
    }
    return statement;
}

Condition *Parser::parseIf()
{
    ++current;
    checkToken(Token { Token::PUNCTUAL, "(" });
    Condition *condition = new Condition;
    condition->exp = parseExpression();
    checkToken(Token { Token::PUNCTUAL, ")" });
    Token token = tokens[current];
    if(token.type == Token::PUNCTUAL && token.data == "{")
    {
        ++current;
        ++braceCount;
        condition->positive = parseToTree();
    }
    else
        condition->positive = parseSingleCommand();
    token = tokens[current];
    if(token.type == Token::KEYWORD && token.data == "else")
    {
        ++current;
        token = tokens[current];
        if(token.type == Token::PUNCTUAL && token.data == "{")
        {
            ++current;
            ++braceCount;
            condition->negative = parseToTree();
        }
        else
            condition->negative = parseSingleCommand();
    }
    return condition;
}

WhileLoop *Parser::parseWhile()
{
    ++current;
    checkToken(Token { Token::PUNCTUAL, "(" });
    WhileLoop *loop = new WhileLoop;
    loop->exp = parseExpression();
    checkToken(Token { Token::PUNCTUAL, ")" });
    Token token = tokens[current];
    if(token.type == Token::PUNCTUAL && token.data == "{")
    {
        ++current;
        ++braceCount;
        loop->action = parseToTree();
    }
    else
        loop->action = parseSingleCommand();
    return loop;
}

BotControl *Parser::parseMove()
{
    ++current;
    checkToken(Token { Token::PUNCTUAL, "(" });
    checkToken(Token { Token::PUNCTUAL, ")" });
    checkToken(Token { Token::PUNCTUAL, ";" });
    return new BotControl(World::MOVE);
}

BotControl *Parser::parseTurnLeft()
{
    ++current;
    checkToken(Token { Token::PUNCTUAL, "(" });
    checkToken(Token { Token::PUNCTUAL, ")" });
    checkToken(Token { Token::PUNCTUAL, ";" });
    return new BotControl(World::TURN_LEFT);
}

BotControl *Parser::parseTurnRight()
{
    ++current;
    checkToken(Token { Token::PUNCTUAL, "(" });
    checkToken(Token { Token::PUNCTUAL, ")" });
    checkToken(Token { Token::PUNCTUAL, ";" });
    return new BotControl(World::TURN_RIGHT);
}

BotControl *Parser::parseJump()
{
    ++current;
    checkToken(Token { Token::PUNCTUAL, "(" });
    checkToken(Token { Token::PUNCTUAL, ")" });
    checkToken(Token { Token::PUNCTUAL, ";" });
    return new BotControl(World::JUMP);
}

BotControl *Parser::parseStand()
{
    ++current;
    checkToken(Token { Token::PUNCTUAL, "(" });
    checkToken(Token { Token::PUNCTUAL, ")" });
    checkToken(Token { Token::PUNCTUAL, ";" });
    return new BotControl(World::STAND);
}

StatementList *Parser::parseToTree()
{
    Token token;
    StatementList *statements = new StatementList;
    bool scopeCreated = false;
    while(current < size)
    {
        token = tokens[current];
        switch(token.type)
        {
        case Token::IDENTIFIER:
            {
                statements->statements.push_back(parseSingleCommand());
                break;
            }
        case Token::KEYWORD:
            {
                if(token.data == "var")
                {
                    if(!scopeCreated)
                    {
                        statements->statements.push_back(
                            new ScopeControl(ScopeControl::CREATE));
                        scopeCreated = true;
                    }
                    statements->statements.push_back(parseVar());
                }
                else if(token.data == "if")
                    statements->statements.push_back(parseIf());
                else if(token.data == "while")
                    statements->statements.push_back(parseWhile());
                else if(token.data == "print")
                    statements->statements.push_back(parsePrint());
                else if(token.data == "move")
                    statements->statements.push_back(parseMove());
                else if(token.data == "turnLeft")
                    statements->statements.push_back(parseTurnLeft());
                else if(token.data == "turnRight")
                    statements->statements.push_back(parseTurnRight());
                else if(token.data == "jump")
                    statements->statements.push_back(parseJump());
                else if(token.data == "stand")
                    statements->statements.push_back(parseStand());
                else if(token.data == "function")
                    parseFunction();
                else if(token.data == "raise")
                    statements->statements.push_back(parseRaise());
                break;
            }
        case Token::PUNCTUAL:
            {
                if(token.data == "}")
                {
                    if(braceCount == 0)
                    {
                        std::cout << "Error: not expected '}'.\n";
                        throw 0;
                    }
                    else
                    {
                        --braceCount;
                        ++current;
                        if(scopeCreated)
                            statements->statements.push_back(
                                new ScopeControl(ScopeControl::DELETE));
                        return statements;
                    }
                }
                break;
            }
        default:
            {
                std::cout << "Error: identifier or keyword expected.\n";
                throw 0;
            }
        }
    }
    if(scopeCreated)
        statements->statements.push_back(
            new ScopeControl(ScopeControl::DELETE));
    return statements;
}

void Parser::splitToTokens(std::string str)
{
    char symbol;
    std::string token;
    unsigned i = 0;
    bool isFirstDot;
    unsigned strSize = str.size();
    while(i < strSize)
    {
        symbol = str[i];
        token = symbol;
        if(symbol == ' ' || symbol == '\t')
        {
            ++i;
        }
        else if(isDigit(symbol))
        {
            ++i;
            isFirstDot = true;
            while(i < strSize)
            {
                symbol = str[i];
                if(isDigit(symbol) || symbol == '.')
                {
                    token += symbol;
                    if(symbol == '.')
                    {
                        if(isFirstDot)
                            isFirstDot = false;
                        else
                        {
                            std::cout << "Error: not expected '.'.\n";
                            throw 0;
                        }
                    }
                    else if(token[0] == '0' && token[1] == '0')
                    {
                        std::cout << "Error: not expected '0'.\n";
                        throw 0;
                    }
                }
                else if(symbol == ' ' || symbol == '\t' || isOperator(symbol) || isPunctual(symbol))
                {
                    if(token.back() == '.')
                    {
                        std::cout << "Error: float can't have a dot in the end.\n";
                        throw 0;
                    }
                    if(isFirstDot)
                        tokens.push_back(Token { Token::NUMBER, token });
                    else
                        tokens.push_back(Token { Token::FLOAT, token });
                    break;
                }
                else
                {
                    std::cout << "Error: not expected symbol '" << symbol << "'.\n";
                    throw 0;
                }
                ++i;
            }
        }
        else if(isLetter(symbol))
        {
            ++i;
            while(i < strSize)
            {
                symbol = str[i];
                if(isLetter(symbol) || isDigit(symbol))
                    token += symbol;
                else
                {
                    if(token == "var" || token == "if" ||
                       token == "while" || token == "break" ||
                       token == "continue" || token == "return" ||
                       token == "function" || token == "print" ||
                       token == "else" || token == "stand" ||
                       token == "move" || token == "turnLeft" ||
                       token == "turnRight" || token == "jump" ||
                       token == "listen" || token == "raise")
                        tokens.push_back(Token { Token::KEYWORD, token });
                    else if(token == "true" || token == "false")
                        tokens.push_back(Token { Token::BOOLEAN, token});
                    else if(token == "null")
                        tokens.push_back(Token { Token::PNULL, ""});
                    else
                        tokens.push_back(Token { Token::IDENTIFIER, token });
                    break;
                }
                ++i;
            }
        }
        else if(isPunctual(symbol))
        {
            tokens.push_back(Token { Token::PUNCTUAL, token });
            ++i;
        }
        else if(isOperator(symbol))
        {
            ++i;
            symbol = str[i];
            if(token == "/" && symbol == '*')
            {
                i+=2;
                while(i < strSize)
                {
                    if(str[i] == '/' && str[i - 1] == '*')
                        break;
                    else
                        ++i;
                }
                if(i < strSize)
                    ++i;
                else
                {
                    std::cout << "Error: not found end of comment.\n";
                    throw 0;
                }
            }
            else if(isOperator(symbol))
            {
                token += symbol;
                if(token == "==" || token == "!=" ||
                   token == "<=" || token == ">=" ||
                   token == "+=" || token == "-=" ||
                   token == "*=" || token == "/=" ||
                   token == "&&" || token == "||")
                {
                    tokens.push_back(Token { Token::OPERATOR, token });
                    ++i;
                }
                else
                {
                    token.pop_back();
                    tokens.push_back(Token { Token::OPERATOR, token });
                }
            }
            else if(token != "&" && token != "|")
                tokens.push_back(Token { Token::OPERATOR, token });
        }
        else if(symbol == '\"')
        {
            ++i;
            token = "";
            while(i < strSize)
            {
                symbol = str[i];
                if(symbol == '\"')
                {
                    ++i;
                    tokens.push_back(Token { Token::STRING, token });
                    break;
                }
                else if(symbol == '\\')
                {
                    ++i;
                    symbol = str[i];
                    switch(symbol)
                    {
                    case 'n':
                        token += '\n';
                        break;
                    case '\\':
                        token += '\\';
                        break;
                    case 't':
                        token += '\t';
                        break;
                    case '\"':
                        token += '\"';
                        break;
                    }
                    ++i;
                }
                else
                {
                    token += symbol;
                    ++i;
                }
            }
        }
        else
        {
            std::cout << "Error: not expected '" << symbol << "'.\n";
            throw 0;
        }
    }
}

std::string readFromFile(std::string path)
{
    std::ifstream fin;
    fin.open(path);
    std::string temp, code;
    bool empty = true;
    while(std::getline(fin, temp))
    {
        if(empty)
            empty = false;
        else
            code += " ";
        code += temp;
    }
    fin.close();
    return code;
}

int main()
{
    std::string code = readFromFile("in.txt");
    sf::Mutex mutex;
    World w;
    w.loadFromFile("res/01.btr");
    Renderer r(w);
    Parser parser(w);
    BotControl::world = &w;
    try
    {
        parser.analyse(code);
    }
    catch(...)
    {
        std::cout << "\nThere were errors during parsing.\n";
        return 0;
    }
    sf::Thread renderThread(&Renderer::loop, &r);
    renderThread.launch();
    sf::Thread parserThread(&Parser::Execute, &parser);
    parserThread.launch();
    parserThread.wait();
    renderThread.wait();
    return 0;
}
