/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:43:26 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/03 12:49:16 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "JoinCommand.hpp"
#include <cstddef>


std::map<int, std::string> JoinCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	std::map<int, std::string> ret;

	std::string buf(buffer);
	std::string channelName = buf.substr(5);
	if (buf.find("JOIN"))
	{
		std::vector<std::string> nick = (server.findChannelOrNull(clientSocket))->getNicknames();
		std::string userlist;
		for (size_t i = 0; i < nick.size(); i++)
		{
			userlist += nick[i];
			if (i != nick.size())
				userlist += ' ';
		}
		ret[clientSocket] = ":[닉네임]![username]@[host]" + buf;
		ret[clientSocket] = 
	}
	// message class
	std::vector<Message>
	// message 안에는 내용물이랑 송신 할 클라이언트 주소 
}

void JoinCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
}
