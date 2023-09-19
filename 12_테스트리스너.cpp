// 12_테스트리스너.cpp
// => Google Test Framework의 기능입니다.
// : 모든 테스트의 과정에 수행해야 하는 작업을 정의할 수 있습니다.

#include <gtest/gtest.h>

TEST(SampleTest, foo) { }
TEST(SampleTest, goo) { }

// 1) 리스너 정의
//  => testing::TestEventListener
//   필요한 기능에 대해서만 오버라이딩 할 수 있는 testing::EmptyTestEventListener
using testing::TestInfo;
using testing::TestSuite;

class TestListener : public testing::EmptyTestEventListener {
public:
    void OnTestSuiteStart(const TestSuite& /*test_suite*/) override { std::cout << __func__ << std::endl; }
    void OnTestSuiteEnd(const TestSuite& /*test_suite*/) override { std::cout << __func__ << std::endl; }

    void OnTestStart(const TestInfo& /*test_info*/) override { std::cout << __func__ << std::endl; }
    void OnTestEnd(const TestInfo& /*test_info*/) override { std::cout << __func__ << std::endl; }
};

// 2) 리스너 등록
// => main 함수를 직접 정의해서 리스너를 등록해야 합니다.
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    auto& listeners = testing::UnitTest::GetInstance()->listeners();
    listeners.Append(new TestListener);

    delete listeners.Release(listeners.default_result_printer());
    // 리스너를 통해 테스트의 결과를 출력하는 기능을 구현할 수 있습니다.
    // => Google Default Printer / XML Generator

    return RUN_ALL_TESTS();
}
