/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:09:01 by sejjeong          #+#    #+#             */
/*   Updated: 2025/03/31 17:09:01 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "KickCommand.hpp"

std::string KickCommand::getMessageToSend(const Server& server, const int clientSocket, const char* buffer)
{
	(void) server;
	(void) clientSocket;
	(void) buffer;
	return "";
}

std::string KickCommand::getMessageToRecive(const Server& server, const int clientSocket, const char* buffer)
{
	(void) server;
	(void) clientSocket;
	(void) buffer;
	return "";
}

std::vector<int> KickCommand::getTargetSockets(const Server& server, const int clientSocket, const char* buffer)
{
	(void) server;
	(void) clientSocket;
	(void) buffer;
	return std::vector<int>();
}

void KickCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	(void) server;
	(void) clientSocket;
	(void) buffer;
}
