/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Space.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:51:10 by sejjeong          #+#    #+#             */
/*   Updated: 2026/01/06 09:20:32 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <map>
#include <vector>
#include <memory>
#include "User.hpp"
#include "Result.hpp"

class IOutgoingMessageProvider;
class IExecutable;

class Space
{
public:
	virtual ~Space() = default;
	/* getter */
	virtual std::shared_ptr<IOutgoingMessageProvider> getOutgoingMessageProvider(const char* buffer) const = 0;
	virtual std::shared_ptr<IExecutable> getExecutor(const char* buffer) const = 0;
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
