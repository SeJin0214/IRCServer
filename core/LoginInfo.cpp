/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoginInfo.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:09:17 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 16:11:35 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LoginInfo.hpp"

LoginInfo::LoginInfo()
: mUsername("")
, mNickname("")
, mbAuthenticated(false)
, mStartTime(std::clock())
{

}

std::string LoginInfo::getUsername() const
{ 
	return mUsername;
}

std::string LoginInfo::getNickname() const
{ 
	return mNickname;
}

bool LoginInfo::hasNickname() const
{
	return mNickname != "";
}

bool LoginInfo::hasUsername() const
{
	return mUsername != "";
}

bool LoginInfo::isPassed() const
{
	return mbAuthenticated;
}

bool LoginInfo::isValidInfo() const
{
	return hasNickname() && hasUsername() && isPassed();
}

bool LoginInfo::isTimeout() const
{
	clock_t currentTime = std::clock();
	double sec = static_cast<double>(currentTime - mStartTime) / CLOCKS_PER_SEC;
	return sec > MAX_TIME;
}

void LoginInfo::setNickname(const std::string& nickname)
{
	mNickname = nickname;
}

void LoginInfo::setUsername(const std::string& username)
{
	mUsername = username;
}

void LoginInfo::setAthenticated()
{
	mbAuthenticated = true;
}
