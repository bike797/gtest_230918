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
};

int Image::allocCount = 0;

// SUT에 대해서 메모리 누수가 발생하는지 여부를 검증하고 싶습니다.
//  1) SUT의 클래스의 메모리 할당/해지 연산을 재정의합니다.
bool DrawImage(const std::string& url)
{
    Image* p = new Image(url);
    p->Draw();

    //...

    delete p;
    return true;
}

#include <gtest/gtest.h>

TEST(ImageTest, DrawImage)
{
    int allocCount = Image::allocCount;

    bool result = DrawImage("https://a.com/a.png");
    EXPECT_TRUE(result);

    int diff = Image::allocCount - allocCount;
    EXPECT_EQ(diff, 0) << diff << " object(s) leaks";
}
