/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:13:06 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/06 21:56:21 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User()
: mUsername("")
, mNickname("")
{

}

User::User(const std::string& username, const std::string& nickname)
: mUsername(username)
, mNickname(nickname)
{

}

User::~User()
{

}

std::string User::getUsername() const
{ 
	return mUsername;
}

std::string User::getNickname() const
{ 
	return mNickname;
}

std::vector<std::string> User::getJoinedChannels() const
{
	return mJoinedChannels;
}

void User::setNickname(const std::string& nickname)
{
	mNickname = nickname;
}

void User::setUsername(const std::string& username)
{
	mUsername = username;
}

bool User::addjoinedChannel(std::string& title)
{
	mJoinedChannels.push_back(title);
	return true;
}

bool User::removejoinedChannel(std::string& title)
{
	for (std::vector<std::string> :: iterator it = mJoinedChannels.begin(); it != mJoinedChannels.end(); ++it)
	{
		if (*it == title)
		{
			mJoinedChannels.erase(it);
			return true;
		}				
	}
	return false;
}