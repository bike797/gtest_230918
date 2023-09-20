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
    virtual void Print(const std::vector<int>& numbers) = 0;
};

#include <gmock/gmock.h>

class MockPerson : public Person {
public:
    MOCK_METHOD(void, Go, (int x, int y), (override));
    MOCK_METHOD(void, Print, (const std::vector<int>& numbers), (override));
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
    p->Go(10, 20);
    p->Go(10, 20);
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

// 3) 함수 호출 인자
// => Matcher

void UsePerson3(Person* p)
{
    p->Go(10, 20);
    p->Go(10, 20);
    p->Go(10, 20);
}

using testing::_;

using testing::Eq; // ==
using testing::Ge; // >=
using testing::Gt; // >
using testing::Le; // <=
using testing::Lt; // <

using testing::AllOf; // &&
using testing::AnyOf; // ||
using testing::Matcher;

// Hamcrest Matcher
// => 비교 표현의 확장 라이브러리

TEST(PersonTest, Sample3)
{
    MockPerson mock;

    // EXPECT_CALL(mock, Go(10, 20)).Times(3);
    // EXPECT_CALL(mock, Go).Times(3); // 인자와 상관없이 3번 호출되는 것을 검증합니다.

    // 첫번째 인자가 10이고, 두번째 인자는 상관없이 3번 호출됩니다.
    // EXPECT_CALL(mock, Go(10, _)).Times(3);

    // 첫번째 인자는 10이상이고, 두번째 인자는 21미만으로 3번 호출됩니다.
    // EXPECT_CALL(mock, Go(Ge(10), Lt(21))).Times(3);

    // 첫번째 인자: 5 이상이고, 20 미만  => &&
    // Matcher<int> arg1 = AllOf(Ge(5), Lt(20));
    auto arg1 = AllOf(Ge(5), Lt(20));

    // 두번째 인자: 0 미만이거나, 10 초과 => ||
    // Matcher<int> arg2 = AnyOf(Lt(0), Gt(10));
    auto arg2 = AnyOf(Lt(0), Gt(10));
    EXPECT_CALL(mock, Go(arg1, arg2)).Times(3);

    UsePerson3(&mock);
}

using testing::ElementsAre;
using testing::ElementsAreArray;

void UsePerson4(Person* p)
{
    p->Print({ 1, 1, 3 });
}

TEST(PersonTest, Sample4)
{
    MockPerson mock;

    // [0]: 10보다 작아야 합니다. -> Lt(10)
    // [1]: 2 이상입니다.        -> Ge(2)
    // [2]: 1보다 크고, 5보다 작거나 같아야 합니다. -> AllOf(Gt(1), Le(5))
    // EXPECT_CALL(mock, Print(ElementsAre(Lt(10), Ge(2), AllOf(Gt(1), Le(5)))));

    Matcher<int> data[] = { Lt(10), Ge(2), AllOf(Gt(1), Le(5)) };
    EXPECT_CALL(mock, Print(ElementsAreArray(data)));

    UsePerson4(&mock);
}
