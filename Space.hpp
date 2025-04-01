/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Space.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:50:56 by sejjeong          #+#    #+#             */
/*   Updated: 2025/03/31 17:05:10 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <map>
#include <vector>
#include "IMessageCommunicator.hpp"
#include "IExecutable.hpp"
#include "User.hpp"
#include "Result.hpp"

class Space
{
public:
	virtual ~Space();
	/* getter */
	virtual IMessageCommunicators* getMessageCommunicator(const char* buffer) = 0;
	virtual IExecutable* getExecutor(const char* buffer) = 0;
	std::string getHelpMessage() const;
	std::string getCommonCommandList() const;
	std::vector<int> getFdSet() const;
	std::vector<int> getClientSockets() const;
	std::vector<std::string> getNicknames() const;
	std::vector<std::string> getUsernames() const;
	
	Result<User> findUser(const int clientSocket) const;
	bool enterUser(int clientSocket, User& user);
	void exitUser(int clientSocket);

protected:
	std::map<int, User> mUsers; // <int, User *>
	// test 
};
