#include "Message.hpp"
std::vector<std::pair<int, std::string>> Message::getMessage() const
{
    return (mMsg);
}

void Message::addMessage(int socket, std::string msg)
{
    std::pair<int, std::string> message(socket, msg);

    mMsg.push_back(message);
}