#pragma once

#include <iostream>
#include <string>

class User
{
public:
    User(const std::string& name, const std::string& nick);
    std::string getName() const;
    std::string getNick() const;
    User();
    ~User();

private:
    std::string mName;
    std::string mNick;

};