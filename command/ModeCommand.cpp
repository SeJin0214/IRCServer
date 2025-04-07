/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:37:54 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/07 16:29:57 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "ModeCommand.hpp"

 
MessageBetch ModeCommand::getMessageBetch(const Server& server, const int clientSocket, const char* buffer) const
{
	std::cout << buffer << std::endl;
	assert(buffer != NULL);
	MessageBetch msg;
	// CommonCommand commoncommand;

	std::string buf(buffer);
	User user = server.findUser(clientSocket).getValue();
	std::string nickname = user.getNickname();

	std::stringstream ss (buf);
	std::string temp, channelName;
	ss >> temp >> channelName;
	channelName.erase(0, 1);
	if (ss.eof()) //MODE #channel     /r/n
	{
		// channelName.erase(channelName.size() - 2);
		// :irc.local 324 sejjeong #channel :+nt   //sejjeong     +knt :12345678
		// :irc.local 329 sejjeong #channel :1743734234

		//좀더 확인해야함
	}
	else  //MODE #channel b
	{
		msg.addMessage(clientSocket, ":irc.local 368 " + nickname + " #channel :End of channel ban list");
	}
	return msg;
}

void ModeCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
}
