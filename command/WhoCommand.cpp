/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoCommand.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:01:53 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 13:37:47 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "WhoCommand.hpp"

MessageBetch WhoCommand::getMessageBetch(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);

	MessageBetch msg;

	std::string buf(buffer);
	User user = server.findChannelOrNull(clientSocket)->findUser(clientSocket).getValue();
	std::string nickname = user.getNickname();
	int idxOfGuestNick = buf.find_first_of(" ", 4);
      // who 닉네임 %tna,745 / who 채널 %tcuhnfdar,743
	if (buf.find ("%tna,745"))
	{
		std::string guestNick = buf.substr(4, idxOfGuestNick);
		msg.addMessage(clientSocket, ":" + server.getServerName() + " 354 " + nickname + " 745 " + guestNick + " :0");
		msg.addMessage(clientSocket, ":" + server.getServerName() + " 315 " + nickname + " " + guestNick + " :End of /WHO list.");
		return msg;
	}
	else if (buf.find("%tcuhnfdar"))
	{
		std::string channelName = buf.substr(4, idxOfGuestNick);
		std::vector<std::string> nick = (server.findChannelOrNull(clientSocket))->getNicknames();
		std::stringstream ret;
		for (size_t i = 0; i < nick.size(); ++i)
		{
			Channel* channel = server.findChannelOrNull(clientSocket);
			User user = channel->findUser(nick[i]).getValue().second;
			int usersocket = channel->findUser(nick[i]).getValue().first;
			ret << ":" << server.getServerName() << " 354 " << nickname << " 743 " << channelName << user.getUsername() \
			<< " " << CommonCommand::getPrefixMessage(user, usersocket) << " " << nick[i] << " " << "H";
			if (channel->isOperator(server.findUser(nick[i]).getValue().first))
			{
				ret << "@";
			}
			ret << " 0 0 :" << user.getUsername();
			if (nick.size() - 1 != i)
			{
				ret << "\r\n";
			}
		}
		ret << ":" << server.getServerName() << " 315 " << nickname << " " << channelName << " :End of /WHO list.";
		msg.addMessage (clientSocket, ret.str());
	}
	return msg;
}