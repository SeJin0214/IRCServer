/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicCommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:40:36 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 13:37:45 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "TopicCommand.hpp"

std::vector<std::pair<int, std::string> > TopicCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
	return std::vector<std::pair<int, std::string> >();
}

void TopicCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
}
