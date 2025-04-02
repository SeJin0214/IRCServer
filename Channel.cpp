/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:20:19 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/02 10:53:33 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <cassert>
#include <cstring>
#include "BroadcastCommand.hpp"
#include "Channel.hpp"
#include "Util.hpp"
#include "Result.hpp"

Channel::Channel(const std::string& title, const char* password) 
: mTitle(title)
, mPassword(Util::generateHash65599(password))
{
	
}

Channel::~Channel()
{

}

bool Channel::operator<(const Channel& rhs)
{
	return mTitle < rhs.mTitle;
}

/* getter */
std::string Channel::getTitle() const
{
	return mTitle;
}

unsigned int Channel::getPassword() const
{
	return mPassword;
}

std::string Channel::getCommandList() const
{
	return "";
}

/* setter */
bool Channel::setTitle(const int clientSocket, std::string& title)
{
	if (isOperator(clientSocket) == false)
	{
		return false;
	}
	mTitle = title;
	return true;
}

IOutgoingMessageProvider* Channel::getOutgoingMessageProvider(const char* buffer)
{
	assert(buffer != NULL);
	
	if (std::strncmp(buffer, "/", 1) != 0)
	{
		return new BroadcastCommand();
	}
	return NULL;
}

IIncomingMessageProvider* Channel::getIncomingMessageProvider(const char* buffer)
{
	assert(buffer != NULL);
	
	return NULL;
}

IExecutable* Channel::getExecutor(const char* buffer)
{
	assert(buffer != NULL);
	
	return NULL;
}

bool Channel::toggleMode(User& user, const eMode mode)
{
	if (isOperator(user) == false)
	{
		return false;
	}
	const unsigned char bitFlag = 1 << mode;
	mModeFlag ^= bitFlag;
	return true;
}

bool Channel::isOperator(const User& user) const
{
	for (std::map<int, User>::const_iterator it = mUsers.begin(); it != mUsers.end(); ++it)
	{
		if (it->second == user)
		{
			return true;
		}
	}
	return false;
}

bool Channel::isOperator(const int userSocket) const
{
	for (std::map<int, User>::const_iterator it = mUsers.begin(); it != mUsers.end(); ++it)
	{
		if (it->first == userSocket)
		{
			return true;
		}
	}
	return false;
}
