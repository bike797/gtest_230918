// User.h
#ifndef USER_H
#define USER_H

#if 0
// #include <gtest/gtest.h>
#include <gtest/gtest_prod.h>
// 제품 코드에 최소한의 의존성 헤더입니다.

class User {
    int age = 42;

    int GetAge() const { return age; }

public:
    void foo() { age = 100; }

    FRIEND_TEST(UserTest, foo);
};
#endif

#if 1
class User {
    int age = 42;

protected:
    int GetAge() const { return age; }

public:
    void foo() { age = 100; }
};
#endif

#endif
