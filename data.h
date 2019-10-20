#ifndef DATA_H
#define DATA_H

#include <string>

enum VarType
{
    PNULL,
    INTEGER,
    FLOAT,
    STRING,
    BOOLEAN
};

class Data
{
public:
    std::string name;
    VarType type;
    void *data;

    Data(std::string n);
    Data(std::string n, int i);
    Data(std::string n, float f);
    Data(std::string n, std::string s);
    Data(std::string n, bool b);
    Data(Data *v);

    virtual ~Data();
    int* getInt() const;
    float* getFloat() const;
    std::string* getString() const;
    bool* getBoolean() const;
    void createInt(int i);
    void createFloat(float f);
    void createString(std::string s);
    void createBoolean(bool b);
    void copyFrom(Data *v);
    bool CastToBoolean();
};

#endif // DATA_H
