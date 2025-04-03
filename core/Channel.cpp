/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:50:15 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/03 13:12:10 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <cassert>
#include <cstring>
#include <sstream>
#include "ChannelListCommand.hpp"
#include "DirectMessageCommand.hpp"
#include "ErrorCommand.hpp"
#include "HelpCommand.hpp"
#include "InviteCommand.hpp"
#include "KickCommand.hpp"
#include "ModeCommand.hpp"
#include "PartCommand.hpp"
#include "TopicCommand.hpp"
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

// <<<<<<< HEAD
	std::cout << "first : " << buffer << std::endl;
	// if (std::strncmp(buffer, "/", 1) != 0)
// =======
	IOutgoingMessageProvider* provider = Space::getOutgoingMessageProvider(buffer);
// >>>>>>> develop
	if (provider != NULL)
	{
		return provider;
	}

// <<<<<<< HEAD
	std::stringstream ss(buffer);
	std::string command;
	std::getline(ss, command, ' ');
	command = Util::getLowercaseString(command);
	std::cout << "second : " << buffer << std::endl;
	if (std::strncmp("/msg", command.c_str(), command.size()) == 0)
// =======
	std::string command = getCommandSection(buffer);
	if (std::strncmp("MODE", command.c_str(), command.size()) == 0)
// >>>>>>> develop
	{
		std::stringstream ss(buffer);
		std::string command;
		std::getline(ss, command, ' ');
		std::getline(ss, command, ' ');
		if (command[0] == '#')
		{
			return new ModeCommand();
		}
		else
		{
			return new ErrorCommand();
		}
	}
	else if (std::strncmp("PART", command.c_str(), command.size()) == 0)
	{
		return new PartCommand();
	}
	else if (std::strncmp("INVITE", command.c_str(), command.size()) == 0)
	{
		return new InviteCommand();
	}
	else if (std::strncmp("TOPIC", command.c_str(), command.size()) == 0)
	{
		return new TopicCommand();
	}
	return new ErrorCommand();
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
	if (std::strncmp("MODE", command.c_str(), command.size()) == 0)
	{
		return new ModeCommand;
	}
	else if (std::strncmp("PART", command.c_str(), command.size()) == 0)
	{
		return new PartCommand;
	}
	else if (std::strncmp("INVITE", command.c_str(), command.size()) == 0)
	{
		return new InviteCommand;
	}
	else if (std::strncmp("TOPIC", command.c_str(), command.size()) == 0)
	{
		return new TopicCommand;
	}
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
