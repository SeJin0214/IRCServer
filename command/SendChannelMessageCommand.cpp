/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendChannelMessageCommand.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:25:10 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/02 11:26:09 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "SendChannelMessageCommand.hpp"

std::string SendChannelMessageCommand::getOutgoingMessage(const Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
	return "";
}

std::string SendChannelMessageCommand::getIncomingMessage(const Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
	return "";
}

std::vector<int> SendChannelMessageCommand::getTargetSockets(const Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
	return std::vector<int>();
}