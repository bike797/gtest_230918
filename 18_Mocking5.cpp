// 18_Mocking5.cpp
#include <iostream>

struct Packet { };

// 암묵적 인터페이스를 기반으로 하는 의존성 주입 설계
// => C++ 단위 전략(Policy Based Design)
//    템플릿 기반으로 정책을 컴파일 타임에 교체할 수 있습니다.
// => 장점: 인라인 최적화가 가능합니다.
//    단점: 실행 시간에 정책을 교체할 수 없습니다.

class PacketStream {
public:
    void AppendPacket(Packet* newPacket)
    {
        std::cout << "Append Packet" << std::endl;
    }

    const Packet* GetPacket(size_t packetNumber) const
    {
        std::cout << "GetPacket: " << packetNumber << std::endl;
        return nullptr;
    }
};

class PacketReader {
public:
    template <typename IPacketStream>
    void ReadPacket(IPacketStream* stream, size_t packetNumber)
    {
        // ...
        stream->AppendPacket(nullptr);
        stream->GetPacket(packetNumber);
    }
};

//-----
// 의존성 주입
// => 제품 코드를 사용하는 방식 그대로, 테스트도 수행할 수 있습니다.
#if 0
int main()
{
    PacketReader reader;
    PacketStream stream;

    reader.ReadPacket(&stream, 42);
}
#endif

#if 1
#include <gmock/gmock.h>

// 암묵적 인터페이스를 기반으로 Mocking을 수행해서, 테스트 대역을 만들 수 있습니다.
class MockPacketStream {
public:
    // void AppendPacket(Packet* newPacket)
    MOCK_METHOD(void, AppendPacket, (Packet * newPacket));

    // const Packet* GetPacket(size_t packetNumber) const
    MOCK_METHOD(const Packet*, GetPacket, (size_t packetNumber), (const));
};

TEST(PacketReaderTest, Sample)
{
    PacketReader reader;
    MockPacketStream stream;

    EXPECT_CALL(stream, AppendPacket(nullptr));
    EXPECT_CALL(stream, GetPacket(42));

    reader.ReadPacket(&stream, 42);
}
#endif
