/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoggedInSpace.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:13:46 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/04 20:59:19 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <cstring>
#include "ErrorCommand.hpp"
#include "LoggedInSpace.hpp"
#include "NickCommand.hpp"
#include "UserCommand.hpp"
#include "PassCommand.hpp"

IOutgoingMessageProvider* LoggedInSpace::getOutgoingMessageProvider(const char *buffer) const
{
	assert(buffer != NULL);

	std::string command = getCommandSection(buffer);
	if (std::strncmp("PASS", command.c_str(), command.size()) == 0)
	{
		return new PassCommand();
	}
	else if (std::strncmp("USER", command.c_str(), command.size()) == 0)
	{
		return new UserCommand();
	}
	else if (std::strncmp("NICK", command.c_str(), command.size()) == 0)
	{
		return new NickCommand();
	}
	// WHOIS??
	return new ErrorCommand();
}

IExecutable* LoggedInSpace::getExecutor(const char *buffer) const
{
	
}