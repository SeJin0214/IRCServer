/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:05:45 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/07 17:58:55 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <cstring>
#include <unistd.h>
#include <set>
#include "QuitCommand.hpp"
#include "CommonCommand.hpp"

MessageBetch QuitCommand::getMessageBetch(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	
	std::string message = "ERROR :Closing link: (" + CommonCommand::getHostIP(clientSocket) + ") [" + buffer + "]";
	MessageBetch messageBetch;
	
	messageBetch.addMessage(clientSocket, message);
	
	// User current 함수 받으면 변경하기
	Result<User> resultUser = server.findUser(clientSocket);
	User user = resultUser.getValue();
	std::string leaveMessage = CommonCommand::getPrefixMessage(user, clientSocket) + " QUIT :" + buffer + "\r\n";

	std::set<int> socketsToSend;
	std::vector<std::string> joinedChannels = user.getJoinedChannels();
	for (size_t i = 0; i < joinedChannels.size(); ++i)
	{
		Channel* joinedChannel = server.findChannelOrNull(joinedChannels[i]);
		std::vector<int> clientSockets = joinedChannel->getFdSet();
		for (size_t i = 0; i < clientSockets.size(); ++i)
		{
			socketsToSend.insert(clientSockets[i]);
		}
	}
	for (std::set<int>::iterator it = socketsToSend.begin(); it != socketsToSend.end(); ++it)
	{
		messageBetch.addMessage(*it, leaveMessage);
	}
	return messageBetch;
}

void QuitCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	server.exitAllSpaces(clientSocket);
}
