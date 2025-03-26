/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:20:19 by sejjeong          #+#    #+#             */
/*   Updated: 2025/03/26 15:42:49 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include "Channel.hpp"
#include "Util.hpp"

Channel::Channel(const std::string& title, const char* password) 
: mTitle(title)
, mPassword(Util::generateHash65599(password))
{
	
}

Channel::~Channel()
{

}

bool Channel::operator<(const Channel& rhs)
{
	return mTitle < rhs.mTitle;
}

/* getter */
std::string Channel::getTitle() const
{
	return mTitle;
}

unsigned int Channel::getPassword() const
{
	return mPassword;
}

std::vector<std::string> Channel::getNicknames() const
{
	std::vector<std::string> result;
	std::map<int, User>::const_iterator it = mUsers.begin();
	while (it != mUsers.end())
	{
		result.push_back(it->second.getNickname());
		++it;
	}
	return result;
}
	
std::vector<std::string> Channel::getUsernames() const
{
	std::vector<std::string> result;
	std::map<int, User>::const_iterator it = mUsers.begin();
	while (it != mUsers.end())
	{
		result.push_back(it->second.getUsername());
		++it;
	}
	return result;
}

std::string Channel::getCommandList() const
{
	return "";
}

bool Channel::toggleMode(User& user, const eMode mode)
{
	if (isOperator(user) == false)
	{
		return false;
	}
	const unsigned char bitFlag = 1 << mode;
	mModeFlag ^= bitFlag;
	return true;
}

bool Channel::isOperator(const User& user)
{
	for (std::map<int, User>::const_iterator it = mUsers.begin(); it != mUsers.end(); ++it)
	{
		if (it->second.getUsername() == user.getUsername())
		{
			return true;
		}
	}
	return false;
}
