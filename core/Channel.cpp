/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:50:15 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/06 12:42:11 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <cassert>
#include <cstring>
#include <sstream>
#include "ChannelListCommand.hpp"
#include "DirectMessageCommand.hpp"
#include "ErrorCommand.hpp"
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

	std::stringstream ss(buffer);
	std::string command;
	std::getline(ss, command, ' ');
	command = Util::getLowercaseString(command);
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
		return new ModeCommand();
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
	return NULL;
}


bool Channel::isModeActive(const eMode mode)
{
	const unsigned char bitFlag = 1 << mode;
	return (mModeFlag & bitFlag) != 0;
}

bool Channel::onMode(const int userSocket, const eMode mode)
{
	if (isOperator(userSocket) == false)
	{
		return false;
	}
	const unsigned char bitFlag = 1 << mode;
	mModeFlag |= bitFlag;
	return true;
}

bool Channel::offMode(const int userSocket, const eMode mode)
{
	if (isOperator(userSocket) == false)
	{
		return false;
	}
	const unsigned char bitFlag = 1 << mode;
	mModeFlag &= ~bitFlag;
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

bool Channel::isInvited (std::string& invitedUser)
{
	for (std::vector<std::string>::iterator it = mInvitedList.begin(); it != mInvitedList.end(); ++it)
	{
		if (*it == invitedUser)
			return true;
	}
	return false;
}

void Channel::enterInvitedList (std::string& invitedUser)
{
	if (isInvited(invitedUser) == true)
		return ;
	mInvitedList.push_back (invitedUser);
}

void Channel::exitInvitedList (std::string& invitedUser)
{
	if (isInvited(invitedUser) == false)
		return ;
	for (std::vector<std::string>::iterator it = mInvitedList.begin(); it != mInvitedList.end(); ++it)
	{
		if (*it == invitedUser)
		{
			mInvitedList.erase(it);
			break ;
		}
	}
}

std::string Channel::modeState(void)
{
	// std::string ret;

	// if (mModeFlag & 2 == 2)
	// {

	// }
	return "";
}