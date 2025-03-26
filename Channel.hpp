/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:19:57 by sejjeong          #+#    #+#             */
/*   Updated: 2025/03/26 15:37:25 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Space.hpp"
#include "Mode.hpp"

class Channel : public Space
{

public:
	virtual ~Channel();
	std::string getCommandList() const;
	Channel(const std::string& title, const char* password);
	bool operator<(const Channel& rhs);
	std::string getTitle() const;
	unsigned int getPassword() const;
	std::vector<std::string> getNicknames() const;
	std::vector<std::string> getUsernames() const;
	bool toggleMode(User& user, const eMode mode);
	bool isOperator(const User& user);
private:
	std::vector<std::string> mOperators;
	unsigned char mModeFlag;
	std::string mTitle;
	unsigned int mPassword;
};
