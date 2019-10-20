#ifndef DATABANK_H
#define DATABANK_H

#include <vector>
#include <map>
#include <string>

class Function;
class Data;
class Event;

class DataBank
{
public:
    std::vector< std::map<std::string, Data*> > scopes;
    std::map<std::string, Function*> functions;
    std::map<std::string, Event*> events;

    typedef Data* Dataptr;

    bool isDeclared(std::string name);
    Dataptr& get(std::string name);
    unsigned newScope();
    void deleteScope();
    void declare(std::string name, Data *data);
    bool isFunctionDeclared(std::string name);
    Function *getFunction(std::string name);
    void declare(std::string name, Function *f);
    bool isEventDeclared(std::string name);
    Event *getEvent(std::string name);
    void declare(std::string name, Event *e);
    void raiseEvent(std::string event);

    virtual ~DataBank();
};

extern DataBank bank;

#endif // DATABANK_H
