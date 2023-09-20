// 18_Mocking.cpp
#include <gmock/gmock.h>

template <typename T>
class StackInterface {
public:
    virtual ~StackInterface() { }

    virtual int GetSize() const = 0;
    virtual void Push(const T& data) = 0;
};

// 템플릿 기반의 인터페이스도 Mocking 할수 있습니다.
template <typename T>
class MockStackInterface : public StackInterface<T> {
public:
    MOCK_METHOD(int, GetSize, (), (const, override));
    MOCK_METHOD(void, Push, (const T& data), (override));
};

void foo(StackInterface<int>* p)
{
    p->GetSize();
    // p->Push(42);
}

template <typename T>
void goo(StackInterface<T>* p)
{
    p->GetSize();
}

TEST(StackTest, Sample)
{
    MockStackInterface<int> mock;

    EXPECT_CALL(mock, GetSize());
    // EXPECT_CALL(mock, Push(42));

    // foo(&mock);
    goo(&mock);
}
