/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoCommand.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:01:53 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/07 17:25:03 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "WhoCommand.hpp"

MessageBetch WhoCommand::getMessageBetch(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	MessageBetch msg;

	std::string buf(buffer);
	User user = server.findUser(clientSocket).getValue();
	std::string nickname = user.getNickname();
	int idxOfGuestNick = buf.find_first_of(" ", 4);

	if (buf.find ("%tna,745"))
	{
		std::string guestNick = buf.substr(4, idxOfGuestNick);
		msg.addMessage(clientSocket, ":" + server.getServerName() + " 354 " + nickname + " 745 " + guestNick + " :0");
		msg.addMessage(clientSocket, ":" + server.getServerName() + " 315 " + nickname + " " + guestNick + " :End of /WHO list.");
		return msg;
	}
	std::string channelName = buf.substr(4, idxOfGuestNick);
	Result<std::string> lastJoinedChannel = user.getLastJoinedChannel();
	assert(lastJoinedChannel.hasSucceeded());
	std::vector<std::string> nick = (server.findChannelOrNull(lastJoinedChannel.getValue()))->getNicknames();
	for (size_t i = 0; i < nick.size(); i++)
	{
		// @ hostname
		std::pair<int, User> socketAndUser = server.findUser(nick[i]).getValue();
		User user = socketAndUser.second;
		int usersocket = socketAndUser.first;
		msg.addMessage(clientSocket ,":" + server.getServerName() + " 354 " + nickname + " 743 " + channelName + user.getUsername() \
		+ " " + CommonCommand::getPrefixMessage(user, usersocket) + " " + nick[i] + " " + "H@" + " 0 0 :" + user.getUsername()); //// H@ 처리
	}


	msg.addMessage (clientSocket,":" + server.getServerName() + " 315 " + nickname + " " + channelName + " :End of /WHO list.");
	return msg;
}