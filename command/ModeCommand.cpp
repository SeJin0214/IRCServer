/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongdong-yong <jeongdong-yong@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:37:54 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/08 09:08:54 by jeongdong-y      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "ModeCommand.hpp"
#include <stdlib.h>

 
MessageBetch ModeCommand::getMessageBetch(const Server& server, const int clientSocket, const char* buffer) const
{
	std::cout << "mode : " << buffer << std::endl;
	assert(buffer != NULL);
	MessageBetch msg;
	// CommonCommand commoncommand;

	// MODE #channel + - 
	// std::cout << "클라->서버 : " << buffer << std::endl;
	User user = server.findUser(clientSocket).getValue();
	std::string nickname = user.getNickname();

	std::stringstream ss (buffer);
	std::string temp, channelName;
	ss >> temp >> channelName;
	channelName.erase(0, 1);
	if (ss.eof())
	{
		std::stringstream ret;
		ret << ":irc.local 324 " << nickname << " #" << channelName << " :" << server.findChannelOrNull(channelName)->getActiveMode() << "\r\n";
		ret << ":irc.local 329 " << nickname << " #" << channelName << " :1743734234";//시간체크
		msg.addMessage(clientSocket, ret.str());
		return (msg);
	} 

	std::string bMode;
	ss >> bMode;
	std::stringstream clientMsg;
	if (bMode.compare("b") == 0)
	{
		clientMsg << ":irc.local 368 " << nickname << " " << channelName << " :End of channel ban list.";
		msg.addMessage(clientSocket, clientMsg.str());
        return (msg);
	}

	if (bMode.size() != 2)
	{
		for (size_t i; i < bMode.size(); ++i)
		{
			clientMsg << ":irc.local 472 " << nickname << " " << bMode[i] << " :is not a recognised channel mode.";
			if (bMode.size() - 1 < i)
			{
				clientMsg << "\r\n";
			}
		}
		return (msg);
	}

	char sign = sign;
	Channel *channel = server.findChannelOrNull(channelName);
	std::vector<int> userSockets = channel->getFdSet();
	
	if (sign != '-' || sign != '+' || bMode[1] != 'i' || bMode[1] != 'k' || bMode[1] != 'l' || bMode[1] != 'o' || bMode[1] != 't')
	{
		for (size_t i = 0; i < bMode.size(); ++i)
		{
			clientMsg << ":irc.local 472 " << nickname << " " << bMode[i] << " :is not a recognised channel mode.";
			if (bMode.size() - 1 > i)
			{
                clientMsg << "\r\n";
            }
		}
		msg.addMessage(clientSocket, clientMsg.str());
		return (msg);
	}

	std::stringstream successMsg;
	std::stringstream errorMsg;

	if (channel->isOperator(clientSocket) == false)
	{
		errorMsg << server.getServerName() << " 482 " << nickname << " #" << channelName << " :You must be a channel op or higher to set channel mode i (inviteonly).";
		msg.addMessage(clientSocket, errorMsg.str());
		return (msg);
	}

	if (bMode[1] == 'i')
	{
		if (channel->isOperator(clientSocket) == false)
		{
			errorMsg << server.getServerName() << " 482 " << nickname << " #" << channelName << " :You must be a channel op or higher to set channel mode i (inviteonly).";
			msg.addMessage(clientSocket, errorMsg.str());
			return (msg);
		}
		if ((sign == '+' && !channel->isModeActive(MODE_INVITE_ONLY)) || (sign == '-' && channel->isModeActive(MODE_INVITE_ONLY)))
		{
			successMsg << server.getServerName() << " MODE #" << channelName << channel->getActiveMode() << bMode;
		}
	}
	else if (bMode[1] == 'k')
	{
		if (channel->isOperator(clientSocket) == false)
		{
			errorMsg << server.getServerName() << " 482 " << nickname << " #" << channelName << " :You must be a channel op or higher to unset channel mode k (key).";
			msg.addMessage(clientSocket, errorMsg.str());
			return (msg);
		}
		std::string password;
		if (!(ss >> password))
		{
			errorMsg << server.getServerName() << " 696 " << nickname << " #" << channelName << " k * :You must specify a parameter for the key mode. Syntax: <key>.";
            msg.addMessage(clientSocket, errorMsg.str());
            return (msg);
		}
		if (sign == '-' && channel->isModeActive(MODE_KEY_LIMIT))
		{
			if (!channel->isPassword(password))
			{
				errorMsg << server.getServerName() << " 467 " << nickname << " #" << channelName << " :Channel key already set";
				msg.addMessage(clientSocket, errorMsg.str());
				return (msg);
			}
		}
		bMode += " :" + password;
	}
	else if (bMode[1] == 'l')
	{
		unsigned int memberCount;
		if (!(ss >> memberCount))
		{
			errorMsg << server.getServerName() << " 696 " << nickname << " #" << channelName << " l * :You must specify a parameter for the limit mode. Syntax: <limit>.";
            msg.addMessage(clientSocket, errorMsg.str());
            return (msg);
		}
		if (channel->isOperator(clientSocket) == false)
		{
			errorMsg << server.getServerName() << " 482 " << nickname << " #" << channelName << " :You must be a channel op or higher to set channel mode l (limit).";
			msg.addMessage(clientSocket, errorMsg.str());
			return (msg);
		}
		std::stringstream num;
		num << memberCount;
		bMode += " :" + num.str();
	}
	else if (bMode[1] == 'o')
	{
		std::string username;
		if (!(ss >> username))
		{
			errorMsg << server.getServerName() << " 696 " << username << " #" << channelName << " " << "o * :You must specify a parameter for the op mode. Syntax: <nick>.";
            msg.addMessage(clientSocket, errorMsg.str());
            return (msg);
		}
		if (channel->isOperator(clientSocket) == false)
		{
			errorMsg << server.getServerName() << " 482 " << nickname << " #" << channelName << " :You must be a channel op or higher to set channel mode o (op).";
			msg.addMessage(clientSocket, errorMsg.str());
			return (msg);
		}
		if (channel->isAddUserAsAdmin(username) == false) 
		{
			errorMsg << server.getServerName() << " 401 " << nickname << " " << username << " :No such nick.";
            msg.addMessage(clientSocket, errorMsg.str());
            return (msg);
		}
		bMode += " :" + username;
	}
	else if (bMode[1] == 't')
	{
		if (channel->isOperator(clientSocket) == false)
		{
			errorMsg << server.getServerName() << " 482 " << nickname << " #" << channelName << " :You must be a channel op or higher to set channel mode t (topiclock).";
			msg.addMessage(clientSocket, errorMsg.str());
			return (msg);
		}
	}
	successMsg << server.getServerName() << " MODE #" << channelName << channel->getActiveMode() << bMode;

	for (size_t i = 0; i < userSockets.size(); ++i)
	{
		if (userSockets[i] != clientSocket)
		{
			msg.addMessage(userSockets[i], successMsg.str());
		}
	}
	return msg;
}

void ModeCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
}
