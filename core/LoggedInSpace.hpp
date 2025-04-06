/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoggedInSpace.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:11:43 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 16:39:32 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Space.hpp"
#include "LoginInfo.hpp"

class LoggedInSpace : public Space
{
	
public:
	IOutgoingMessageProvider* getOutgoingMessageProvider(const char* buffer) const;
	IExecutable* getExecutor(const char* buffer) const;
	bool enterUser(const int clientSocket, const User& user);
	void exitUser(const int clientSocket);
	void admitOrExile(Server& server);
	/* setter */
	bool trySetAuthenticated(const int clientSocket);
	bool trySetNickname(const int clientSocket, const std::string& nickname);
	bool trySetUsername(const int clientSocket, const std::string& username);
	
private:
	std::map<int, LoginInfo> mInfos;

};