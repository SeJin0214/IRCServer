#include "MessageBetch.hpp"
std::vector<std::pair<int, std::string>> MessageBetch::getMessage() const
{
    return (mMsg);
}

void MessageBetch::addMessage(int socket, std::string msg)
{
    std::pair<int, std::string> message(socket, msg);

    mMsg.push_back(message);
}