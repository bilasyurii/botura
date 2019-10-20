#ifndef HELPER
#define HELPER

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

    Data(std::string n) : name(n), type(PNULL), data(nullptr) {}
    Data(std::string n, int i) : name(n), type(INTEGER), data(new int(i)) {}
    Data(std::string n, float f) : name(n), type(FLOAT), data(new float(f)) {}
    Data(std::string n, std::string s) : name(n), type(STRING), data(new std::string(s)) {}
    Data(std::string n, bool b) : name(n), type(BOOLEAN), data(new bool(b)) {}
    Data(Data *v) : type(PNULL), data(nullptr)
    {
        copyFrom(v);
    }

    virtual ~Data()
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

    int* getInt() const
    {
        return static_cast<int*>(data);
    }

    float* getFloat() const
    {
        return static_cast<float*>(data);
    }

    std::string* getString() const
    {
        return static_cast<std::string*>(data);
    }

    bool* getBoolean() const
    {
        return static_cast<bool*>(data);
    }

    void createInt(int i = 0)
    {
        if(type != PNULL)
            delete static_cast<int*>(data);
        data = new int(i);
    }

    void createFloat(float f = 0.0f)
    {
        if(type != PNULL)
            delete static_cast<float*>(data);
        data = new float(f);
    }

    void createString(std::string s = "")
    {
        if(type != PNULL)
            delete static_cast<std::string*>(data);
        data = new std::string(s);
    }

    void createBoolean(bool b = false)
    {
        if(type != PNULL)
            delete static_cast<bool*>(data);
        data = new bool(b);
    }

    void copyFrom(Data *v)
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

    bool CastToBoolean()
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
};

class Statement
{
public:
    virtual void Execute() = 0;
};

class StatementList : public Statement
{
public:
    std::vector<Statement*> statements;

    virtual void Execute()
    {
        for(Statement *s : statements) {
            s->Execute();
        }
    }
};

class Function : public Statement
{
public:
    std::string name;
    StatementList *statements;

    Function(std::string n, StatementList *s) : name(n), statements(s) {}

    virtual void Execute()
    {
        statements->Execute();
    }
};

class Event : public Statement
{
public:
    std::vector<Function*> listeners;

    virtual void Execute()
    {
        for(unsigned i = 0; i < listeners.size(); ++i)
            listeners[i]->Execute();
    }
};
class DataBank
{
public:
    std::vector< std::map<std::string, Data*> > scopes;
    std::map<std::string, Function*> functions;
    std::map<std::string, Event*> events;

    bool isDeclared(std::string name)
    {
        for(int i = scopes.size() - 1; i >= 0; --i)
            if(scopes[i].find(name) != scopes[i].end())
                return true;
        return false;
    }
    typedef Data* Dataptr;
    Dataptr& get(std::string name)
    {
        for(unsigned i = scopes.size() - 1; i >= 0; --i)
            if(scopes[i].find(name) != scopes[i].end())
                return scopes[i][name];
        std::cout << "Error: calling not existing variable.\n";
        throw 0;
    }

    unsigned newScope()
    {
        scopes.push_back(std::map<std::string, Data*>());
        return scopes.size();
    }

    void deleteScope()
    {
        std::map<std::string, Data*>::iterator it = scopes.back().begin();
        for(; it != scopes.back().end(); ++it)
            delete it->second;
        scopes.pop_back();
    }

    void declare(std::string name, Data *data)
    {
        scopes.back()[name] = data;
    }

    bool isFunctionDeclared(std::string name)
    {
        return functions.find(name) != functions.end();
    }

    Function *getFunction(std::string name)
    {
        return functions.find(name)->second;
    }

    void declare(std::string name, Function *f)
    {
        functions[name] = f;
    }

    bool isEventDeclared(std::string name)
    {
        return events.find(name) != events.end();
    }

    Event *getEvent(std::string name)
    {
        return events.find(name)->second;
    }

    void declare(std::string name, Event *e)
    {
        events[name] = e;
    }

    void raiseEvent(std::string event)
    {
        if(isEventDeclared(event))
            events[event]->Execute();
    }
};

DataBank bank;

#endif // HELPER
