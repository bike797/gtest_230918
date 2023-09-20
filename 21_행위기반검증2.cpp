// 21_행위기반검증2.cpp

class Dog {
public:
    virtual void First() = 0;
    virtual void Second() = 0;
    virtual void Third() = 0;
    virtual void Fourth() = 0;
};

#include <gmock/gmock.h>

class MockDog : public Dog {
public:
    MOCK_METHOD(void, First, (), (override));
    MOCK_METHOD(void, Second, (), (override));
    MOCK_METHOD(void, Third, (), (override));
    MOCK_METHOD(void, Fourth, (), (override));
};

void Process1(Dog* p)
{
    p->First();
    p->Second();
    p->Third();
    p->Fourth();
}

// First -> Second -> Third -> Fourth
// => testing::InSequence
using testing::InSequence;

TEST(DogTest, Sample1)
{
    InSequence seq; // 해당 객체가 존재하면, 순서를 검증합니다.
    MockDog mock;

    EXPECT_CALL(mock, First);
    EXPECT_CALL(mock, Second);
    EXPECT_CALL(mock, Third);
    EXPECT_CALL(mock, Fourth);

    Process1(&mock);
}

void Process2(Dog* p)
{
    p->First();

    p->Third();

    p->Second();
    p->Fourth();
}

// First -----> Second            : seq1
//       |
//       -----> Third  -> Fourth  : seq2
// => testing::Sequence
//  EXPECT_CALL(...).InSequence(seq1 ...);

using testing::Sequence;

TEST(DogTest, Sample2)
{
    Sequence seq1, seq2;
    MockDog mock;

    EXPECT_CALL(mock, First).InSequence(seq1, seq2);

    EXPECT_CALL(mock, Second).InSequence(seq1);

    EXPECT_CALL(mock, Third).InSequence(seq2);
    EXPECT_CALL(mock, Fourth).InSequence(seq2);

    Process2(&mock);
}
