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

#include "InviteCommand.hpp"
#include "Server.hpp"

std::string InviteCommand::getMessageToSend(const Server& server, const int clientSocket, const char* buffer)
{
	(void) server;
	(void) clientSocket;
	(void) buffer;
	return "";
}

std::string InviteCommand::getMessageToRecive(const Server& server, const int clientSocket, const char* buffer)
{
	(void) server;
	(void) clientSocket;
	(void) buffer;
	return "";
}

std::vector<int> InviteCommand::getTargetSockets(const Server& server, const int clientSocket, const char* buffer)
{
	(void) server;
	(void) clientSocket;
	(void) buffer;
	return std::vector<int>();
}

void InviteCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
    (void) server;
	(void) clientSocket;
	(void) buffer;
}