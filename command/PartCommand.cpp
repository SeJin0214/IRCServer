/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:41:48 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/08 16:45:03 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <cstring>
#include "PartCommand.hpp"

MessageBetch PartCommand::getMessageBetch(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	assert(std::strncmp(buffer, "PART ", std::strlen("PART ")) == 0);
	
	MessageBetch messageBetch;
	
	assert(server.findUser(clientSocket).hasSucceeded());
	User user = server.findUser(clientSocket).getValue();

 	const char* channelName = std::strchr(buffer, '#');
	assert(channelName != NULL);

	std::string leaveMessage = CommonCommand::getPrefixMessage(user, clientSocket) + " PART :" + channelName;
	
	messageBetch.addMessage(clientSocket, leaveMessage);

	assert(user.getLastJoinedChannel().hasSucceeded());
	std::string currentJoinedChannelName = user.getLastJoinedChannel().getValue();

	Channel* channel = server.findChannelOrNull(currentJoinedChannelName);
	assert(channel != NULL);

	std::vector<int> clientSockets = channel->getFdSet();
	for (size_t i = 0; i < clientSockets.size(); ++i)
	{
		User* userToFind = channel->findUserOrNull(clientSockets[i]);
		// b에 접속 /part #aaa
		assert(userToFind != NULL);
		
		std::string currentChannel = userToFind->getLastJoinedChannel().getValue();
		assert(userToFind->getLastJoinedChannel().hasSucceeded());

		if (currentChannel == channel->getTitle())
		{
			messageBetch.addMessage(clientSockets[i], leaveMessage);
		}
	}
	return messageBetch;
}

void PartCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	assert(std::strncmp(buffer, "PART ", std::strlen("PART ")) == 0);
	
	const char* startPointer = strchr(buffer, '#');
	assert(startPointer != NULL);
	
	std::string channelName(startPointer + 1);
	server.exitUserInChannel(clientSocket, channelName);
}
