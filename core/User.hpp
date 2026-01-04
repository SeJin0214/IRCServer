/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:13:00 by sejjeong          #+#    #+#             */
/*   Updated: 2026/01/05 02:52:51 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>
#include "Result.hpp"
#include <sstream>

class User
{
    
public:
    User() = default;
    User(const User& user);
    User(const std::string& nickname, const std::string& username);
    ~User() = default;

    std::string getUsername() const;
    std::string getNickname() const;
    size_t getJoinedChannelCount() const;
    std::vector<std::string> getJoinedChannels() const;
    void setNickname(const std::string& nickname);
    void setUsername(const std::string& username);
    bool isInChannel(const std::string& title) const;
    void addJoinedChannel(const std::string& title);
    std::string flushBuffer();
    void appendStringInBuffer(const char* buffer);
    void removeLastJoinedChannel();


    Result<size_t> getIndexOfJoinedChannel (const std::string& channelName) const;
    void removeJoinedChannel(const std::string& channelName);
    std::string getJoinedChannelName(const size_t indexOfJoinedChannels) const;
    

    Result<std::string> getLastJoinedChannel() const;

private:
    std::vector<std::string> mJoinedChannels;
    std::string mUsername;
    std::string mNickname;
    std::stringstream mBuffer;
};
