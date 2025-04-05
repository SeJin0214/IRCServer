/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelListCommand.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:41:36 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/04 20:59:53 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "ChannelListCommand.hpp"

Message ChannelListCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	Message msg;
	// std::string nickName = server.find
	return msg;
}
// 127.000.000.001.06667-127.000.000.001.58162: :irc.local 321 donkim3 Channel :Users Name
// :irc.local 322 donkim3 #ccc 1 :[+nt] 
// :irc.local 322 donkim3 #bbb 2 :[+nt] 
// :irc.local 322 donkim3 #aaa 2 :[+nt] 
// :irc.local 323 donkim3 :End of channel list.


// sejjeong
//로그인  pass nick user 명령어

//donjeong
// mode 기능 


// donkim3
// invite 기능 출ㄹ/
// quit  기능
// topic 기능 출력
// list 기능 출력
// kick 기능 출력
// part 기능 출력
std::vector<std::pair<int, std::string> > ChannelListCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
	return std::vector<std::pair<int, std::string> >();
}