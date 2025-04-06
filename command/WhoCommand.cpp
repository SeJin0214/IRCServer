/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoCommand.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:01:53 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 13:37:47 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "WhoCommand.hpp"

MessageBetch WhoCommand::getMessageBetch(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	MessageBetch msg;
	CommonCommand commoncommand;

	std::string buf(buffer);
	User user = server.findChannelOrNull(clientSocket)->findUser(clientSocket).getValue();
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
	std::vector<std::string> nick = (server.findChannelOrNull(clientSocket))->getNicknames();
	for (size_t i = 0; i < nick.size(); i++)
	{
		// @ hostname
		Channel* channel = server.findChannelOrNull(clientSocket);
		User user = channel->findUser(nick[i]).getValue().second;
		int usersocket = channel->findUser(nick[i]).getValue().first;
		msg.addMessage(clientSocket ,":" + server.getServerName() + " 354 " + nickname + " 743 " + channelName + user.getUsername() \
		+ " " + commoncommand.getPrefixMessage(user, usersocket) + " " + nick[i] + " " + "H@" + " 0 0 :" + user.getUsername()); //// H@ 처리
	}
	msg.addMessage (clientSocket,":" + server.getServerName() + " 315 " + nickname + " " + channelName + " :End of /WHO list.");
	return msg;
}