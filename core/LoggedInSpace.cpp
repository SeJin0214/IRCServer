/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoggedInSpace.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:13:46 by sejjeong          #+#    #+#             */
/*   Updated: 2026/01/06 09:32:21 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "Server.hpp"
#include "LoggedInSpace.hpp"
#include "CommandRegistry.hpp"

std::shared_ptr<IOutgoingMessageProvider> LoggedInSpace::getOutgoingMessageProvider(const char *buffer) const
{
	assert(buffer != NULL);

	std::string command = getCommandSection(buffer);

	CommandRegistry& instance = CommandRegistry::getInstance();
	Result<std::shared_ptr<IOutgoingMessageProvider> > result = instance.getProviderInLoggedInSpace(command);
	if (result.hasSucceeded())
	{
		return result.getValue();
	}
	return std::shared_ptr<IOutgoingMessageProvider>();
}

std::shared_ptr<IExecutable> LoggedInSpace::getExecutor(const char *buffer) const
{
	assert(buffer != NULL);

	std::string command = getCommandSection(buffer);

	CommandRegistry& instance = CommandRegistry::getInstance();
	Result<std::shared_ptr<IExecutable> > result = instance.getExecutorInLoggedInSpace(command);
	if (result.hasSucceeded())
	{
		return result.getValue();
	}
	return std::shared_ptr<IExecutable>();
}

void LoggedInSpace::admitOrExile(Server& server)
{
	std::map<int, LoginInfo>::iterator it = mInfos.begin();
	while (it != mInfos.end())
	{
		LoginInfo info = it->second;
		if (info.isValidInfo())
		{
			int clientSocket = it->first;
			++it;
			User* user = exitUserOrNull(clientSocket);
			user->setNickname(info.getNickname());
			user->setUsername(info.getUsername());
			server.loginToServer(clientSocket, user);
		}
		else if (info.isTimeout())
		{
			int clientSocket = it->first;
			++it;
			server.leaveServer(clientSocket);
		}
		else
		{
			++it;
		}
	}
}

bool LoggedInSpace::enterUser(const int clientSocket, User* user)
{
	bool bIsSucceed = Space::enterUser(clientSocket, user);
	assert(bIsSucceed);
	LoginInfo info;
	std::pair<int, LoginInfo> pair(clientSocket, info);
	mInfos.insert(pair);
	return true;
}

User* LoggedInSpace::exitUserOrNull(const int clientSocket)
{
	mInfos.erase(clientSocket);
	return Space::exitUserOrNull(clientSocket);
}

bool LoggedInSpace::trySetAuthenticated(const int clientSocket)
{
	std::map<int, LoginInfo>::iterator it = mInfos.find(clientSocket);
	if (it != mInfos.end())
	{
		it->second.setAthenticated();
		return true;
	}
	return false;
}

bool LoggedInSpace::trySetNickname(const int clientSocket, const std::string& nickname)
{
	std::map<int, LoginInfo>::iterator it = mInfos.find(clientSocket);
	if (it != mInfos.end())
	{
		it->second.setNickname(nickname);
		return true;
	}
	return false;
}

bool LoggedInSpace::trySetUsername(const int clientSocket, const std::string& username)
{
	std::map<int, LoginInfo>::iterator it = mInfos.find(clientSocket);
	if (it != mInfos.end())
	{
		it->second.setUsername(username);
		return true;
	}
	return false;
}
