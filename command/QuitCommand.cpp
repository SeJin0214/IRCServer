/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:05:45 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 11:46:22 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <cstring>
#include <unistd.h>
#include "QuitCommand.hpp"
#include "CommonCommand.hpp"

std::vector<std::pair<int, std::string> > QuitCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);

	std::vector<std::pair<int, std::string> > result;
	
	// 호스트 주소는 주어진 함수를 이용해서 제작  
	std::string message = "ERROR :Closing link: (root@127.0.0.1) [";
	message += buffer;
	message += "]\r\n";
	
	// 다시 할게요~~
	std::pair<int, std::string> socketAndMessage(clientSocket, message);
	result.push_back(socketAndMessage);

	Channel* channel = server.findChannelOrNull(clientSocket);
	if (channel == NULL)
	{
		return result;
	}
	Result<User> temp = channel->findUser(clientSocket);
	assert(temp.hasSucceeded());
	
	User user = temp.getValue();
	message = CommonCommand::getPrefixMessage(user, clientSocket) + " QUIT :" + buffer + "\r\n";
	std::vector<int> clientSockets = channel->getClientSockets();
	for (size_t i = 0; i < clientSockets.size(); ++i)
	{
		if (clientSockets[i] == clientSocket)
		{
			continue;
		}
		std::pair<int, std::string> socketAndMessage(clientSockets[i], message);
		result.push_back(socketAndMessage);
	}
	return result;
}

void QuitCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	Channel* channel;
	User user = server.findUser(clientSocket).getValue();
	while (server.findChannelOrNull(clientSocket))
	{
		channel = server.findChannelOrNull(clientSocket);
		std::string channelName = channel->getTitle();
		user.removejoinedChannel(channelName);
		channel->exitUser(clientSocket);
	}
	server.exitUserInLobby(clientSocket);
}
