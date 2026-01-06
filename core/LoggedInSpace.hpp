/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoggedInSpace.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:11:43 by sejjeong          #+#    #+#             */
/*   Updated: 2026/01/06 09:22:21 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Space.hpp"
#include "LoginInfo.hpp"

class Server;

class LoggedInSpace : public Space
{
	
public:
	~LoggedInSpace() override = default;
	std::shared_ptr<IOutgoingMessageProvider> getOutgoingMessageProvider(const char* buffer) const override;
	std::shared_ptr<IExecutable> getExecutor(const char* buffer) const override;
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
