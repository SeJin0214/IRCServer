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
#include <sstream>

Message JoinCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	Message msg;
	CommonCommand commoncommand;

	std::string buf(buffer);
	User user = server.findChannelOrNull(clientSocket)->findUser(clientSocket).getValue();
	std::string nickname = user.getNickname();
	if (buf.find("JOIN"))
	{
		std::string channelName = buf.substr(6, buf.size() - 2);
		Channel *channel = server.findChannelOrNull(clientSocket);
		std::vector<std::string> nick = channel->getNicknames();
		std::vector<int> userSockets = channel->getClientSockets();
		std::string userlist;
		for (size_t i = 0; i < nick.size(); i++)
		{
			if (channel->isOperator(userSockets[i]))
				userlist += "@";
			userlist += nick[i];
			if (i != nick.size())
				userlist += ' ';
		}
		msg.addMessage(clientSocket, commoncommand.getPrefixMessage(user, clientSocket) + " " + buf);
		msg.addMessage(clientSocket, ":irc.local 353 " + nickname + " = " + channelName + " :" + userlist);
		msg.addMessage(clientSocket, ":irc.local 366 " + nickname + " " + channelName + " :End of /NAMES list.");
		return msg;
	}
}

void JoinCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	// JOIN #channel
	std::string buf(buffer);
	std::string channelName;
	buf.erase(buf.size() - 2);
	channelName = buf.erase(0,6); // channel
	Channel *channel = server.findChannelOrNull(channelName);
	// channel->enterUser(clientSocket, )  get sejjeong;
}
