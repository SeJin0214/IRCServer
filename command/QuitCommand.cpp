/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:05:45 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/04 12:41:48 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <cstring>
#include <unistd.h>
#include "QuitCommand.hpp"
#include "CommonCommand.hpp"

std::map<int, std::string> QuitCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);

	std::map<int, std::string> result;
	
	// 호스트 주소는 주어진 함수를 이용해서 제작  
	std::string message = "ERROR :Closing link: (root@127.0.0.1) [";
	message += buffer;
	message += "]";
	
	std::pair<int, std::string> socketAndMessage(clientSocket, message);
	result.insert(socketAndMessage);

	Channel* channel = server.findChannelOrNull(clientSocket);
	if (channel == NULL)
	{
		return result;
	}
	Result<User> temp = channel->findUser(clientSocket);
	assert(temp.hasSucceeded());
	
	User user = temp.getValue();
	message = CommonCommand::getPrefixMessage(user) + " QUIT :" + buffer;
	std::vector<int> clientSockets = channel->getClientSockets();
	for (size_t i = 0; i < clientSockets.size(); ++i)
	{
		if (clientSockets[i] == clientSocket)
		{
			continue;
		}
		std::pair<int, std::string> socketAndMessage(clientSockets[i], message);
		result.insert(socketAndMessage);
	}
	return result;
}

void QuitCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	server.QuitServer(clientSocket);
}
