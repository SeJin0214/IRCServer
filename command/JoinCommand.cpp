/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:43:26 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 13:37:54 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "JoinCommand.hpp"

std::vector<std::pair<int, std::string> > JoinCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
	return std::vector<std::pair<int, std::string> >();
}

void JoinCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
}
