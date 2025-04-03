/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectMessageCommand.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:22:22 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/02 12:54:12 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "DirectMessageCommand.hpp"
#include <iostream>
#include <sstream>

std::string DirectMessageCommand::getOutgoingMessage(const Server& server, const int clientSocket, const char* buffer)
{

	assert(buffer != NULL);
	//buffer = 127.000.000.001.06667: PRIVMSG nickname :message


	// :donkim3!root@127.0.0.1 PRIVMSG donkim :nickname helloooo
	//맞으면 
	// :[닉네임]![username]@[host] PRIVMSG [상대닉] :[메시지] << 변환 후 리턴
	
	std::string str = std::string (buffer);
	size_t firstIdxOfNick = str.find("PRIVMSG") + 8;
	int lastIdxOfNick = str.find_first_of(" ", firstIdxOfNick);
    std::string username = str.substr(firstIdxOfNick, lastIdxOfNick - firstIdxOfNick);
	// find user () << 매칭후 맞으면

	return (str.substr(lastIdxOfNick + 2));

	while (buffer)
	(void) server;
	(void) clientSocket;
	return "";
}

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