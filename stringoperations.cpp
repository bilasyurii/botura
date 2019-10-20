#include "stringoperations.h"
#include "data.h"
#include <iostream>

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

bool isDigit(char c)
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
