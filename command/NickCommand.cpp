/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:36:00 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/08 14:24:18 by sejjeong         ###   ########.fr       */
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
	
	// NICK을 제대로 안 넣었을 때 
	size_t startIndex = std::strlen("NICK ");
	char nickname[MAX_BUFFER] = { 0, };
	strcpy(nickname, buffer + startIndex);

	std::stringstream message;
	MessageBetch messageBetch;
	
	size_t nicknameLength = std::strlen(nickname);
	if (nicknameLength == 0)
	{
		message << ":" << server.getServerName() << " 431 * " << nickname << " :No nickname given";
		messageBetch.addMessage(clientSocket, message.str());
	}
	else if (nicknameLength > 30)
	{
		message << ":" << server.getServerName() << " 432 * " << nickname << " :Erroneous nickname";
		messageBetch.addMessage(clientSocket, message.str());
	}
	else if (server.isDuplicatedNickname(nickname))
	{
		message << ":" << server.getServerName() << " 433 * " << nickname << " :Nickname is already in use.";
		messageBetch.addMessage(clientSocket, message.str());
	}
	return messageBetch;
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
