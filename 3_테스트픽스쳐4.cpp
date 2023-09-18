// 3_테스트픽스쳐4.cpp
#include <gtest/gtest.h>

class ImageProcessorTest : public testing::Test {
public:
    ImageProcessorTest() { std::cout << "ImageProcessorTest()" << std::endl; }
    ~ImageProcessorTest() { std::cout << "~ImageProcessorTest()" << std::endl; }

    void SetUp() override
    {
        std::cout << "ImageProcessorTest.SetUp()" << std::endl;
    }

    void TearDown() override
    {
        std::cout << "ImageProcessorTest.TearDown()" << std::endl;
    }
};

TEST_F(ImageProcessorTest, ResizeImage)
{
    std::cout << "ImageProcessorTest.ResizeImage()" << std::endl;
}

TEST_F(ImageProcessorTest, BlurImage)
{
    std::cout << "ImageProcessorTest.BlurImage()" << std::endl;
}

// 신선한 픽스쳐 전략
// => 각 테스트케이스마다 새로운 객체를 생성하고 파괴하는 형태로 테스트케이스가 수행됩니다.
/*
ImageProcessorTest* ts = new ImageProcessorTest();
ts->SetUp();
ts->ResizeImage();
ts->TearDown();
delete ts;

ImageProcessorTest* ts = new ImageProcessorTest();
ts->SetUp();
ts->BlurImage();
ts->TearDown();
delete ts;
*/
