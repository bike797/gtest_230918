// 15_Fake.cpp
#include <string>

class User {
    std::string name;
    int age;

public:
    User(const std::string& s, int n)
        : name { s }
        , age { n }
    {
    }

    std::string GetName() const { return name; }
    int GetAge() const { return age; }
};

class IDatabase {
public:
    virtual ~IDatabase() { }

    virtual void SaveUser(const std::string& name, User* user) = 0;
    virtual User* LoadUser(const std::string& name) = 0;
};

class Respository {
    IDatabase* database;

public:
    Respository(IDatabase* p)
        : database { p }
    {
    }

    void Save(User* user)
    {
        database->SaveUser(user->GetName(), user);
    }

    User* Load(const std::string& name)
    {
        return database->LoadUser(name);
    }
};
