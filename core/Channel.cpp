/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:50:15 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 13:37:57 by sejjeong         ###   ########.fr       */
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
: mModeFlag(0)
, mTitle(title)
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
std::string Channel::getTopic() const
{
	return mTopic;
}

std::string Channel::getTitle() const
{
	return mTitle;
}

unsigned int Channel::getPassword() const
{
	return mPassword;
}

/* setter */
bool Channel::setTopic(const int clientSocket, std::string& topic)
{
	if (isOperator(clientSocket) == false)
	{
		return false;
	}
	mTopic = topic;
	return true;
}

IOutgoingMessageProvider* Channel::getOutgoingMessageProvider(const char* buffer) const
{
	assert(buffer != NULL);

	IOutgoingMessageProvider* provider = Space::getOutgoingMessageProvider(buffer);
	if (provider != NULL)
	{
		return provider;
	}

	std::string command = getCommandSection(buffer);
	if (std::strncmp("MODE", command.c_str(), command.size()) == 0)
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

IExecutable* Channel::getExecutor(const char* buffer) const
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

bool Channel::enterUser(const int clientSocket, const User& user)
{
	if (getUserCount() == 0)
	{
		mOperatorNicknames.push_back(user.getNickname());
	}
	assert(getUserCount() > 0);
	bool bSucceed = Space::enterUser(clientSocket, user);
	assert(bSucceed);
	return bSucceed;
}

void Channel::exitUser(const int clientSocket)
{
	std::vector<std::string>::iterator it = mOperatorNicknames.begin();
	std::map<int, User>::iterator mit = mUsers.find(clientSocket);
	while (it != mOperatorNicknames.end())
	{
		if (*it == mit->second.getNickname())
		{
			mOperatorNicknames.erase(it);
			break;
		}
		++it;
	}
	assert(it != mOperatorNicknames.end());
}

bool Channel::isOperator(const User& user) const
{
	for (size_t i = 0; i < mOperatorNicknames.size(); ++i)
	{
		if (mOperatorNicknames[i] == user.getNickname())
		{
			return true;
		}
	}
	return false;
}

bool Channel::isOperator(const int userSocket) const
{
	Result<User> user = findUser(userSocket);
	for (size_t i = 0; i < mOperatorNicknames.size(); ++i)
	{
		if (mOperatorNicknames[i] == user.getValue().getNickname())
		{
			return true;
		}
	}
	return false;
}