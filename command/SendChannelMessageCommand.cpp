/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendChannelMessageCommand.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:25:10 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/04 20:59:26 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "SendChannelMessageCommand.hpp"

 
Message SendChannelMessageCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	assert(buffer != "");
	std::map<int, std::string> socketAndMessage;
	CommonCommand commoncommand;
	Message retMsg;

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

	return retMsg;
}
  std::vector<std::pair<int, std::string> > SendChannelMessageCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
	return std::vector<std::pair<int, std::string> >();
 }