// 18_Mocking.cpp
#include <gmock/gmock.h>

// 협력 객체의 인터페이스
class MP3 {
public:
    virtual ~MP3() { }

    virtual void Play() = 0;
    virtual bool Stop(int n) = 0;

    virtual std::string GetTitle() const = 0;
    virtual void Go() const noexcept = 0;

    virtual std::pair<bool, int> GetPair() const = 0;

    // 아래 함수를 Mocking을 직접 해보세요.
    virtual bool CheckMap(std::map<int, double> a, bool b) const = 0;
};

// Google Mock은 테스트 대역이기 때문에,
// 협력 객체의 인터페이스를 구현하는 형태로 만들어야 합니다.
class MockMP3 : public MP3 {
public:
    // MOCK_METHOD(반환타입, 메소드이름, (인자 정보), (한정자 정보));

    // 주의 사항: 템플릿의 타입 인자가 2개 이상 존재하는 경우,
    //          괄호로 감싸 주어야 합니다.
    // bool CheckMap(std::map<int, double> a, bool b) const override
    MOCK_METHOD(bool, CheckMap, ((std::map<int, double> a), bool b), (const, override));

    // std::pair<bool, int> GetPair() const override
    MOCK_METHOD((std::pair<bool, int>), GetPair, (), (const, override));

    // void Play() override
    MOCK_METHOD(void, Play, (), (override));

    // bool Stop(int n) override
    MOCK_METHOD(bool, Stop, (int n), (override));

    // std::string GetTitle() const override
    MOCK_METHOD(std::string, GetTitle, (), (const, override));

    // void Go() const noexcept override
    MOCK_METHOD(void, Go, (), (const, noexcept, override));
};

TEST(MP3Test, Sample)
{
    MockMP3 mock; // !!
}
