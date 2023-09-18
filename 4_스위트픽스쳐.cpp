// 4_스위트픽스쳐.cpp
#include <unistd.h>
#include <string>

class Terminal {
public:
    void Connect() { }
    void Disconnect() { }

    void LogIn(const std::string& id, const std::string& password) { }
    void LogOut() { }

    bool IsLogIn() { return false; }
};

#include <gtest/gtest.h>

class TerminalTest : public testing::Test {
protected:
    Terminal* ts;

    void SetUp() override
    {
        ts = new Terminal;
        ts->Connect();
    }

    void TearDown() override
    {
        ts->Disconnect();
        delete ts;
    }
};

TEST_F(TerminalTest, LogIn)
{
    ts->LogIn("test_id", "test_password");

    ASSERT_TRUE(ts->IsLogIn()) << "로그인 하였을 때";
}

TEST_F(TerminalTest, LogOut)
{
    ts->LogIn("test_id", "test_password");
    ts->LogOut();

    ASSERT_FALSE(ts->IsLogIn()) << "로그아웃 하였을 때";
}

#if 0
// 아래의 코드를 암묵적 설치/해체의 코드로 변경해보세요.
TEST(TerminalTest, LogIn)
{
    Terminal* ts = new Terminal;
    ts->Connect();

    ts->LogIn("test_id", "test_password");

    ASSERT_TRUE(ts->IsLogIn()) << "로그인 하였을 때";

    ts->Disconnect();
    delete ts;
}

TEST(TerminalTest, LogOut)
{
    Terminal* ts = new Terminal;
    ts->Connect();

    ts->LogIn("test_id", "test_password");
    ts->LogOut();

    ASSERT_FALSE(ts->IsLogIn()) << "로그아웃 하였을 때";

    ts->Disconnect();
    delete ts;
}
#endif
