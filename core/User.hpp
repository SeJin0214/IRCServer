/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:13:00 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 16:12:19 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>

class User
{
    
public:
    User();
    User(const std::string& nickname, const std::string& username);
    std::string getUsername() const;
    std::string getNickname() const;
    void setNickname(const std::string& nickname);
    void setUsername(const std::string& username);
    void addjoinedChannel(std::string& title);
    std::string getLastJoinedChannel() const; // 추가
    ~User();

private:
    std::vector<std::string> joinedChannels;
    std::string mUsername;
    std::string mNickname;
};