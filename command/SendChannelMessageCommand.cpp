/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendChannelMessageCommand.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:25:10 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 13:37:43 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "SendChannelMessageCommand.hpp"

std::vector<std::pair<int, std::string> > SendChannelMessageCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
	return std::vector<std::pair<int, std::string> >();
}