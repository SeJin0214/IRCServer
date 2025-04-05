/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:13:00 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 11:29:26 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>

class User
{
    
public:
    User();
    std::string getUsername() const;
    std::string getNickname() const;
    bool hasNickname() const;
    bool hasUsername() const;
    bool isPassed() const;
    void setNickname(const std::string& nickname);
    void setUsername(const std::string& username);
    bool addjoinedChannel(std::string& title);
    bool removejoinedChannel(std::string& title);
    void setAthenticated();
    bool operator==(const User& rhs) const;
    ~User();

private:
    std::vector<std::string> joinedChannels;
    std::string mUsername;
    std::string mNickname;
    bool mbAuthenticated;
    bool mbHasNickname;
    bool mbHasUsername;
};