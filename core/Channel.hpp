/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:19:57 by sejjeong          #+#    #+#             */
/*   Updated: 2026/01/05 02:47:54 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include "Space.hpp"
#include "Mode.hpp"

class Channel : public Space
{

public:
	~Channel() override = default;
	Channel(const std::string& title, const char* password);
	Channel(const Channel&) = delete;
	Channel& operator=(const Channel&) = delete;

	IOutgoingMessageProvider* getOutgoingMessageProvider(const char* buffer) const override;
	IExecutable* getExecutor(const char* buffer) const override;
	bool operator<(const Channel& rhs) const;
	std::string getTitle() const;
	std::string getTopic() const;
	bool setTopic(int clientSocket, const std::string& topic);
	unsigned int getPassword() const;

	void setPassword(const std::string& password);
	bool isPassword(const std::string& password) const;
	bool isInvited(const std::string& invitedUser) const;

	void enterInvitedList (const std::string& invitedUser);
	void exitInvitedList (const std::string& invitedUser);
	bool isAddUserAsAdmin(const std::string& userNickname);
	void removeOperatorNicknames(const std::string& nickname);
	void removeInvitedLists(const std::string& nickname);
	std::string getActiveMode() const;
	bool isModeActive(const eMode mode) const;
	bool onMode(const int userSocket, const eMode mode);
	bool offMode(const int userSocket, const eMode mode);
	bool enterUser(const int clientSocket, User* user) override;
	User* exitUserOrNull(const int clientSocket) override;
	bool isOperator(const User& user) const;
	bool isOperator(const int userSocket) const;
	void setMaxMemberCount(unsigned int num);
	size_t getMaxMemberCount() const;
 
private:
	std::vector<std::string> mOperatorNicknames;
	std::vector<std::string> mInvitedList;
	unsigned int mMaxMemberCount;
	unsigned char mModeFlag;
	std::string mTitle;
	std::string mTopic;
	unsigned int mPassword;
};
