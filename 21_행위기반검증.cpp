// 21_행위기반검증.cpp
// 정의: SUT 내부에서 협력 객체(테스트 대역)를 대상으로 함수의 호출을 통해
//      정상 동작 여부를 검증합니다.
//   1) 함수 호출 여부
//   2) 함수 호출 횟수
//   3) 함수 호출 인자
//   4) 함수 호출 순서
#include <vector>
#include <string>

class Person {
public:
    virtual ~Person() { }

    virtual void Go(int x, int y) = 0;
};

#include <gmock/gmock.h>

class MockPerson : public Person {
public:
    MOCK_METHOD(void, Go, (int x, int y), (override));
};

// 행위 기반 검증
//   : EXPECT_CALL
// 1. 별도의 오류 메세지를 지정할 수 있는 기능이 존재하지 않습니다.
// 2. 모의 객체를 통해서 검증이 수행되는 시점은
//    모의 객체가 소멸자에 의해 파괴되는 시점에 검증이 수행됩니다.
//   => EXPECT_CALL 만 존재합니다. ASSERT_CALL은 존재하지 않습니다.

// 1) 함수 호출 여부
void UsePerson(Person* p)
{
    p->Go(10, 20);
}

TEST(PersonTest, Sample)
{
    MockPerson mock;

    EXPECT_CALL(mock, Go(10, 20));

    UsePerson(&mock);
}

// 2) 함수 호출 횟수
//  : EXPECT_CALL(...).Times(N)
//    EXPECT_CALL(...).Times(Cardinality)

// 1) AtLeast
// 2) AtMost
// 3) Between
using testing::AtLeast; // AtLeast(N) => N번 이상
using testing::AtMost; // AtMost(N) => N번 이하
using testing::Between; // Between(A, B) => A ~ B번

void UsePerson2(Person* p)
{
    p->Go(10, 20);
    // p->Go(10, 20);
    // p->Go(10, 20);
}

TEST(PersonTest, Sample2)
{
    MockPerson mock;

    // EXPECT_CALL(mock, Go(10, 20)); // 1번

    // EXPECT_CALL(mock, Go(10, 20)).Times(2);
    // EXPECT_CALL(mock, Go(10, 20)).Times(AtLeast(2));
    // EXPECT_CALL(mock, Go(10, 20)).Times(AtMost(2));
    EXPECT_CALL(mock, Go(10, 20)).Times(Between(2, 3));

    UsePerson2(&mock);
}
