/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:19:57 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/02 13:15:00 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Space.hpp"
#include "Mode.hpp"

class Channel : public Space
{

public:
	virtual ~Channel();
	IOutgoingMessageProvider* getOutgoingMessageProvider(const char* buffer);
	IIncomingMessageProvider* getIncomingMessageProvider(const char* buffer);
	IExecutable* getExecutor(const char* buffer);
	Channel(const std::string& title, const char* password);
	bool operator<(const Channel& rhs);
	std::string getTopic() const;
	bool setTopic(int clientSocket, std::string& title);
	unsigned int getPassword() const;
	bool toggleMode(User& user, const eMode mode);
	// 유저의 이름을 바꾸는 setter

	
private:
	std::vector<std::string> mOperators;
	unsigned char mModeFlag;
	std::string mTopic;
	unsigned int mPassword;
	
	bool isOperator(const User& user) const;
	bool isOperator(const int userSocket) const;
	
};
