/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicCommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:40:36 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/11 13:34:39 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "TopicCommand.hpp"
#include <sstream>

MessageBetch TopicCommand::getMessageBetch(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	MessageBetch msg;
	std::string temp;
	std::string channelName;
	std::string topic;

	std::stringstream ss(buffer);
	std::stringstream ret;
	ss >> temp >> channelName >> topic;
	if (channelName[0] != '#')
	{
		std::string errMsg = "Invalid format.";
		msg.addMessage(clientSocket, errMsg);
		return msg;
	}
	channelName.erase(0, 1);
	Channel* channel = server.findChannelOrNull(channelName);
	std::string clientNickname = server.findUser (clientSocket).getValue().getNickname();

	if (channel == NULL)
	{
		ret << ":" << server.getServerName() << " 403 " << clientNickname << " #" << channelName << " :No such channel";
		msg.addMessage(clientSocket, ret.str());
	}
	else if (channel->findUserOrNull(clientSocket) != NULL)
	{
		if (channel->isModeActive(MODE_TOPIC_LOCK) == true && channel->isOperator(clientSocket) == false)
		{
			ret << ":" << server.getServerName() << " 482 " << clientNickname << " #" << channelName << " :You must be a channel op or higher to change the topic.";
			msg.addMessage(clientSocket, ret.str());
		}
		else
		{
			std::vector<int> namesInChannel = channel->getFdSet();
			for (size_t i = 0; i < namesInChannel.size(); ++i)
			{
				ret << ":" << server.getServerName() << " " << buffer;
				msg.addMessage(namesInChannel[i], ret.str());
			}
		}
	}
	else
	{
		if (channelName.empty() == true)
		{
			ret << ":" << server.getServerName() << " 461 " << clientNickname << " TOPIC :Not enough parameters.";
			msg.addMessage(clientSocket, ret.str());
		}
		else if (topic.empty() == false)
		{
			ret << ":" << server.getServerName() << " 442 " << clientNickname << " #" << channelName << " :You're not on that channel!";
			msg.addMessage(clientSocket, ret.str());
		}
		else if (channel->getTopic().empty())
		{
			ret << ":" << server.getServerName() << " 331 " << clientNickname << " #" << channelName << " :No topic is set.";
		}
		else
		{
			ret << ":" << server.getServerName() << " 332 " << clientNickname << " #" << channelName << " :" << channel->getTopic() << "\r\n" \
			<< ":" << server.getServerName() << " 333 " << clientNickname << " #" << channelName << " " << CommonCommand::getPrefixMessage(server.findUser(clientSocket).getValue(), clientSocket) << " :1744009620";
		}
		msg.addMessage(clientSocket, ret.str());
	}
	return (msg);
}

void TopicCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	std::string temp;
	std::string channelName;
	std::string topic;
	std::stringstream ss(buffer);

	ss >> temp >> channelName >> topic;
	if (channelName[0] != '#')
	{
		return ;
	}
	channelName.erase(0, 1);
	Channel* channel = server.findChannelOrNull(channelName);
	if (channel == NULL)
	{
		return ;
	}
	User user = server.findUser(clientSocket).getValue();
	if (user.getLastJoinedChannel().getValue() != channelName
		|| (channel->isModeActive(MODE_TOPIC_LOCK) == true && channel->isOperator(clientSocket) == false))
	{
		return ;
	}
	channel->setTopic(clientSocket, topic);
}