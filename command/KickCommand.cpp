/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:09:01 by sejjeong          #+#    #+#             */
/*   Updated: 2025/03/31 17:09:01 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <cstring>
#include <sstream>
#include "KickCommand.hpp"

MessageBetch KickCommand::getMessageBetch(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	MessageBetch msg;

	Result<User> resultUser = server.findUser(clientSocket);
	User clientUser = resultUser.getValue();
	std::string temp;
	std::string channelName;
	std::string kickedName;
	std::string kickMsg;
	std::stringstream ss(buffer);
	std::stringstream ret;
	ss >> temp >> channelName;
	if (channelName[0] != '#')
	{
		std::string errMsg = "Invalid format.";
		msg.addMessage(clientSocket, errMsg);
		return msg;
	}
	if (!(ss >> kickedName))
	{
		std::string errMsg = "Invalid format.";
		msg.addMessage(clientSocket, errMsg);
		return msg;
	}
	channelName.erase(0, 1);
	getline(ss, kickMsg);
	Channel* channel = server.findChannelOrNull(channelName);
	assert(channel != NULL);
	std::cout << "name :" << kickedName << std::endl;
	if (server.findUser(kickedName).hasSucceeded() == false)
	{
		ret << ":" << server.getServerName() << " 401 " << clientUser.getNickname() << " " << kickedName << " :No such nick";
		msg.addMessage(clientSocket, ret.str());
	}
	else if (channel->findUser(kickedName).hasSucceeded() == false)
	{
		ret << ":" << server.getServerName() << " 441 " << clientUser.getNickname() << " " << kickedName << " #" << channelName << " :They are not on that channel";
		msg.addMessage(clientSocket, ret.str());
	}
	else if (channel->isOperator(clientSocket) == false)
	{
		ret << ":" << server.getServerName() << " 482 " << clientUser.getNickname() << " #" << channelName << " :You must be a channel op or higher to kick a more privileged user.";
		msg.addMessage(clientSocket, ret.str());
	}
	else
	{
		std::string leaveMessage = CommonCommand::getPrefixMessage(clientUser, clientSocket) + " KICK #" + channelName + " " + kickedName;
		std::vector<int> namesInChannel = channel->getFdSet();
		for (size_t i = 0; i < namesInChannel.size(); ++i)
		{
			ret << leaveMessage << kickMsg;
			if (i + 1 < namesInChannel.size())
				ret << "\r\n";
			msg.addMessage(namesInChannel[i], ret.str());
		}
	}
	return msg;
}

void KickCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);

	std::string temp;
	std::string channelName;
	std::string kickedName;
	std::stringstream ss(buffer);
	ss >> temp >> channelName >> kickedName;
	channelName.erase(0, 1);

	Channel* channel = server.findChannelOrNull(channelName);
	if (channel == NULL)
	{
		return ;
	}
	Result<std::pair<int, User*> > result = channel->findUser(kickedName);
	std::pair<int, User *> kickedUserPack = result.getValue();	
	if (result.hasSucceeded() == false 
	|| channel->isOperator(clientSocket) == false)
	{
		return ;
	}
	
	size_t channelIndexInKickedUser = kickedUserPack.second->getIndexOfJoinedChannel(channelName).getValue();
	for (size_t i = 0; i <= channelIndexInKickedUser; ++i)
	{
		std::cout << "i = " << i << std::endl;
		std::string exitChannelName = kickedUserPack.second->getJoinedChannelName(0);
		server.exitUserInChannel(kickedUserPack.first, exitChannelName);
		kickedUserPack.second->removeJoinedChannel(exitChannelName);
	}
}
