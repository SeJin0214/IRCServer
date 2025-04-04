/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:13:00 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/04 20:54:11 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>

class User
{
    
public:
    User();
    std::string getUsername() const;
    std::string getNickname() const;
    bool hasNickname() const;
    bool hasUsername() const;
    bool isPassed() const;
    void setNickname(std::string& nickname);
    void setUsername(std::string& username);
    void setAthenticated();
    bool operator==(const User& rhs) const;
    ~User();

private:
    std::string mUsername;
    std::string mNickname;
    bool mbAuthenticated;
    bool mbHasNickname;
    bool mbHasUsername;

};