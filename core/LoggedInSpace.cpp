/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoggedInSpace.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:13:46 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 19:24:36 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <cstring>
#include "ErrorCommand.hpp"
#include "LoggedInSpace.hpp"
#include "NickCommand.hpp"
#include "UserCommand.hpp"
#include "PassCommand.hpp"

IOutgoingMessageProvider* LoggedInSpace::getOutgoingMessageProvider(const char *buffer) const
{
	assert(buffer != NULL);

	std::string command = getCommandSection(buffer);
	if (std::strncmp("NICK", command.c_str(), command.size()) == 0)
	{
		return new NickCommand();
	}
	return NULL;
}

#include <iostream>
IExecutable* LoggedInSpace::getExecutor(const char *buffer) const
{
	assert(buffer != NULL);

	std::string command = getCommandSection(buffer);
	if (std::strncmp("PASS", command.c_str(), command.size()) == 0)
	{
		std::cout << command << std::endl;
		return new PassCommand();
	}
	else if (std::strncmp("USER", command.c_str(), command.size()) == 0)
	{
		return new UserCommand();
	}
	else if (std::strncmp("NICK", command.c_str(), command.size()) == 0)
	{
		return new NickCommand();
	}
	return NULL;
}

void LoggedInSpace::admitOrExile(Server& server)
{
	std::map<int, LoginInfo>::iterator it = mInfos.begin();
	while (it != mInfos.end())
	{
		LoginInfo info = it->second;
		if (info.isValidInfo())
		{
			server.enterUserInLobby(it->first, User(info.getUsername(), info.getNickname()));
			int clientSocket = it->first;
			++it;
			exitUser(clientSocket);
		}
		else if (info.isTimeout())
		{
			int clientSocket = it->first;
			++it;
			server.QuitServer(clientSocket);
		}
		else
		{
			++it;
		}
	}
}

bool LoggedInSpace::enterUser(const int clientSocket, const User& user)
{
	bool bSucceed = Space::enterUser(clientSocket, user);
	assert(bSucceed);
	LoginInfo info;
	std::pair<int, LoginInfo> pair(clientSocket, info);
	mInfos.insert(pair);
	return true;
}

void LoggedInSpace::exitUser(const int clientSocket)
{
	Space::exitUser(clientSocket);
	mInfos.erase(clientSocket);
}

bool LoggedInSpace::trySetAuthenticated(const int clientSocket)
{
	std::map<int, User>::iterator it = mUsers.find(clientSocket);
	if (it != mUsers.end())
	{
		std::map<int, LoginInfo>::iterator info = mInfos.find(clientSocket);
		assert(info != mInfos.end());
		info->second.setAthenticated();
		return true;
	}
	return false;
}

bool LoggedInSpace::trySetNickname(const int clientSocket, const std::string& nickname)
{
	std::map<int, User>::iterator it = mUsers.find(clientSocket);
	if (it != mUsers.end())
	{
		std::map<int, LoginInfo>::iterator info = mInfos.find(clientSocket);
		assert(info != mInfos.end());
		info->second.setNickname(nickname);
		return true;
	}
	return false;
}

bool LoggedInSpace::trySetUsername(const int clientSocket, const std::string& username)
{
	std::map<int, User>::iterator it = mUsers.find(clientSocket);
	if (it != mUsers.end())
	{
		std::map<int, LoginInfo>::iterator info = mInfos.find(clientSocket);
		assert(info != mInfos.end());
		info->second.setUsername(username);
		return true;
	}
	return false;
}