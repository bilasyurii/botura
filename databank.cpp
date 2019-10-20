#include "databank.h"
#include "event.h"
#include "data.h"
#include <iostream>
#include "function.h"

bool DataBank::isDeclared(std::string name)
{
    for(int i = scopes.size() - 1; i >= 0; --i)
        if(scopes[i].find(name) != scopes[i].end())
            return true;
    return false;
}
DataBank::Dataptr& DataBank::get(std::string name)
{
    for(unsigned i = scopes.size() - 1; i >= 0; --i)
        if(scopes[i].find(name) != scopes[i].end())
            return scopes[i][name];
    std::cout << "Error: calling not existing variable.\n";
    throw 0;
}

unsigned DataBank::newScope()
{
    scopes.push_back(std::map<std::string, Data*>());
    return scopes.size();
}

void DataBank::deleteScope()
{
    std::map<std::string, Data*>::iterator it = scopes.back().begin();
    for(; it != scopes.back().end(); ++it)
        delete it->second;
    scopes.pop_back();
}

void DataBank::declare(std::string name, Data *data)
{
    scopes.back()[name] = data;
}

bool DataBank::isFunctionDeclared(std::string name)
{
    return functions.find(name) != functions.end();
}

Function *DataBank::getFunction(std::string name)
{
    return functions.find(name)->second;
}

void DataBank::declare(std::string name, Function *f)
{
    functions[name] = f;
}

bool DataBank::isEventDeclared(std::string name)
{
    return events.find(name) != events.end();
}

Event *DataBank::getEvent(std::string name)
{
    return events.find(name)->second;
}

void DataBank::declare(std::string name, Event *e)
{
    events[name] = e;
}

void DataBank::raiseEvent(std::string event)
{
    if(isEventDeclared(event))
        events[event]->Execute();
}

DataBank::~DataBank()
{
    while(scopes.size() != 0)
        deleteScope();
    std::map<std::string, Function*>::iterator it = functions.begin();
    for(; it != functions.end(); ++it)
        delete it->second;
}

DataBank bank;
