/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:13:00 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/06 21:00:00 by sejjeong         ###   ########.fr       */
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
    std::vector<std::string> getJoinedChannels() const;
    void setNickname(const std::string& nickname);
    void setUsername(const std::string& username);
    bool addjoinedChannel(std::string& title);
    bool removejoinedChannel(std::string& title);
    ~User();

private:
    std::vector<std::string> mJoinedChannels;
    std::string mUsername;
    std::string mNickname;
};