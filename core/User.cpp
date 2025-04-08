/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:13:06 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/07 17:57:59 by sejjeong         ###   ########.fr       */
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

size_t User::getJoinedChannelCount() const
{
	return mJoinedChannels.size();
}

void User::setNickname(const std::string& nickname)
{
	mNickname = nickname;
}

void User::setUsername(const std::string& username)
{
	mUsername = username;
}

void User::addJoinedChannel(std::string& title)
{
	for (std::vector<std::string> :: iterator it = mJoinedChannels.begin(); it != mJoinedChannels.end(); ++it)
	{
		if (*it == title)
		{
			mJoinedChannels.erase(it);
			break ;
		}				
	}
	mJoinedChannels.push_back(title);
}

void User::removeLastJoinedChannel()
{
	if (mJoinedChannels.empty())
	{
		return;
	}
	mJoinedChannels.erase(mJoinedChannels.end()- 1);
}

Result<std::string> User::getLastJoinedChannel() const
{
	if (mJoinedChannels.empty())
	{
		return Result<std::string>("", false);
	}
	return Result<std::string>(mJoinedChannels.back(), true);
}

Result<int> User::getIndexOfJoinedChannel (const std::string& channelName)
{
	for (size_t i = 0; i < mJoinedChannels.size(); ++i)
	{
		if (mJoinedChannels[i] == channelName)
			return Result<int>(i, true);
	}
	return Result<int>(-1, false);
}

void User::removeJoinedChannel(std::string channelName)
{
	for (std::vector<std::string>::iterator it = mJoinedChannels.begin(); it != mJoinedChannels.end(); ++it)
	{
		if (*it == channelName)
			mJoinedChannels.erase(it);
	}
}

std::string User::getJoinedChannelName(int indexOfJoinedChannels)
{
	return (mJoinedChannels[indexOfJoinedChannels]);
}
