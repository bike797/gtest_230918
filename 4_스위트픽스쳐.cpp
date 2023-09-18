// 4_스위트픽스쳐.cpp
#include <unistd.h>
#include <string>

class Terminal {
public:
    // 가정: Connect/Disconnect가 느립니다.
    void Connect() { sleep(2); }
    void Disconnect() { sleep(1); }

    void LogIn(const std::string& id, const std::string& password) { }
    void LogOut() { }

    bool IsLogIn() { return false; }
};

#include <gtest/gtest.h>

// 문제점
// - SetUp/TearDown이 느려서(픽스쳐 설치와 해체가 느려서)
//   테스트케이스가 추가될 때마다 전체적인 테스트의 수행 시간이 늘어납니다.
//  "Slow Test"
//  * 테스트가 너무 느려서, 테스트를 수행하는 개발자의 생산성을 떨어뜨립니다.
//  * 테스트가 너무 느려서, 코드가 변경되어도 아무도 테스트를 수행하지 않습니다.

// 해결방법
// => xUnit Test Framework은 스위트 픽스쳐 설치/해체를 제공합니다.
//   객체를 생성하기 전에 설치하고, 객체를 파괴한 이후에 호출됩니다.
//  : "정적 메소드"

class TerminalTest : public testing::Test {
public:
    static Terminal* ts;

    static void SetUpTestSuite()
    {
        std::cout << "SetUpTestSuite" << std::endl;
        ts = new Terminal;
        ts->Connect();
    }

    static void TearDownTestSuite()
    {
        std::cout << "TearDownTestSuite" << std::endl;
        ts->Disconnect();
        delete ts;
    }

protected:
    // Terminal* ts;

    void SetUp() override
    {
        // ts = new Terminal;
        // ts->Connect();
    }

    void TearDown() override
    {
        // ts->Disconnect();
        // delete ts;
    }
};

// 정적 멤버 데이터는 외부 정의가 반드시 필요합니다.
Terminal* TerminalTest::ts = nullptr;

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

TEST_F(TerminalTest, foo) { }

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
