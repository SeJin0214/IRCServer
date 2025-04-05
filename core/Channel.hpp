/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:19:57 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 13:37:58 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include "Space.hpp"
#include "Mode.hpp"

class Channel : public Space
{

public:
	virtual ~Channel();
	IOutgoingMessageProvider* getOutgoingMessageProvider(const char* buffer) const;
	IExecutable* getExecutor(const char* buffer) const;
	Channel(const std::string& title, const char* password);
	bool operator<(const Channel& rhs);
	std::string getTitle() const;
	std::string getTopic() const;
	bool setTopic(int clientSocket, std::string& topic);
	unsigned int getPassword() const;
	bool toggleMode(User& user, const eMode mode);
	bool enterUser(const int clientSocket, const User& user);
	void exitUser(const int clientSocket);
	bool isOperator(const User& user) const;
	bool isOperator(const int userSocket) const;

private:
	std::vector<std::string> mOperatorNicknames;
	unsigned char mModeFlag;
	std::string mTitle;
	std::string mTopic;
	unsigned int mPassword;
	
	
};
