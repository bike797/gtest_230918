// 11_파라미터화테스트4.cpp
#include <gtest/gtest.h>

enum Color {
    RED,
    WHITE,
    BLACK
};

Color colors[] = {
    Color::RED, Color::WHITE, Color::BLACK
};

std::vector<Color> LoadFromFile()
{
    return {
        Color::RED, Color::WHITE, Color::BLACK
    };
}

std::vector<std::string> cars = {
    "Sonata",
    "Avante",
    "Genesis",
};

int years[] = { 2022, 2023, 2024 };

// 파라미터화 테스트를 통해서 여러 개의 데이터를 조합해서
// 파라미터화 테스트를 수행할 수 있습니다.
// => 데이터 형식(tuple)
using CarType = std::tuple<std::string, Color, int>;

class CarTest : public testing::TestWithParam<CarType> {
};

// 2개 이상의 데이터 셋을 조합할 때는 testing::Combine을 이용하면 됩니다.
INSTANTIATE_TEST_SUITE_P(CarValues, CarTest,
    testing::Combine(
        testing::ValuesIn(cars),
        // testing::Values(Color::RED, Color::WHITE, Color::BLACK)
        // testing::ValuesIn(colors)
        testing::ValuesIn(LoadFromFile()),
        testing::ValuesIn(years)));

TEST_P(CarTest, Sample)
{
    const CarType& data = GetParam();
    std::string car = std::get<0>(data);
    Color color = std::get<1>(data);
    int year = std::get<2>(data);

    std::cout << car << ", " << color << ", " << year << std::endl;
}
