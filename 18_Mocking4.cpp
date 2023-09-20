// 18_Mocking4.cpp
#include <iostream>

struct Packet { };

// 명시적인 인터페이스
// 장점: 실행시간에 정책을 교체할 수 있습니다.
// 단점: 인라인 최적화가 불가능합니다.

class IPacketStream {
public:
    virtual ~IPacketStream() { }

    virtual void AppendPacket(Packet* newPacket) = 0;
    virtual const Packet* GetPacket(size_t packetNumber) const = 0;
};

class PacketStream : public IPacketStream {
public:
    void AppendPacket(Packet* newPacket) override
    {
        std::cout << "Append Packet" << std::endl;
    }

    const Packet* GetPacket(size_t packetNumber) const override
    {
        std::cout << "GetPacket: " << packetNumber << std::endl;
        return nullptr;
    }
};

class PacketReader {
public:
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

#include <gmock/gmock.h>

class MockPacketStream : public IPacketStream {
public:
    // void AppendPacket(Packet* newPacket) override
    MOCK_METHOD(void, AppendPacket, (Packet * newPacket), (override));

    // const Packet* GetPacket(size_t packetNumber) const override
    MOCK_METHOD(const Packet*, GetPacket, (size_t packetNumber), (const, override));
};

TEST(PacketReaderTest, Sample)
{
    PacketReader reader;
    MockPacketStream stream;

    EXPECT_CALL(stream, AppendPacket(nullptr));
    EXPECT_CALL(stream, GetPacket(42));

    reader.ReadPacket(&stream, 42);
}
