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

std::vector<std::pair<int, std::string> > InviteCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);

	// INVITE donjeong #channel\r\n
	std::string userlist, channelName, temp;
	std::string buf = std::string(buffer);

	std::string pars = buf.substr(7, buf.size() - 2);
    int lastIdxOfNick = pars.rfind(" ");
    userlist = pars.substr(0, lastIdxOfNick);
    channelName = pars.substr(lastIdxOfNick + 1);
	std::stringstream ss(userlist);
	while (getline(ss, temp, ' '))
	{
	}
	//:irc.local 341 donkim donjeong :#channel // 서버 -> donkim
	// :donkim!root@127.0.0.1 INVITE donjeong :#channel // 서버 -> donjeong;

	// *******실패*******

	// 권한 없음
// 127.000.000.001.40182-127.000.000.001.06667: INVITE sejjeong #channel
	// 127.000.000.001.06667-127.000.000.001.40182: :irc.local 482 donjeong #channel :You must be a channel op or higher to send an invite.

	// Nickname이 없음;
	// invite donjeong,sejjeong 
// INVITE donjeong,sejjeong #channel
	//:irc.local 401 donkim donjeong,sejjeong :No such nick

	// 2명 이상 초대;
	// invite donjeong sejjeong 
// INVITE donjeong sejjeong --> donkim3 -> server
	// 127.000.000.001.06667-127.000.000.001.58162: :irc.local 403 donkim3 sejjeong :No such channel
	// server -> donkim3

	//  채널에 있는 donkim3 초대
// PRIVMSG #channel :invite donkim3 
	// irc.local 443 donkim3 donkim3 #channel :is already on channel


    (void) server;
	(void) clientSocket;
	return std::vector<std::pair<int, std::string> >();
}


void InviteCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
    (void) server;
	(void) clientSocket;
}