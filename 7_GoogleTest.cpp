// 7_GoogleTest.cpp
#include <gtest/gtest.h>

// 1. 테스트 비활성화
// * 작성중인 테스트는 명시적으로 실패해야 합니다.
// * 테스트를 주석처리하게 되면, 잊혀진 테스트가 됩니다.
// * 테스트를 비활성화해서, 테스트를 수행하지 않고, 결과에 포함되지 않습니다.
//   비활성화된 테스트의 존재 여부를 알립니다.
// => Google Test에서 테스트를 비활성화하는 방법은
//    테스트 스위트 이름 또는 테스트 케이스의 이름이 DISABLED_로 시작해야 합니다.
// => 비활성화된 테스트도 수행할 수 있는 기능을 제공합니다.
//   $ ./a.out --gtest_also_run_disabled_tests
#if 0
TEST(ImageProcessorTest, DISABLED_ResizeImage)
{
    // 작성중입니다.
    FAIL() << "작성중입니다.";
}

class DISABLED_SampleTest : public testing::Test { };

TEST_F(DISABLED_SampleTest, foo) { }
TEST_F(DISABLED_SampleTest, goo) { }
TEST_F(DISABLED_SampleTest, hoo) { }
#endif

// 2. 테스트 필터
// > 원하는 테스트를 선택적으로 수행할 수 있습니다.
//  => 테스트 이름을 잘 구성하는 것이 효과적입니다.
// $ ./a.out --gtest_filter=ImageTest.ResizeImage

// - 여러 개를 :을 통해서 나열할 수 있습니다.
// $ ./a.out --gtest_filter=ImageTest.ResizeImage:ImageTest.BlurImage
// $ ./a.out --gtest_filter=ImageProcessTest.*
// $ ./a.out --gtest_filter=Image*.foo

// - 앞의 조건에서 제외할 수 있습니다.
// $ ./a.out --gtest_filter=Image*.foo:-ImageProcessTest.foo

TEST(ImageTest, foo) { }
TEST(ImageTest, goo) { }
TEST(ImageTest, hoo) { }

TEST(ImageProcessTest, foo) { }
TEST(ImageProcessTest, goo) { FAIL(); }
TEST(ImageProcessTest, hoo) { }

// 3. 반복 / 무작위 순서 테스트
// $ ./a.out --gtest_shuffle --gtest_repeat=10 --gtest_break_on_failure
// => 단위 테스트는 반복적으로 어떤 순서로 수행되어도
//    항상 동일한 결과가 나와야 합니다.
// => "변덕스러운 테스트"를 확인하는 목적으로 위의 옵션을 활용합니다.
//   : 테스트의 결과가 일정하지 않습니다.
//     테스트의 결과를 신뢰할 수 없습니다.

// 4. 테스트 결과 포맷터(Test Result Formatter)
// : 테스트의 결과를 XML 형식으로 export 기능을 제공합니다.
// $ ./a.out --gtest_output=xml
//  => 표준 xUnit Test Framework 포맷입니다.

// $ ./a.out --gtest_output=json
//  => Google Test 1.10 이후

// 5. 추가적인 정보도 기록할 수 있습니다.
//    : RecordProperty(key, msg)

#define SPEC(msg)                    \
    do {                             \
        printf("[SPEC] %s\n", msg);  \
        RecordProperty("spec", msg); \
    } while (0)

TEST(ImageTest, ResizeImage)
{
    SPEC("이미지를 리사이즈 합니다.");
    RecordProperty("cpu", "50%");
}

TEST(ImageTest, BlurImage)
{
    SPEC("이미지를 블러 합니다.");
    RecordProperty("cpu", "10%");
}
