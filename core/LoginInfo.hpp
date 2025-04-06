/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoginInfo.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:07:31 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/06 12:50:02 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <sys/time.h> 

class LoginInfo
{

public:
	LoginInfo();
	std::string getUsername() const;
    std::string getNickname() const;
    bool hasNickname() const;
    bool hasUsername() const;
    bool isPassed() const;
	bool isValidInfo() const;
	bool isTimeout() const;
	void setAthenticated();
	void setNickname(const std::string& nickname);
    void setUsername(const std::string& username);
private:
	enum { MAX_TIME = 10 };
	std::string mUsername;
    std::string mNickname;
    bool mbAuthenticated;
	struct timeval mStartTime;
	
};