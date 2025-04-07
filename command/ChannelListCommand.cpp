/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelListCommand.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:41:36 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 13:37:48 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "ChannelListCommand.hpp"

MessageBetch ChannelListCommand::getMessageBetch(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
	MessageBetch msg;
	// std::string nickName = server.find
	return msg;
}
// :irc.local 321 donkim3 Channel :Users Name
// :irc.local 322 donkim3 #ccc 1 :[+nt] 
// :irc.local 322 donkim3 #bbb 2 :[+nt] 
// :irc.local 322 donkim3 #aaa 2 :[+nt] 
// :irc.local 323 donkim3 :End of channel list.


// sejjeong
//로그인  pass nick user 명령어

//donjeong
// mode 기능 


// donkim3
// invite 기능 출력 <------ ok
// quit  기능
// part 기능 출력


// kick 기능 출력
// topic 기능 출력