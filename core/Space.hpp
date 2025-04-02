/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Space.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:50:56 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/02 13:11:35 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <map>
#include <vector>
#include "IExecutable.hpp"
#include "User.hpp"
#include "Result.hpp"

class IIncomingMessageProvider;
class IOutgoingMessageProvider;

class Space
{
public:
	virtual ~Space();
	/* getter */
	virtual IOutgoingMessageProvider* getOutgoingMessageProvider(const char* buffer) = 0;
	virtual IIncomingMessageProvider* getIncomingMessageProvider(const char* buffer) = 0;
	virtual IExecutable* getExecutor(const char* buffer) = 0;
	std::vector<int> getFdSet() const;
	std::vector<int> getClientSockets() const;
	std::vector<std::string> getNicknames() const;
	std::vector<std::string> getUsernames() const;
	
	Result<User> findUser(const int clientSocket) const;
	bool enterUser(int clientSocket, User& user);
	void exitUser(int clientSocket);

protected:
	std::map<int, User> mUsers; // <int, User *>


};
