/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:09:01 by sejjeong          #+#    #+#             */
/*   Updated: 2025/03/31 17:09:01 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "KickCommand.hpp"

MessageBetch KickCommand::getMessageBetch(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	MessageBetch msg;

	//  KICK #channel donjeong :     //donjeong 강퇴당한사람
	//   :donkim!root@127.0.0.1  KICK #channel donjeong :
	//       ->KICK 명령어 사용한 호스트





	//clientsocket(클라이언트)의 isoperator
	//이름이 채널에 있는지 확인 ->에러메시지 발송 :irc.local 401 donkim donjeongss :No such nick
	//msg 보내기

	(void) server;
	(void) clientSocket;
	return msg;
}

void KickCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
}
