// 8_비기능테스트2.cpp
#include <iostream>
#include <string>

class Image {
    std::string url;

public:
    Image(const std::string& s)
        : url { s }
    {
    }

    void Draw() const
    {
        std::cout << "Draw Image: " << url << std::endl;
    }

#ifdef GTEST_LEAK_TEST
    static int allocCount;
    void* operator new(size_t size)
    {
        ++allocCount;
        return malloc(size);
    }

    void operator delete(void* p, size_t)
    {
        --allocCount;
        free(p);
    }
#endif
};

#ifdef GTEST_LEAK_TEST
int Image::allocCount = 0;
#endif

// SUT에 대해서 메모리 누수가 발생하는지 여부를 검증하고 싶습니다.
//  1) SUT의 클래스의 메모리 할당/해지 연산을 재정의합니다.
bool DrawImage(const std::string& url)
{
    Image* p = new Image(url);
    p->Draw();

    //...

    // delete p;
    return true;
}

#include <gtest/gtest.h>

#if 0
TEST(ImageTest, DrawImage)
{
    int allocCount = Image::allocCount;

    bool result = DrawImage("https://a.com/a.png");
    EXPECT_TRUE(result);

    int diff = Image::allocCount - allocCount;
    EXPECT_EQ(diff, 0) << diff << " object(s) leaks";
}
#endif

// 장점
// 1) 기능적인 테스트와 비기능적인 테스트를 분리할 수 있습니다.
// 2) 모든 테스트케이스는 메모리 검증을 수행합니다.
class ImageTest : public testing::Test {
protected:
    int allocCount = 0;

    void SetUp() override
    {
#ifdef GTEST_LEAK_TEST
        allocCount = Image::allocCount;
#endif
    }

    void TearDown() override
    {
#ifdef GTEST_LEAK_TEST
        int diff = Image::allocCount - allocCount;
        EXPECT_EQ(diff, 0) << diff << " object(s) leaks";
#endif
    }
};

// $ build.sh 8_비기능테스트2.cpp -DGTEST_LEAK_TEST
// => 테스트 코드 안에서만 메모리 관련 코드가 빌드됩니다.

TEST_F(ImageTest, DrawImage)
{
    bool result = DrawImage("https://a.com/a.png");
    EXPECT_TRUE(result);
}

TEST_F(ImageTest, DrawImage2)
{
    bool result = DrawImage("https://a.com/a.png");
    EXPECT_TRUE(result);
}
