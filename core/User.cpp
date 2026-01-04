/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:13:06 by sejjeong          #+#    #+#             */
/*   Updated: 2026/01/05 02:52:48 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "User.hpp"

User::User(const std::string& username, const std::string& nickname)
: mUsername(username)
, mNickname(nickname)
{

}

User::User(const User& other)
: mJoinedChannels(other.mJoinedChannels)
, mUsername(other.mUsername)
, mNickname(other.mNickname)
{
	mBuffer << other.mBuffer.str();
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

bool User::isInChannel(const std::string& title) const
{
	for (size_t i = 0; i < mJoinedChannels.size(); ++i)
	{
		if (mJoinedChannels[i] == title)
		{
			return true;
		}
	}
	return false;
}

std::string User::flushBuffer()
{
	std::string result = mBuffer.str();
	mBuffer.str("");
	return result;
}

void User::appendStringInBuffer(const char* buffer)
{
	mBuffer << buffer;
}

void User::addJoinedChannel(const std::string& title)
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

Result<size_t> User::getIndexOfJoinedChannel(const std::string& channelName) const
{
	for (size_t i = 0; i < mJoinedChannels.size(); ++i)
	{
		if (mJoinedChannels[i] == channelName)
		{
			return Result<size_t>(i, true);
		}
	}
	return Result<size_t>(-1, false);
}

void User::removeJoinedChannel(const std::string& channelName)
{
	for (std::vector<std::string>::iterator it = mJoinedChannels.begin(); it != mJoinedChannels.end(); ++it)
	{
		if (*it == channelName)
		{
			mJoinedChannels.erase(it);
			break;
		}
	}
}

std::string User::getJoinedChannelName(const size_t indexOfJoinedChannels) const
{
	return (mJoinedChannels[indexOfJoinedChannels]);
}
