/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelListCommand.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:41:36 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 13:37:48 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "ChannelListCommand.hpp"

std::vector<std::pair<int, std::string> > ChannelListCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
	return std::vector<std::pair<int, std::string> >();
}
