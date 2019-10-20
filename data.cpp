#include "data.h"

Data::Data(std::string n) : name(n), type(PNULL), data(nullptr) {}

Data::Data(std::string n, int i) : name(n), type(INTEGER), data(new int(i)) {}

Data::Data(std::string n, float f) : name(n), type(FLOAT), data(new float(f)) {}

Data::Data(std::string n, std::string s) : name(n), type(STRING), data(new std::string(s)) {}

Data::Data(std::string n, bool b) : name(n), type(BOOLEAN), data(new bool(b)) {}

Data::Data(Data *v) : type(PNULL), data(nullptr)
{
    copyFrom(v);
}

Data::~Data()
{
    switch(type)
    {
    case PNULL:
        break;
    case INTEGER:
        delete static_cast<int*>(data);
        break;
    case FLOAT:
        delete static_cast<float*>(data);
        break;
    case STRING:
        delete static_cast<std::string*>(data);
        break;
    case BOOLEAN:
        delete static_cast<bool*>(data);
        break;
    }
}

int* Data::getInt() const
{
    return static_cast<int*>(data);
}

float* Data::getFloat() const
{
    return static_cast<float*>(data);
}

std::string* Data::getString() const
{
    return static_cast<std::string*>(data);
}

bool* Data::getBoolean() const
{
    return static_cast<bool*>(data);
}

void Data::createInt(int i = 0)
{
    if(type != PNULL)
        delete static_cast<int*>(data);
    data = new int(i);
}

void Data::createFloat(float f = 0.0f)
{
    if(type != PNULL)
        delete static_cast<float*>(data);
    data = new float(f);
}

void Data::createString(std::string s = "")
{
    if(type != PNULL)
        delete static_cast<std::string*>(data);
    data = new std::string(s);
}

void Data::createBoolean(bool b = false)
{
    if(type != PNULL)
        delete static_cast<bool*>(data);
    data = new bool(b);
}

void Data::copyFrom(Data *v)
{
    if(data != nullptr)
        switch(type)
        {
        case PNULL:
            break;
        case INTEGER:
            delete static_cast<int*>(data);
            break;
        case FLOAT:
            delete static_cast<float*>(data);
            break;
        case STRING:
            delete static_cast<std::string*>(data);
            break;
        case BOOLEAN:
            delete static_cast<bool*>(data);
            break;
    }
    type = v->type;
    switch(type)
    {
    case VarType::PNULL:
        data = nullptr;
        break;
    case VarType::INTEGER:
        data = new int(*(v->getInt()));
        break;
    case VarType::FLOAT:
        data = new float(*(v->getFloat()));
        break;
    case VarType::STRING:
        data = new std::string(*(v->getString()));
        break;
    case VarType::BOOLEAN:
        data = new bool(*(v->getBoolean()));
        break;
    }
}

bool Data::CastToBoolean()
{
    switch(type)
    {
    case VarType::BOOLEAN:
        return *getBoolean();
    case VarType::FLOAT:
        return *getFloat() != 0.0f;
    case VarType::INTEGER:
        return *getInt() != 0;
    case VarType::PNULL:
        return false;
    case VarType::STRING:
        return getString()->size() != 0;
    }
    return nullptr;
}
