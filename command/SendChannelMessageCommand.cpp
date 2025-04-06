/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendChannelMessageCommand.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:25:10 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 13:37:43 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <cstring>
#include "SendChannelMessageCommand.hpp"

 
MessageBetch SendChannelMessageCommand::getMessageBetch(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	assert(std::strcmp(buffer, "") != 0);
	std::map<int, std::string> socketAndMessage;
	MessageBetch retMsg;

	// PRIVMSG #aaa :asdfasdf
	// donkim!root@127.0.0.1 PRIVMSG #aaa :asdfasdf
	std::string str(buffer);
	std::stringstream ss(str);
	std::string temp;
	std::string channelName;
	ss >> temp >> channelName;
	channelName.erase(0, 1);
	//채널에 있는 유저들의 소켓 필요
	//user -> 채널네임 findchannel(channelName)  채널 나옴
	// 채널 돌면서 getClientSockets() 로 소켓벡터 얻음
	// clientSocket 과 다르면 하나씩 보냄

	(void) clientSocket;
	(void) server;

	return retMsg;
}