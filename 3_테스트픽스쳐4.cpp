// 3_테스트픽스쳐4.cpp
#include <gtest/gtest.h>

class ImageProcessorTest : public testing::Test {
public:
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
