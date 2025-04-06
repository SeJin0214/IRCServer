/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:41:48 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/06 21:52:08 by sejjeong         ###   ########.fr       */
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
	
	Result<User> resultUser = server.findUser(clientSocket);
	User user = resultUser.getValue();
	std::string leaveMessage = CommonCommand::getPrefixMessage(user, clientSocket) + " PART :" + buffer;
	
	messageBetch.addMessage(clientSocket, leaveMessage);
	std::vector<std::string> joinedChannels = user.getJoinedChannels();
	std::string currentJoinedChannelName = joinedChannels[joinedChannels.size() - 1];

	// User current 함수 받으면 변경하기
	Channel* channel = server.findChannelOrNull(currentJoinedChannelName);
	assert(channel != NULL);

	std::vector<int> clientSockets = channel->getFdSet();
	for (size_t i = 0; i < clientSockets.size(); ++i)
	{
		Result<User> user = channel->findUser(clientSockets[i]);
		assert(user.hasSucceeded());
		std::vector<std::string> joinedChannelsOfOtherUser = user.getValue().getJoinedChannels();
		std::string currentChannel = joinedChannelsOfOtherUser[joinedChannelsOfOtherUser.size() - 1];
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
	
	std::string channelName(startPointer);
	server.exitUserInChannel(clientSocket, channelName);
}
