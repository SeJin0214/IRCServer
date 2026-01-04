/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Space.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:51:10 by sejjeong          #+#    #+#             */
/*   Updated: 2026/01/05 02:51:27 by sejjeong         ###   ########.fr       */
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
	virtual ~Space() = default;
	/* getter */
	virtual IOutgoingMessageProvider* getOutgoingMessageProvider(const char* buffer) const;
	virtual IExecutable* getExecutor(const char* buffer) const;
	virtual bool enterUser(const int clientSocket, User* user);
	virtual User* exitUserOrNull(const int clientSocket);
	std::vector<int> getFdSet() const;
	size_t getUserCount() const;
	std::vector<std::string> getNicknames() const;
	std::vector<std::string> getUsernames() const;
	User* findUserOrNull(const int clientSocket) const;
	Result<std::pair<int, User*> > findUser(const std::string& nickname) const;

protected:
	Space() = default;
	Space(const Space&) = delete;
	Space& operator=(const Space&) = delete;
	std::map<int, User*> mUsers;
  	std::string getCommandSection(const char* buffer) const;

 };
