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
#include "CommonCommand.hpp"

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
		std::string channelName = buf.substr(5, buf.size() - 2);
		std::vector<std::string> nick = (server.findChannelOrNull(clientSocket))->getNicknames();
		std::string userlist;
		for (size_t i = 0; i < nick.size(); i++)
		{
			// @ hostname
			userlist += nick[i];
			if (i != nick.size())
				userlist += ' ';
		}
		msg.addMessage(clientSocket, commoncommand.getPrefixMessage(user, clientSocket) + " " + buf);
		msg.addMessage(clientSocket, ":irc.local 353 " + nickname + " = " + channelName + " :" + userlist);
		msg.addMessage(clientSocket, ":irc.local 366 " + nickname + " " + channelName + " :End of /NAMES list.");
		return msg;
	}
	else if (buf.find ("WHO") && buf.find ("%tna,745"))
	{
		int idxOfGuestNick = buf.find_first_of(" ", 4);
		std::string channelName = buf.substr(4, idxOfGuestNick);
		std::string guestNick = buf.substr(4, idxOfGuestNick);
		msg.addMessage(clientSocket, ":irc.local 354 " + nickname + " 745 " + guestNick + " :0");
		msg.addMessage(clientSocket, ":irc.local 315 " + nickname + " " + guestNick + " :End of /WHO list.");
		return msg;
	}
	else if (buf.find ("WHO") && buf.find ("%tcuhnfdar,743"))
	{
		int idxOfGuestNick = buf.find_first_of(" ", 4);
		std::string channelName = buf.substr(4, idxOfGuestNick);
		std::vector<std::string> nick = (server.findChannelOrNull(clientSocket))->getNicknames();
		for (size_t i = 0; i < nick.size(); i++)
		{
			// @ hostname  nick [] [] [] [] [] 
			Channel* channel = server.findChannelOrNull(clientSocket);
			User user = channel->findUser(nick[i]).getValue().second;
			int usersocket = channel->findUser(nick[i]).getValue().first;
			msg.addMessage(clientSocket ,":irc.local 354 " + nickname + " 743 " + channelName + user.getUsername() \
			+ " " + commoncommand.getPrefixMessage(user, usersocket) + " " + nick[i] + " " + "H@" + " 0 0 :" + user.getUsername()); //// H@ 처리
		}
		msg.addMessage (clientSocket,":irc.local 315 " + nickname + " " + channelName + " :End of /WHO list.");
		return msg;
	}
	else if (buf.find("MODE"))
	{
		std::stringstream ss (buf);
		std::string temp, channelName;
		ss >> temp >> channelName;
		if (ss.eof()) //MODE #channel
		{
			// :irc.local 324 sejjeong #channel :+nt   //sejjeong     +knt :12345678
			// :irc.local 329 sejjeong #channel :1743734234

			//좀더 확인해야함
		}
		else  //MODE #channel b
		{
			msg.addMessage(clientSocket, ":irc.local 368 " + nickname + " #channel :End of channel ban list");
			return msg;
		}
	}
	// message class
	// std::vector<Message>
	// message 안에는 내용물이랑 송신 할 클라이언트 주소 
}

void JoinCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
}
