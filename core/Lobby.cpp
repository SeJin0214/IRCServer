/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lobby.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:48:49 by sejjeong          #+#    #+#             */
/*   Updated: 2026/01/12 17:08:45 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <sstream>
#include "Lobby.hpp"
#include "CommandRegistry.hpp"

std::shared_ptr<IOutgoingMessageProvider> Lobby::getOutgoingMessageProvider(const char* buffer) const
{
	assert(buffer != NULL);
	std::string command = getCommandSection(buffer);

	CommandRegistry& instance = CommandRegistry::getInstance();
	Result<std::shared_ptr<IOutgoingMessageProvider> > result = instance.getProviderInLobby(command);
	if (result.hasSucceeded())
	{
		return result.getValue();
	}
	return std::shared_ptr<IOutgoingMessageProvider>();
}

std::shared_ptr<IExecutable> Lobby::getExecutor(const char* buffer) const
{
	assert(buffer != NULL);

	CommandRegistry& instance = CommandRegistry::getInstance();
	std::string command = getCommandSection(buffer);

	Result<std::shared_ptr<IExecutable> > result = instance.getExecutorInLobby(command);
	if (result.hasSucceeded())
	{
		return result.getValue();
	}
	return std::shared_ptr<IExecutable>();
}
