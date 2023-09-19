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
        // ...
    }

    User* Load(const std::string& name)
    {
        // ...
        return database->LoadUser(name);
    }
};

#include <gtest/gtest.h>
#include <map>

// Fake Object Pattern
// 의도: 아직 준비되지 않은 협력 객체로 인해서, 테스트 되지 않은 요구사항이 존재합니다.
// 방법: 동일한 기능을 제공하는 가벼운 테스트 대역을 통해, 테스트 되지 않은 요구사항을 검증합니다.
//   1) 협력 객체가 준비되지 않았을 때
//   2) 협력 객체를 사용하기 어려울 때
//   3) 협력 객체가 너무 느려서, 느린 테스트의 문제가 발생할 때

class FakeDatebase : public IDatabase {
    std::map<std::string, User*> data;

public:
    void SaveUser(const std::string& name, User* user) override
    {
        data[name] = user;
    }

    User* LoadUser(const std::string& name) override
    {
        return data[name];
    }
};

// 1) 사용자 정의 객체를 단언문을 통해 검증하기 위해서는
//    해당하는 연산자에 대한 오버로딩이 반드시 제공되어야 합니다.
bool operator==(const User& lhs, const User& rhs)
{
    return lhs.GetName() == rhs.GetName() && lhs.GetAge() == rhs.GetAge();
}

TEST(RespositoryTest, Save)
{
    FakeDatebase fake;
    Respository repo { &fake };
    std::string testName = "test_name";
    int testAge = 42;
    User expected { testName, testAge };

    repo.Save(&expected);
    User* actual = repo.Load(testName);

    EXPECT_EQ(expected, *actual); // ==
}
