/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:20:19 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/02 15:08:53 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <cassert>
#include <cstring>
#include "BroadcastCommand.hpp"
#include "ChannelListCommand.hpp"
#include "DirectMessageCommand.hpp"
#include "HelpCommand.hpp"
#include "Channel.hpp"
#include "Util.hpp"
#include "Result.hpp"

Channel::Channel(const std::string& title, const char* password) 
: mTopic(title)
, mPassword(Util::generateHash65599(password))
{
	
}

Channel::~Channel()
{

}

bool Channel::operator<(const Channel& rhs)
{
	return mTopic < rhs.mTopic;
}

/* getter */
std::string Channel::getTopic() const
{
	return mTopic;
}

unsigned int Channel::getPassword() const
{
	return mPassword;
}

/* setter */
bool Channel::setTopic(const int clientSocket, std::string& title)
{
	if (isOperator(clientSocket) == false)
	{
		return false;
	}
	mTopic = title;
	return true;
}

IOutgoingMessageProvider* Channel::getOutgoingMessageProvider(const char* buffer)
{
	assert(buffer != NULL);

	IOutgoingMessageProvider* provider = Space::getOutgoingMessageProvider(buffer);
	if (provider != NULL)
	{
		return provider;
	}
	else if (std::strncmp(buffer, "/", 1) != 0)
	{
		return new BroadcastCommand();
	}

	std::string command = getCommandSection(buffer);
	
	return NULL;
}

IIncomingMessageProvider* Channel::getIncomingMessageProvider(const char* buffer)
{
	assert(buffer != NULL);
	
	IIncomingMessageProvider* provider = Space::getIncomingMessageProvider(buffer);
	if (provider != NULL)
	{
		return provider;
	}
	
	std::string command = getCommandSection(buffer);
	if (std::strncmp("/help", command.c_str(), command.size()) == 0)
	{
		return new HelpCommand();
	}
	return NULL;
}

IExecutable* Channel::getExecutor(const char* buffer)
{
	assert(buffer != NULL);
	IExecutable* executor = Space::getExecutor(buffer);
	if (executor != NULL)
	{
		return executor;
	}
	
	std::string command = getCommandSection(buffer);
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
