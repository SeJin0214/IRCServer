/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectMessageCommand.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:22:22 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/03 10:51:54 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "DirectMessageCommand.hpp"
#include <iostream>
#include <sstream>
#include "User.hpp"

std::map<int, std::string> DirectMessageCommand::getSocketAndMessages(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	assert(buffer != "");
	std::map<int, std::string> socketAndMessage;

	// :donkim3!root@127.0.0.1 PRIVMSG donkim,donjeong :thhrtxh xh h xh hxhx
	//맞으면 
	// :[닉네임]![username]@[host] PRIVMSG [상대닉] :thhrtxh xh h xh hxhx << 변환 후 리턴

	(void) clientSocket;
	std::string str = std::string (buffer);
	size_t firstIdxOfNick = str.find("PRIVMSG") + 8;
	int lastIdxOfNick = str.find_first_of(" ", firstIdxOfNick);
	int colonIdx = str.find_first_of(":", lastIdxOfNick);
    std::string username = str.substr(firstIdxOfNick, lastIdxOfNick - firstIdxOfNick);
	std::string temp;
	std::string privmsg(" PRIVMSG ");
	std::string msg = str.substr(colonIdx - 1);
	std::stringstream ss(username);
	std::string ret;
	for (int i = 0; getline(ss, temp, ','); i++)
	{
		Result<std::pair<int, User>> User = server.findUser(temp);
		if(User.hasSucceeded() == true)
		{
			std::string who = ":[닉네임]![username]@[host]";
			ret = who + privmsg + temp + msg;
			socketAndMessage[User.getValue().first] = ret;
		}
		else
		{
			// std::string errorMsg = " :No such nick/channel";
			ret = ":server 401 " + temp + " :No such nick/channel";
			socketAndMessage[User.getValue().first] = ret;
		}
	}
	return socketAndMessage;
	// usernamesplit(',') a a a strtok
	// find user () << 매칭후 맞으면

}
// <<<<<<< HEAD

std::string DirectMessageCommand::getIncomingMessage(const Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
	return "";
}

std::vector<int> DirectMessageCommand::getTargetSockets(const Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);

	(void) server;
	(void) clientSocket;
	return std::vector<int>();
}
// =======
// >>>>>>> develop
