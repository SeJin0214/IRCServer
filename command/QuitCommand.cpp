/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:05:45 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/07 18:21:41 by sejjeong         ###   ########.fr       */
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
	
	MessageBetch messageBetch;

	std::stringstream message("ERROR :Closing link: (");
	message << CommonCommand::getHostIP(clientSocket) << ") [" << buffer << "]";

	messageBetch.addMessage(clientSocket, message.str());
	
	Result<User> resultUser = server.findUser(clientSocket);
	User user = resultUser.getValue();
	std::stringstream leaveMessage(CommonCommand::getPrefixMessage(user, clientSocket));
	leaveMessage << " QUIT :" << buffer;

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
		messageBetch.addMessage(*it, leaveMessage.str());
	}
	return messageBetch;
}

void QuitCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	server.exitAllSpaces(clientSocket);
}
