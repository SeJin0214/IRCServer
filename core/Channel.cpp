/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:50:15 by sejjeong          #+#    #+#             */
/*   Updated: 2026/01/06 09:31:45 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <sstream>
#include "Channel.hpp"
#include "CommandRegistry.hpp"
#include "Util.hpp"
#include "Result.hpp"

Channel::Channel(const std::string& title, const char* password) 
: mModeFlag(0)
, mTitle(title)
, mPassword(Util::generateHash65599(password))
{
	
}

bool Channel::operator<(const Channel& rhs) const
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

void Channel::setPassword(const std::string& password)
{
	mPassword = Util::generateHash65599(password.c_str());
}

bool Channel::setTopic(const int clientSocket, const std::string& topic)
{
	if (isOperator(clientSocket) == false)
	{
		return false;
	}
	mTopic = topic;
	return true;
}

std::shared_ptr<IOutgoingMessageProvider> Channel::getOutgoingMessageProvider(const char* buffer) const
{
	assert(buffer != NULL);

	std::string command = getCommandSection(buffer);
	CommandRegistry& instance = CommandRegistry::getInstance();
	Result<std::shared_ptr<IOutgoingMessageProvider> > result = instance.getProviderInChannel(command);
	if (result.hasSucceeded())
	{
		return result.getValue();
	}
	return std::shared_ptr<IOutgoingMessageProvider>();
}

std::shared_ptr<IExecutable> Channel::getExecutor(const char* buffer) const
{
	assert(buffer != NULL);
	
	std::string command = getCommandSection(buffer);
	CommandRegistry& instance = CommandRegistry::getInstance();
	Result<std::shared_ptr<IExecutable> > result = instance.getExecutorInChannel(command);
	if (result.hasSucceeded())
	{
		return result.getValue();
	}
	return std::shared_ptr<IExecutable>();
}

std::string Channel::getActiveMode() const
{
	std::stringstream ss;
	ss << "+n";
	if (isModeActive(MODE_INVITE_ONLY))
	{
		ss << "i";
	}
	if (isModeActive(MODE_KEY_LIMIT))
	{
		ss << "k";
	}
	if (isModeActive(MODE_LIMIT_USER))
	{
		ss << "l";
	}
	if (isModeActive(MODE_TOPIC_LOCK))
	{
		ss << "t";
	}
	return ss.str();
}

bool Channel::isPassword(const std::string& password) const
{
	unsigned int	hash = 0;

	const char *str = password.c_str();
	for (int i = 0; str[i] != '\0'; ++i)
	{
		hash = 65599 * hash + str[i];
	}
	if (mPassword == (hash ^ (hash >> 16)))
		return true;
	return false;
}


bool Channel::isModeActive(const eMode mode) const
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

bool Channel::enterUser(const int clientSocket, User* user)
{
	if (getUserCount() == 0)
	{
		mOperatorNicknames.push_back(user->getNickname());
	}
	bool bIsSucceed = Space::enterUser(clientSocket, user);
	assert(bIsSucceed);
	user->addJoinedChannel(mTitle);

	std::string nickname = user->getNickname();
	exitInvitedList(nickname);
	
	assert(getUserCount() > 0);
	return bIsSucceed;
}

User* Channel::exitUserOrNull(const int clientSocket)
{
	std::map<int, User*>::iterator userIt = mUsers.find(clientSocket);
	if (userIt != mUsers.end())
	{
		std::vector<std::string>::iterator it = mOperatorNicknames.begin();
		while (it != mOperatorNicknames.end())
		{
			if (*it == userIt->second->getNickname())
			{
				mOperatorNicknames.erase(it);
				break;
			}
			++it;
		}
		User* user = userIt->second;
		user->removeJoinedChannel(mTitle);
	}
	return Space::exitUserOrNull(clientSocket);
}

bool Channel::isAddUserAsAdmin(const std::string& userNickname)
{
	if (this->findUser(userNickname).hasSucceeded())
	{
		for (size_t i = 0; i < mOperatorNicknames.size(); ++i)
		{
			if (mOperatorNicknames[i] == userNickname)
			{
				return true;
			}
		}
		mOperatorNicknames.push_back(userNickname);
		return true;
	}
	return false;
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
	User* user = findUserOrNull(userSocket);
	for (size_t i = 0; i < mOperatorNicknames.size(); ++i)
	{
		if (mOperatorNicknames[i] == user->getNickname())
		{
			return true;
		}
	}
	return false;
}

bool Channel::isInvited(const std::string& invitedUser) const
{
	for (std::vector<std::string>::const_iterator it = mInvitedList.begin(); it != mInvitedList.end(); ++it)
	{
		if (*it == invitedUser)
		{
			return true;
		}
	}
	return false;
}

void Channel::enterInvitedList(const std::string& invitedUser)
{
	if (isInvited(invitedUser) == true)
	{	
		return ;
	}
	mInvitedList.push_back(invitedUser);
}

void Channel::exitInvitedList(const std::string& invitedUser)
{
	if (isInvited(invitedUser) == false)
	{
		return ;
	}
	for (std::vector<std::string>::iterator it = mInvitedList.begin(); it != mInvitedList.end(); ++it)
	{
		if (*it == invitedUser)
		{
			mInvitedList.erase(it);
			break ;
		}
	}
}

void Channel::setMaxMemberCount(unsigned int num)
{
	mMaxMemberCount = num;
}

size_t Channel::getMaxMemberCount() const
{
	return mMaxMemberCount;
}

void Channel::removeOperatorNicknames(const std::string& nickname)
{
	for (std::vector<std::string>::iterator it = mOperatorNicknames.begin(); it != mOperatorNicknames.end(); ++it)
	{
		if (*it == nickname)
		{
			mOperatorNicknames.erase(it);
			break;
		}
	}
}

void Channel::removeInvitedLists(const std::string& nickname)
{
	for (std::vector<std::string>::iterator it = mInvitedList.begin(); it != mInvitedList.end(); ++it)
	{
		if (*it == nickname)
		{
			mInvitedList.erase(it);
			break;
		}
	}
}
