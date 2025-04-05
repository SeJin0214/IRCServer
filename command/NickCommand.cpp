/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:36:00 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 19:32:49 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <cstddef>
#include <cstring>
#include "NickCommand.hpp"

std::vector<std::pair<int, std::string> > NickCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	assert(std::strncmp(buffer, "NICK ", std::strlen("NICK ")) == 0);
	
	size_t startIndex = std::strlen("NICK ");
	char nickname[MAX_BUFFER] = { 0, };
	strcpy(nickname, buffer + startIndex);
	nickname[std::strlen(nickname) - 1] = '\0';

	std::vector<std::pair<int, std::string> > result;
	size_t nicknameLength = std::strlen(nickname);
	// NICKNAME 확인하기 
	if (nicknameLength == 0)
	{
		std::string message = server.getServerName() + " 431 * " + nickname + " :No nickname given";
		std::pair<int, std::string> socketAndMessage(clientSocket, message);
		result.push_back(socketAndMessage);
	}
	else if (nicknameLength > 30)
	{
		std::string message = server.getServerName() + " 432 * " + nickname + " :Erroneous nickname";
		std::pair<int, std::string> socketAndMessage(clientSocket, message);
		result.push_back(socketAndMessage);
	}
	else if (server.isDuplicatedNickname(nickname))
	{
		std::string message = server.getServerName() + " 433 * " + nickname + " :Nickname is already in use.";
		std::pair<int, std::string> socketAndMessage(clientSocket, message);
		result.push_back(socketAndMessage);
	}
	return result;
}

void NickCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	assert(std::strncmp(buffer, "NICK ", std::strlen("NICK ")) == 0);
	
	size_t startIndex = std::strlen("NICK ");
	char nickname[MAX_BUFFER] = { 0, };
	strcpy(nickname, buffer + startIndex);

	assert(std::strncmp(nickname, buffer + startIndex, std::strlen(nickname)) == 0);

	if (server.isDuplicatedNickname(nickname) == false)
	{
		server.trySetNicknameInLoggedSpace(clientSocket, nickname);
	}
}
