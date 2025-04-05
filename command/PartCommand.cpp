/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:41:48 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 13:37:39 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "PartCommand.hpp"

std::vector<std::pair<int, std::string> > PartCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);

	(void) server;
	(void) clientSocket;
	return std::vector<std::pair<int, std::string> >();
}

void PartCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
}
