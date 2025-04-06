/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:37:54 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 13:37:56 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "ModeCommand.hpp"

 
MessageBetch ModeCommand::getMessageBetch(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	MessageBetch msg;
	// CommonCommand commoncommand;

	// MODE #channel + - 
	// std::cout << "클라->서버 : " << buffer << std::endl;
	std::string buf(buffer);
	User user = server.findChannelOrNull(clientSocket)->findUser(clientSocket).getValue();
	std::string nickname = user.getNickname();

	std::stringstream ss (buf);
	std::string temp, channelName;
	ss >> temp >> channelName;
	
	if (ss.eof())    //MODE #channel        n/t/k/l/i/o
	{
		std::stringstream ret;
		ret << ":irc.local 324 " << nickname << " " << channelName << " :" << server.findChannelOrNull(channelName)->getActiveMode() << "\r\n";//모드 검사
		ret << ":irc.local 329 " << nickname << " " << channelName << " :1743734234";//시간체크
		msg.addMessage(clientSocket, ret.str());
		return (msg);
	} 

	std::string bMode;
	ss >> bMode;
	if (bMode.compare("b") == 0)// MODE #channel b
	{
		msg.addMessage(clientSocket, ":irc.local 368 " + nickname + " " + channelName + " :End of channel ban list.");
        return (msg);
	}
	// MODE #channel +-모드   비밀번호
	char sign;

	std::stringstream clientMsg;
	std::stringstream changeMode;
	channelName.erase(0, 1);
	Channel *channel = server.findChannelOrNull(channelName);
	std::vector<int> userSockets = channel->getFdSet();
	for (size_t i = 0; i < bMode.size(); ++i)
	{
		if ((bMode[i] == '+') || (bMode[i] == '-'))
		{
			sign = bMode[i];
			continue;
		}

		switch (bMode[i])// +i+k+l
		{
			case 'i':
			{
				if (channel->isOperator(clientSocket) == true)
				{
					if (sign == '+' && !channel->isModeActive(MODE_INVITE_ONLY))
					{
						channel->onMode(clientSocket, MODE_INVITE_ONLY);
						changeMode << sign + 'i';
						//성공메시지 돌면서 보내기
					}
					else if (sign == '-' && channel->isModeActive(MODE_INVITE_ONLY))
					{
						channel->offMode(clientSocket, MODE_INVITE_ONLY);
						changeMode << sign + 'i';
						//성공메시지 돌면서 보내기
					}
				}
				else
				{//:irc.local 482 sejjeong #channel :You must be a channel op or higher to set channel mode i (inviteonly).
					clientMsg << server.getServerName() << " 482 " << nickname << " #" << channelName << " :You must be a channel op or higher to set channel mode i (inviteonly).";
				}
				break ;
			}
			case 'k':
			{
				if (channel->isOperator(clientSocket) == true)
				{
					std::string password;
					if (ss >> password)
					{
						if (sign == '+' && !channel->isModeActive(MODE_KEY_LIMIT))//다음인자 확인
						{
							channel->onMode(clientSocket, MODE_KEY_LIMIT);
							channel->setPassword(password);
							changeMode << sign + 'k';
							//성공메시지 돌면서 보내기
						}
						else if (sign == '-' && channel->isModeActive(MODE_KEY_LIMIT))//다음인자 있으면 확인
						{
							if (channel->isPassword(password))
							{
								channel->offMode(clientSocket, MODE_KEY_LIMIT);
								changeMode << sign + 'k';
								//성공메시지 돌면서 보내기
							}
							else
							{//비밀번호가 맞지 않을떄
								// :irc.local 467 nickname1 #a :Channel key already set
								clientMsg << server.getServerName() << " 467 " << nickname << " #" << channelName << " :Channel key already set";
							}
						}
					}
					else
					{//인자가 없을때
						// :irc.local 696 nickname1 #a k * :You must specify a parameter for the key mode. Syntax: <key>.
						clientMsg << server.getServerName() << " 696 " << nickname << " #" << channelName << " k * :You must specify a parameter for the key mode. Syntax: <key>.";
					}

				}
				else
				{//권한이 없을때
					// :irc.local 482 nickname2 #a :You must be a channel op or higher to unset channel mode k (key).
					clientMsg << server.getServerName() << " 482 " << nickname << " #" << channelName << " :You must be a channel op or higher to unset channel mode k (key).";
				}
				break ;
			}
			case 'l':
			{
				if (channel->isOperator(clientSocket) == true)
				{
					std::string password;
					if (ss >> password)
					{
						if (sign == '+' && !channel->isModeActive(MODE_LIMIT_USER))// 다음인자 확인
						{
							channel->onMode(clientSocket, MODE_LIMIT_USER);
							changeMode << sign + 'l';
							//성공메시지 돌면서 보내기
						}
						else if (sign == '-' && channel->isModeActive(MODE_LIMIT_USER))
						{
							channel->offMode(clientSocket, MODE_LIMIT_USER);
							changeMode << sign + 'l';
							//성공메시지 돌면서 보내기
						}
					}
					else
					{//인자 없을 떄 (권한보다 우선)
						// :irc.local 696 nickname2 #a l * :You must specify a parameter for the limit mode. Syntax: <limit>.
						clientMsg << server.getServerName() << " 696 " << nickname << " #" << channelName << " l * :You must specify a parameter for the limit mode. Syntax: <limit>.";
					}
				}
				else
				{//권한 없을 때
					// :irc.local 482 nickname2 #a :You must be a channel op or higher to set channel mode l (limit).
					clientMsg << server.getServerName() << " 482 " << nickname << " #" << channelName << " :You must be a channel op or higher to set channel mode l (limit).";
				}
				break ;
            }
			case 'o': //다음인자 확인
			{
				// 유저한테 권한이 있는지 확인한다음 권한 주기  //뒤에 인자가 없을떄랑 인자가 있을 때 닉네임이 다른 경우
				if (channel->isOperator(clientSocket) == true)
				{
					std::string userName; 
					if (ss >> userName)//인자가 있을 때
					{
						if (channel->isAddUserAsAdmin(userName) == true) //닉네임이 맞는경우 
						{
							//성공메시지 돌면서 보내기
						}
						else
						{
							//:irc.local 401 donjeong donkimm :No such nick
							clientMsg << server.getServerName() << " 401 " << nickname << " " << userName << " :No such nick.";
						}
					}
					else//인자가 없을 때
					{
						//:irc.local 696 donkim #channel o * :You must specify a parameter for the op mode. Syntax: <nick>.
						clientMsg << server.getServerName() << " 696 " << userName << " #" << channelName << " " << "o * :You must specify a parameter for the op mode. Syntax: <nick>.";
					}

				}
				else
				{//:irc.local 482 nickname3 #a :You must be a channel op or higher to set channel mode o (op).
					clientMsg << server.getServerName() << " 482 " << nickname << " #" << channelName << " :You must be a channel op or higher to set channel mode o (op).";
				}
				break ;
            }
			case 't':
			{
				if (channel->isOperator(clientSocket) == true)
				{
					if (sign == '+' && !channel->isModeActive(MODE_TOPIC_LOCK))
					{
						channel->onMode(clientSocket, MODE_TOPIC_LOCK);
						changeMode << sign + 't';
						//성공메시지 돌면서 보내기
					}
					else if (sign == '-' && channel->isModeActive(MODE_TOPIC_LOCK))
					{
						channel->offMode(clientSocket, MODE_TOPIC_LOCK);
						changeMode << sign + 't';
						//성공메시지 돌면서 보내기
					}
				}
				else
				{//권한 없을 때
					//:irc.local 482 nickname2 #a :You must be a channel op or higher to set channel mode t (topiclock).
					clientMsg << server.getServerName() << " 482 " << nickname << " #" << channelName << " :You must be a channel op or higher to set channel mode t (topiclock).";
				}
				break ;
            }
			default:
			{
				clientMsg << ":irc.local 472 " << nickname << " " << bMode[i] << " :is not a recognised channel mode.";
				break ;
			}//:nickname1!root@127.0.0.1 MODE #a +klo(isgetmode) 12345678(저장) 4(저장) :nickname3(저장)
			//에러메시지 add
			//changeMode 를 돌리기 add
			for (int i = 0; i < userSockets.size(); ++i)
			{
				std::stringstream succeseMsg;
				succeseMsg << server.getServerName() << " MODE #" << channelName << channel->getActiveMode() << " " << "<password>" << " " << "숫자" << " ";
				std::vector< std::pair <int, std::string> >
			}
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
