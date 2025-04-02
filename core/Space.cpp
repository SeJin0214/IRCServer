/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Space.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:52:43 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/02 11:10:48 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IOutgoingMessageProvider.hpp"
#include "IIncomingMessageProvider.hpp"
#include "Space.hpp"

Space::~Space()
{

}

/* getter */
std::vector<int> Space::getFdSet() const
{
	std::vector<int> result;
	std::map<int, User>::const_iterator it = mUsers.begin();
	while (it != mUsers.end())
	{
		result.push_back(it->first);
		++it;
	}
	return result;
}

std::string Space::getHelpMessage() const
{
	std::string message = "'/' 문자로 시작되는 모든 메시지가 명령어로 해석됩니다. /command를 입력하여 명령어를 확인하세요!\n다시 확인하고 싶으시다면 /help 를 입력하세요.\r\n";
	
	return message;
}

std::string Space::getCommonCommandList() const
{
	// 공통 : 
	// 귓속말을 하고 싶다면 무슨 입력을 하세요. 
	// 유저 목록 확인
	// 전체 유저, 채널 유저
	return "";
}

std::vector<std::string> Space::getNicknames() const
{
	std::vector<std::string> result;
	std::map<int, User>::const_iterator it = mUsers.begin();
	while (it != mUsers.end())
	{
		result.push_back(it->second.getNickname());
		++it;
	}
	return result;
}

std::vector<std::string> Space::getUsernames() const
{
	std::vector<std::string> result;
	std::map<int, User>::const_iterator it = mUsers.begin();
	while (it != mUsers.end())
	{
		result.push_back(it->second.getUsername());
		++it;
	}
	return result;
}

std::vector<int> Space::getClientSockets() const
{
	std::vector<int> result;
	std::map<int, User>::const_iterator it = mUsers.begin();
	while (it != mUsers.end())
	{
		result.push_back(it->first);
		++it;
	}
	return result;
}

bool Space::enterUser(int clientSocket, User& user)
{
	mUsers.insert(std::pair<int, User>(clientSocket, user));
	return true;
}

void Space::exitUser(int clientSocket)
{
	mUsers.erase(clientSocket);
	//  user 반환하기? pair로 반환하기?
}

Result<User> Space::findUser(const int clientSocket) const
{
	std::map<int, User>::const_iterator it = mUsers.find(clientSocket);
	if (it != mUsers.end())
	{
		Result<User> result(it->second, true);
		return result;
	}
	else
	{
		Result<User> result(it->second, false);
		return result;	
	}
}
