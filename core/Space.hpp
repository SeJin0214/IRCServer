/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Space.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:50:56 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/03 10:40:09 by sejjeong         ###   ########.fr       */
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
	virtual IOutgoingMessageProvider* getOutgoingMessageProvider(const char* buffer);
	virtual IExecutable* getExecutor(const char* buffer);
	std::vector<int> getFdSet() const;
	std::vector<int> getClientSockets() const;
	std::vector<std::string> getNicknames() const;
	std::vector<std::string> getUsernames() const;
	Result<User> findUser(const int clientSocket) const;
	Result<std::pair<int, User> > findUser(std::string nickname) const;
	bool enterUser(int clientSocket, User& user);
	void exitUser(int clientSocket);

protected:
	Space() {};
	std::map<int, User> mUsers; // <int, User *>

};
