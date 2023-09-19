// 11_파라미터화테스트2.cpp
bool IsPrime(int value)
{
    for (int i = 2; i < value; ++i) {
        if (value % i == 0) {
            return false;
        }
    }

    return true;
}

#include <gtest/gtest.h>
// 위의 IsPrime을 데이터 중심의 파라미터화 테스트를 통해 작성해보세요.
// 2, 3, 5, 7, 11, 13, 17, 23
