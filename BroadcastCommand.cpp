/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BroadcastCommand.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:30:42 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/01 18:30:42 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BroadcastCommand.hpp"

std::string BroadcastCommand::getMessageToSend(const Server& server, const int clientSocket, const char* buffer)
{
	(void) server;
	(void) clientSocket;
	std::string result(buffer);
	return result;
}

std::string BroadcastCommand::getMessageToRecive(const Server& server, const int clientSocket, const char* buffer)
{
	(void) server;
	(void) clientSocket;
	(void) buffer;
	return "";
}

std::vector<int> BroadcastCommand::getTargetSockets(const Server& server, const int clientSocket, const char* buffer)
{
	(void) server;
	(void) clientSocket;
	(void) buffer;
	return std::vector<int>();
}
