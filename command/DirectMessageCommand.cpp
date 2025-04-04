/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectMessageCommand.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:22:22 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/03 16:26:16 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "DirectMessageCommand.hpp"
#include "CommonCommand.hpp"
#include <iostream>
#include <sstream>
#include "User.hpp"

std::map<int, std::string> DirectMessageCommand::getSocketAndMessages(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	assert(buffer != "");
	std::map<int, std::string> socketAndMessage;
	CommonCommand commoncommand;

	// 	127.000.000.001.53570-127.000.000.001.06667: PRIVMSG donjeong,sejjeong :tnlqkf
	// 127.000.000.001.06667-127.000.000.001.54892: :donkim!root@127.0.0.1 PRIVMSG donjeong :tnlqkf
	// 127.000.000.001.06667-127.000.000.001.47094: :donkim!root@127.0.0.1 PRIVMSG sejjeong :tnlqkf
	// :server 401 nickname target :No such nick/channel

	std::string str = std::string (buffer);
	size_t firstIdxOfNick = str.find("PRIVMSG") + 8;
	int lastIdxOfNick = str.find_first_of(" ", 0);
	int colonIdx = str.find_first_of(":", lastIdxOfNick);
    std::string username = str.substr(0, lastIdxOfNick - firstIdxOfNick);
	std::string temp;
	std::string msg = str.substr(colonIdx - 1);
	std::stringstream ss(username);
	std::string ret;
	for (int i = 0; getline(ss, temp, ','); i++)
	{
		Result<std::pair<int, User>> user = server.findUser(temp);
		if(user.hasSucceeded() == true)
		{
			User host = server.findChannelOrNull(clientSocket)->findUser(clientSocket).getValue();
			ret = commoncommand.getPrefixMessage(host, clientSocket) + " PRIVMSG " + temp + msg;
			socketAndMessage[user.getValue().first] = ret;
		}
		else
		{
			ret = ":server 401 " + temp + " :No such nick/channel";
			socketAndMessage[user.getValue().first] = ret;
		}
	}
	return socketAndMessage;
}