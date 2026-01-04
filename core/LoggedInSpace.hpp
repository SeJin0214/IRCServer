/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoggedInSpace.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:11:43 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/07 15:24:29 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Space.hpp"
#include "LoginInfo.hpp"

class LoggedInSpace : public Space
{
	
public:
	~LoggedInSpace() override = default;
	IOutgoingMessageProvider* getOutgoingMessageProvider(const char* buffer) const override;
	IExecutable* getExecutor(const char* buffer) const override;
	bool enterUser(const int clientSocket, User* user) override;
	User* exitUserOrNull(const int clientSocket) override;
	void admitOrExile(Server& server);
	/* setter */
	bool trySetAuthenticated(const int clientSocket);
	bool trySetNickname(const int clientSocket, const std::string& nickname);
	bool trySetUsername(const int clientSocket, const std::string& username);
	
private:
	std::map<int, LoginInfo> mInfos;

};
