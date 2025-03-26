/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Space.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:50:56 by sejjeong          #+#    #+#             */
/*   Updated: 2025/03/26 15:23:08 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <map>
#include <vector>
#include "User.hpp"

class Space
{
public:
	virtual ~Space();
	virtual std::string getCommandList() const = 0;
	std::string getHelpMessage() const;
	std::string getCommonCommandList() const;
	bool enterUser(int clientSocket, User& user);
	std::vector<int> getFdSet() const;
	
protected:
	std::map<int, User> mUsers;
};
