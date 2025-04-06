/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:31:28 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/01 18:31:28 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "InviteCommand.hpp"
#include "Server.hpp"
#include <sstream>

MessageBetch InviteCommand::getMessageBetch(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);

	// INVITE donjeong #channel\r\n
	std::string guestNick, guestNick2, channelName;
	std::string buf = std::string(buffer);
	MessageBetch msg;
	CommonCommand commonCommand;

	buf.erase(0, 7);
	buf.erase(buf.size() - 2); // donjeong #channel
	std::stringstream ss(buf);
	ss >> guestNick >> channelName;
	Result<std::pair<int, User> > guestInChannelPack = server.findChannelOrNull(clientSocket)->findUser(guestNick);
	const User hostUser = server.findUser(clientSocket).getValue();
	if (!ss.eof()) // 2개 이상
	{
	// INVITE donjeong sejjeong --> donkim3 -> server
		// :irc.local 403 donkim3 sejjeong :No such channel
		// server -> donkim3
		guestNick2 = channelName;
		ss >> channelName;
		msg.addMessage(clientSocket, ":irc.local 403 " + hostUser.getNickname() + " " + guestNick2 + " :No such channel");
		return msg;
	}
	else if (server.findChannelOrNull(clientSocket)->isOperator(clientSocket) == false)
	{
		// 권한 없음
	// INVITE sejjeong #channel
		// :irc.local 482 donjeong #channel :You must be a channel op or higher to send an invite.
		msg.addMessage(clientSocket, ":irc.local 482 " + hostUser.getNickname() + " " + channelName + "  :You must be a channel op or higher to send an invite.");
		return msg;
	}
	else if (server.findUser(guestNick).hasSucceeded() == false)// Nickname이 없음;
	{
		// 127.000.000.001.58398-127.000.000.001.06667: INVITE asdf #channel
		// 127.000.000.001.06667-127.000.000.001.58398: :irc.local 401 donkim3 asdf :No such nick
		msg.addMessage (clientSocket, ":irc.local 401 " + hostUser.getNickname() + " " + guestNick + " :No such nick");
		return msg;
	}
	else if (guestInChannelPack.hasSucceeded() == true)
	{
		//  채널에 있는 donkim3 초대
	// INVITE donkim3 #channel
	// :irc.local 443 donkim3 donkim3 #channel :is already on channel
		msg.addMessage(clientSocket, ":irc.local 443 " + guestNick + " " + guestNick + " " + channelName + "  :is already on channel");
		return msg;
	}
	else
	{
 		// INVITE sejjeong #channel
		// :irc.local 341 donkim3 sejjeong :#channel
		// :donkim3!root@127.0.0.1 INVITE sejjeong :#channel

		//성공
		msg.addMessage(clientSocket, ":irc.local 341 " + hostUser.getNickname() + " " + guestNick + " :" + channelName);
		msg.addMessage(clientSocket, commonCommand.getPrefixMessage(hostUser, clientSocket) + " INVITE " + guestNick + " :" + channelName);
		return msg;
	}
	return msg;
}

void InviteCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	std::string guest, channelName;
	std::string buf(buffer);

//  INVITE sejjeong #channel
//	:irc.local 341 donkim3 sejjeong :#channel
//  :donkim3!root@127.0.0.1 INVITE sejjeong :#channel

	buf.erase(0, 7);
	buf.erase(buf.size() - 2); // donjeong #channel
	std::stringstream ss(buf);
	ss >> guest >> channelName;

	Result<std::pair<int, User> > guestPack = server.findUser(guest);
	int guestSocket = guestPack.getValue().first;
	User guestUser = guestPack.getValue().second;
	Channel* clientChannel = server.findChannelOrNull(clientSocket); 
	clientChannel->enterUser(guestSocket, guestUser);
	channelName.erase(0, 1); // delete # 
	server.exitUserInLobby(guestSocket);
	guestUser.addjoinedChannel(channelName);
}