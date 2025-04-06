/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectMessageCommand.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:22:22 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 13:37:49 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <cstring>
#include "DirectMessageCommand.hpp"
#include "CommonCommand.hpp"
#include <iostream>
#include <sstream>
#include "User.hpp"

MessageBetch DirectMessageCommand::getMessageBetch(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	assert(std::strcmp(buffer, "") != 0);
	std::map<int, std::string> socketAndMessage;
	CommonCommand commoncommand;
	MessageBetch retMsg;

	// 127.000.000.001.58178-127.000.000.001.06667: PRIVMSG #aaa :hello@######@@world
	// 127.000.000.001.06667-127.000.000.001.58162: :sejjeong!root@127.0.0.1 PRIVMSG #aaa :hello@######@@world
    //        aa,bb,cc,dd

	std::string buf(buffer);
	std::string pri, msg, usernames;
	std::stringstream si(buf);
	si >> pri >> usernames >> msg;
	
	std::stringstream ss(usernames);
	std::string ret;
	std::string temp;
	for (int i = 0; getline(ss, temp, ','); i++)
	{
		Result<std::pair<int, User> > user = server.findUser(temp);
		if(user.hasSucceeded() == true)
		{
			User host = server.findChannelOrNull(clientSocket)->findUser(clientSocket).getValue();
			ret = commoncommand.getPrefixMessage(host, clientSocket) + " PRIVMSG " + temp + msg;
			retMsg.addMessage(clientSocket, ret);
		}
		else
		{
			ret = ":server 401 " + temp + " :No such nick/channel";
			retMsg.addMessage(clientSocket, ret);
		}
	}
	return retMsg;
}