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

	std::string guestNick, guestNick2, channelName;
	MessageBetch msg;
	CommonCommand commonCommand;
	std::stringstream ss(buffer);
	std::string temp;

	ss >> temp >> guestNick >> channelName;

	const User hostUser = server.findUser(clientSocket).getValue();
	if (channelName[0] != '#')
	{
		guestNick2 = channelName;
		ss >> channelName;
		msg.addMessage(clientSocket, ":" + server.getServerName() + " 403 " + hostUser.getNickname() + " " + guestNick2 + " :No such channel\r\n");
		return msg;
	}

	User user = server.findUser(clientSocket).getValue();
	Channel *channel = server.findChannelOrNull(user.getLastJoinedChannel().getValue());
	
	if (channel == NULL)
	{
		std::string errMsg = "Invalid format.";
		msg.addMessage(clientSocket, errMsg);
		return msg;
	}

	Result<std::pair<int, User *> > guestInChannelPack = channel->findUser(guestNick);
	if (guestInChannelPack.hasSucceeded() == true)
	{
		msg.addMessage(clientSocket, ":" + server.getServerName() + " 443 " + guestNick + " " + guestNick + " " + channelName + "  :is already on channel\r\n");
		return msg;
	}
	else if (server.findUser(guestNick).hasSucceeded() == false)
	{
		msg.addMessage (clientSocket, ":" + server.getServerName() + " 401 " + hostUser.getNickname() + " " + guestNick + " :No such nick\r\n");
		return msg;
	}
	else if (server.findChannelOrNull(user.getLastJoinedChannel().getValue())->isOperator(clientSocket) == false)
	{
		msg.addMessage(clientSocket, ":" + server.getServerName() + " 482 " + hostUser.getNickname() + " " + channelName + "  :You must be a channel op or higher to send an invite.\r\n");
		return msg;
	}
	else
	{
		int userSocket = server.findUser(guestNick).getValue().first;
		msg.addMessage(clientSocket, ":" + server.getServerName() + " 341 " + hostUser.getNickname() + " " + guestNick + " :" + channelName + "\r\n");
		msg.addMessage(userSocket, commonCommand.getPrefixMessage(hostUser, clientSocket) + " INVITE " + guestNick + " :" + channelName + "\r\n");
		return msg;
	}
	return msg;
}

void InviteCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	std::string guest;
	std::string channelName;
	std::string temp;

	std::stringstream ss(buffer);
	ss >> temp >> guest >> channelName;
	if (channelName[0] != '#')
	{
		return ;
	}
	User invitedUser = server.findUser(guest).getValue().second;
	std::string currentChannelName = server.findUser(clientSocket).getValue().getLastJoinedChannel().getValue();
	Channel *channel = server.findChannelOrNull(currentChannelName);
	if (channel == NULL)
	{
		return ;
	}
	std::string nick(invitedUser.getNickname());
	channel->enterInvitedList(nick);
}