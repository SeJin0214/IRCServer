/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:19:57 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/06 21:56:10 by sejjeong         ###   ########.fr       */
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
	void setPassword(std::string& password);
	bool isPassword(std::string& password);
	bool isInvited (std::string& invitedUser);
	void enterInvitedList (std::string& invitedUser);
	void exitInvitedList (std::string& invitedUser);
	bool isAddUserAsAdmin(const std::string& userNickname);//서버에서 채널생성할 때 사용 유저 호스트만들기
	std::string getActiveMode();
	bool isModeActive(const eMode mode);
	bool onMode(const int userSocket, const eMode mode);
	bool offMode(const int userSocket, const eMode mode);
	bool enterUser(const int clientSocket, const User& user);
	void exitUser(const int clientSocket);
	bool isOperator(const User& user) const;
	bool isOperator(const int userSocket) const;
	void setMemberCount(unsigned int num);
	unsigned int getMemberCount() const;
 
private:
	std::vector<std::string> mOperatorNicknames;
	std::vector<std::string> mInvitedList;
	unsigned int mMemberCount;
	unsigned char mModeFlag;
	std::string mTitle;
	std::string mTopic;
	unsigned int mPassword;
};