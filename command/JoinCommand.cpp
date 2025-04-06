/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:43:26 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 13:37:54 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <cstddef>
#include <cstring>
#include <sstream>
#include "JoinCommand.hpp"

 
MessageBetch JoinCommand::getMessageBetch(const Server& server, const int clientSocket, const char* buffer) const
{
	JoinCommand a;
	a.execute(const_cast<Server&>(server), clientSocket, buffer);
	assert(buffer != NULL);
	assert(std::strncmp(buffer, "JOIN ", std::strlen("JOIN ")) == 0);

	MessageBetch msg;
	std::string buf(buffer);
	User user = server.findUser(clientSocket).getValue();
	std::string nickname = user.getNickname();
	std::string channelName = buf.substr(5, buf.size() - 2);
	Channel *channel = server.findChannelOrNull(clientSocket);
	std::vector<std::string> nick = channel->getNicknames();//문제발생

	std::vector<int> userSockets = channel->getFdSet();
	std::string userlist;
	for (size_t i = 0; i < nick.size(); i++)
	{
		if (channel->isOperator(userSockets[i]))
		{
			userlist += "@";
		}
		userlist += nick[i];
		if (i != nick.size())
		{
			userlist += ' ';
		}
	}

	msg.addMessage(clientSocket, CommonCommand::getPrefixMessage(user, clientSocket) + " " + buf);
	msg.addMessage(clientSocket, ":irc.local 353 " + nickname + " = " + channelName + " :" + userlist);
	msg.addMessage(clientSocket, ":irc.local 366 " + nickname + " " + channelName + " :End of /NAMES list.");
	return msg;
}

void JoinCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	// JOIN #channel
	std::string buf(buffer);
	std::string channelName;
	channelName = buf.erase(0,6); // channel
	Channel *channel = server.findChannelOrNull(channelName);
	if (!channel)
	{
		server.addChannel(channelName);
	}
	server.findChannelOrNull(channelName)->enterUser(clientSocket, server.findUser(clientSocket).getValue());
	server.findUser(clientSocket).getValue().addjoinedChannel(channelName);
	server.exitUserInLobby(clientSocket);
}
