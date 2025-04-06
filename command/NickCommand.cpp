/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:36:00 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/07 00:03:35 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <cstddef>
#include <cstring>
#include "NickCommand.hpp"

MessageBetch NickCommand::getMessageBetch(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	assert(std::strncmp(buffer, "NICK ", std::strlen("NICK ")) == 0);
	
	MessageBetch msg;
	size_t startIndex = std::strlen("NICK ");
	char nickname[MAX_BUFFER] = { 0, };
	strcpy(nickname, buffer + startIndex);

	size_t nicknameLength = std::strlen(nickname);
	std::string message = ":";
	if (nicknameLength == 0)
	{
		message += server.getServerName() + " 431 * " + nickname + " :No nickname given";
		msg.addMessage(clientSocket, message);
	}
	else if (nicknameLength > 30)
	{
		message += server.getServerName() + " 432 * " + nickname + " :Erroneous nickname";
		msg.addMessage(clientSocket, message);
	}
	else if (server.isDuplicatedNickname(nickname))
	{
		message += server.getServerName() + " 433 * " + nickname + " :Nickname is already in use.";
		msg.addMessage(clientSocket, message);
	}
	
	return msg;
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
