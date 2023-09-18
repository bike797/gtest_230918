// 4_스위트픽스쳐.cpp
#include <unistd.h>
#include <string>

class Terminal {
public:
    void Connect() { }
    void Disconnect() { }

    void LogIn(const std::string& id, const std::string& password) { }
    void LogOut() { }

    bool IsLogIn() { return false; }
};
