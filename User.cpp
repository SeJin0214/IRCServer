#include "User.hpp"


User::User() : mName(""), mNick("") {}

User::~User() {}

User::User(const std::string &name, const std::string &nick) 
    : mName(name), mNick(nick) {}

std::string User::getName() const { return mName; }

std::string User::getNick() const { return mNick; }