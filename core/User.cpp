/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:13:06 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 16:12:16 by sejjeong         ###   ########.fr       */
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
	joinedChannels.push_back (title);
	return true;
}

bool User::removejoinedChannel(std::string& title)
{
	for (std::vector<std::string> :: iterator it = joinedChannels.begin(); it != joinedChannels.end(); ++it)
	{
		if (*it == title)
		{
			joinedChannels.erase(it);
			return true;
		}				
	}
	return false;
}

std::string User::getLastJoinedChannel() const
{
	return (joinedChannels[joinedChannels.size() - 1]);
}