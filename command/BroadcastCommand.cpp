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

#include <cassert>
#include "BroadcastCommand.hpp"

std::string BroadcastCommand::getOutgoingMessage(const Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
	std::string result(buffer);
	return result;
}

std::vector<int> BroadcastCommand::getTargetSockets(const Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
	return std::vector<int>();
}
