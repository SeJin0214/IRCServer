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

std::vector<std::pair<int, std::string> > InviteCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
    (void) server;
	(void) clientSocket;
	return std::vector<std::pair<int, std::string> >();
}


void InviteCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
    (void) server;
	(void) clientSocket;
}