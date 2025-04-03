/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Space.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:52:43 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/03 10:42:33 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "IOutgoingMessageProvider.hpp"
#include "Space.hpp"

Space::~Space()
{
	
}



/* getter */
IOutgoingMessageProvider* Space::getOutgoingMessageProvider(const char* buffer)
{
	assert(buffer != NULL);
	
	return NULL;
}

IExecutable* Space::getExecutor(const char* buffer)
{
	assert(buffer != NULL);
	return NULL;
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

bool Space::enterUser(int clientSocket, User& user)
{
	mUsers.insert(std::pair<int, User>(clientSocket, user));
	return true;
}

void Space::exitUser(int clientSocket)
{
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

Result<std::pair<int, User> > Space::findUser(std::string nickname) const
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
	std::pair<int, User> socketAndUser(-1, User("", ""));
	Result<std::pair<int, User> > result(socketAndUser, false);
	return result;
}

