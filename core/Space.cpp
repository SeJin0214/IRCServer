/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Space.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:49:54 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 13:38:01 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <sstream>
#include <cstring>
#include "DirectMessageCommand.hpp"
#include "ChannelListCommand.hpp"
#include "IOutgoingMessageProvider.hpp"
#include "JoinCommand.hpp"
#include "QuitCommand.hpp"
#include "SendChannelMessageCommand.hpp"
#include "Space.hpp"
#include "Util.hpp"

Space::~Space()
{
	
}

/* getter */
IOutgoingMessageProvider* Space::getOutgoingMessageProvider(const char* buffer) const
{
	assert(buffer != NULL);

	std::string command = getCommandSection(buffer);
	if (std::strncmp("PRIVMSG", command.c_str(), command.size()) == 0)
	{
		std::stringstream ss(buffer);
		std::string command;
		std::getline(ss, command, ' ');
		std::getline(ss, command, ' ');
		if (command[0] == '#')
		{
			return new SendChannelMessageCommand();
		}
		else
		{
			return new DirectMessageCommand();
		}
	}
	else if (std::strncmp("LIST", command.c_str(), command.size()) == 0)
	{
		return new ChannelListCommand();
	}
	else if (std::strncmp("QUIT", command.c_str(), command.size()) == 0)
	{
		return new QuitCommand();
	}
	else if (std::strncmp("JOIN", command.c_str(), command.size()) == 0)
	{
		return new JoinCommand();
	}
	return NULL;
}

IExecutable* Space::getExecutor(const char* buffer) const
{
	assert(buffer != NULL);
	std::string command = getCommandSection(buffer);
	
	if (std::strncmp("QUIT", command.c_str(), command.size()) == 0)
	{
		return new QuitCommand();
	}
	else if (std::strncmp("JOIN", command.c_str(), command.size()) == 0)
	{
		return new JoinCommand();
	}
	return NULL;
}

std::string Space::getCommandSection(const char* buffer) const
{
	std::stringstream ss(buffer);
	std::string command;
	std::getline(ss, command, ' ');
	return command;
}

std::vector<int> Space::getFdSet() const
{
	std::vector<int> result;
	std::map<int, User>::const_iterator it = mUsers.begin();
	while (it != mUsers.end())
	{
		result.push_back(it->first);
		++it;
	}
	return result;
}

std::vector<std::string> Space::getNicknames() const
{
	std::vector<std::string> result;
	std::map<int, User>::const_iterator it = mUsers.begin();
	while (it != mUsers.end())
	{
		result.push_back(it->second.getNickname());
		++it;
	}
	return result;
}

std::vector<std::string> Space::getUsernames() const
{
	std::vector<std::string> result;
	std::map<int, User>::const_iterator it = mUsers.begin();
	while (it != mUsers.end())
	{
		result.push_back(it->second.getUsername());
		++it;
	}
	return result;
}

std::vector<int> Space::getClientSockets() const
{
	std::vector<int> result;
	std::map<int, User>::const_iterator it = mUsers.begin();
	while (it != mUsers.end())
	{
		result.push_back(it->first);
		++it;
	}
	return result;
}

int Space::getUserCount() const
{
	return static_cast<int>(mUsers.size());
}

bool Space::trySetAuthenticated(const int clientSocket)
{
	std::map<int, User>::iterator it = mUsers.find(clientSocket);
	if (it != mUsers.end())
	{
		it->second.setAthenticated();
		return true;
	}
	return false;
}

bool Space::trySetNickname(const int clientSocket, const std::string& nickname)
{
	std::map<int, User>::iterator it = mUsers.find(clientSocket);
	if (it != mUsers.end())
	{
		it->second.setNickname(nickname);
		return true;
	}
	return false;
}

bool Space::trySetUsername(const int clientSocket, const std::string& username)
{
	std::map<int, User>::iterator it = mUsers.find(clientSocket);
	if (it != mUsers.end())
	{
		it->second.setUsername(username);
		return true;
	}
	return false;
}

bool Space::enterUser(const int clientSocket, const User &user)
{
	assert(mUsers.find(clientSocket) == mUsers.end());
	mUsers.insert(std::pair<int, User>(clientSocket, user));
	return true;
}

void Space::exitUser(const int clientSocket)
{
	assert(mUsers.find(clientSocket) != mUsers.end());
	mUsers.erase(clientSocket);
}

Result<User> Space::findUser(const int clientSocket) const
{
	std::map<int, User>::const_iterator it = mUsers.find(clientSocket);
	if (it != mUsers.end())
	{
		Result<User> result(it->second, true);
		return result;
	}
	else
	{
		Result<User> result(it->second, false);
		return result;	
	}
}

Result<std::pair<int, User> > Space::findUser(const std::string& nickname) const
{
	for (std::map<int, User>::const_iterator it = mUsers.begin(); it != mUsers.end(); ++it)
	{
		User user = it->second;
		if (user.getNickname() == nickname)
		{
			std::pair<int, User> socketAndUser(*it);
			Result<std::pair<int, User> > result(socketAndUser, true);
			return result;
		}
	}
	std::pair<int, User> socketAndUser(-1, User());
	Result<std::pair<int, User> > result(socketAndUser, false);
	return result;
}

