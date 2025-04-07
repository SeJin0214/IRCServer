/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendChannelMessageCommand.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:25:10 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 13:37:43 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <cstring>
#include "SendChannelMessageCommand.hpp"

 
MessageBetch SendChannelMessageCommand::getMessageBetch(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	assert(std::strcmp(buffer, "") != 0);
	std::map<int, std::string> socketAndMessage;
	MessageBetch retMsg;

	// PRIVMSG #aaa :asdfasdf
	// donkim!root@127.0.0.1 PRIVMSG #aaa :asdfasdf
	std::string str(buffer);
	std::stringstream ss(str);
	std::string temp;
	std::string channelName;
	ss >> temp >> channelName;
	std::string msg(ss.str());
	channelName.erase(0, 1);
	Channel  *channel = server.findChannelOrNull(channelName);
	std::vector<int> userSockets = channel->getFdSet();
	for (size_t i = 0; i < userSockets.size(); ++i)
	{
		if (userSockets[i] == clientSocket)
		{
			continue;
		}
		User user = server.findUser(clientSocket).getValue();
		std::cout << "in : " << server.findUser(userSockets[i]).getValue().getNickname() << std::endl;
		std::string who = CommonCommand::getPrefixMessage(user, clientSocket);
		retMsg.addMessage(userSockets[i], who + " PRIVMSG #" + channelName + " " + msg + "\r\n");
	}
	return retMsg;
}