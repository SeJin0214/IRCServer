/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:13:00 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/08 11:39:32 by sejjeong         ###   ########.fr       */
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
    User();
    User(const User& user);
    User(const std::string& nickname, const std::string& username);
    std::string getUsername() const;
    std::string getNickname() const;
    size_t getJoinedChannelCount() const;
    std::vector<std::string> getJoinedChannels() const;
    void setNickname(const std::string& nickname);
    void setUsername(const std::string& username);
    void addJoinedChannel(std::string& title);
    std::string flushBuffer();
    void appendStringInBuffer(const char* buffer);
    void removeLastJoinedChannel();
    Result<std::string> getLastJoinedChannel() const; // 추가
    ~User();

private:
    std::vector<std::string> mJoinedChannels;
    std::string mUsername;
    std::string mNickname;
    std::stringstream mBuffer;
};