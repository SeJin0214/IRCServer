/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Space.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:49:54 by sejjeong          #+#    #+#             */
/*   Updated: 2026/01/05 02:44:36 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <sstream>
#include "Space.hpp"
#include "Util.hpp"

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
	std::map<int, User*>::const_iterator it = mUsers.begin();
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
	std::map<int, User*>::const_iterator it = mUsers.begin();
	while (it != mUsers.end())
	{
		result.push_back(it->second->getNickname());
		++it;
	}
	return result;
}

std::vector<std::string> Space::getUsernames() const
{
	std::vector<std::string> result;
	std::map<int, User*>::const_iterator it = mUsers.begin();
	while (it != mUsers.end())
	{
		result.push_back(it->second->getUsername());
		++it;
	}
	return result;
}

size_t Space::getUserCount() const
{
	return mUsers.size();
}

bool Space::enterUser(const int clientSocket, User* user)
{
	mUsers.insert(std::pair<int, User*>(clientSocket, user));
	return true;
}

User* Space::exitUserOrNull(const int clientSocket)
{
	std::map<int, User*>::iterator it = mUsers.find(clientSocket);
	User* user = NULL;
	if (it != mUsers.end())
	{
		user = it->second;
		mUsers.erase(clientSocket);
	}
	return user;
}

User* Space::findUserOrNull(const int clientSocket) const
{
	std::map<int, User*>::const_iterator it = mUsers.find(clientSocket);
	if (it != mUsers.end())
	{
		return it->second;
	}
	return NULL;
}

Result<std::pair<int, User*> > Space::findUser(const std::string& nickname) const
{
	for (std::map<int, User*>::const_iterator it = mUsers.begin(); it != mUsers.end(); ++it)
	{
		User* user = it->second;
		if (user->getNickname() == nickname)
		{
			std::pair<int, User*> socketAndUser(*it);
			Result<std::pair<int, User*> > result(socketAndUser, true);
			return result;
		}
	}
	std::pair<int, User*> socketAndUser(-1, NULL);
	Result<std::pair<int, User*> > result(socketAndUser, false);
	return result;
}
