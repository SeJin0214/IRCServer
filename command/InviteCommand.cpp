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

std::map<int, std::string> InviteCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer)
{
	// INVITE donjeong #channel
	
	std::string buf = std::string(buffer);

	std::string pars = buf.substr(7);
	if (buf.substr(buf.size() - 2) == "\r\n")
		pars = buf.substr(7, buf.size() - 2);
	std::string temp;

	std::stringstream ss(pars);
	while (getline(ss, temp, ' '))
	{

	}
		
	
	// 127.000.000.001.06667-127.000.000.001.54574: :irc.local 341 donkim donjeong :#channel // 서버 -> donkim
	// 127.000.000.001.06667-127.000.000.001.54586: :donkim!root@127.0.0.1 INVITE donjeong :#channel // 서버 -> donjeong;
	// 실패
	// 127.000.000.001.54574-127.000.000.001.06667: INVITE donjeong,sejjeong #channel
	// 127.000.000.001.06667-127.000.000.001.54574: :irc.local 401 donkim donjeong,sejjeong :No such nick
	assert(buffer != NULL);


    (void) server;
	(void) clientSocket;
	return std::map<int, std::string>();
}


void InviteCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
    (void) server;
	(void) clientSocket;
}