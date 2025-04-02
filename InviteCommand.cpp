/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:31:28 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/01 18:31:28 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "InviteCommand.hpp"
#include "Server.hpp"

std::string InviteCommand::getOutgoingMessage(const Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
	return "";
}

std::string InviteCommand::getIncomingMessage(const Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
	return "";
}

std::vector<int> InviteCommand::getTargetSockets(const Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
	return std::vector<int>();
}

void InviteCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
    (void) server;
	(void) clientSocket;
}