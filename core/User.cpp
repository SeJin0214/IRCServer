/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:13:06 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 11:39:30 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User()
: mUsername("")
, mNickname("")
, mbAuthenticated(false)
, mbHasNickname(false)
, mbHasUsername(false)
{

}

bool User::operator==(const User& rhs) const
{
	return mUsername == rhs.mUsername;
}

User::~User()
{

}

bool User::hasNickname() const
{
	return mbHasNickname;
}

bool User::hasUsername() const
{
	return mbHasUsername;
}

bool User::isPassed() const
{
	return mbAuthenticated;
}

std::string User::getUsername() const
{ 
	return mUsername;
}

std::string User::getNickname() const
{ 
	return mNickname;
}

void User::setNickname(const std::string& nickname)
{
	mNickname = nickname;
	mbHasNickname = true;
}

void User::setUsername(const std::string& username)
{
	mUsername = username;
	mbHasUsername = true; 
}

void User::setAthenticated()
{
	mbAuthenticated = true;
}

bool User::addjoinedChannel(std::string& title)
{
	(void) title;
	return true;
}

bool User::removejoinedChannel(std::string& title)
{
	(void) title;
	return true;
}