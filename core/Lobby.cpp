/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lobby.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:02:15 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/02 15:07:36 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <cstring>
#include "Lobby.hpp"

Lobby::~Lobby()
{
	
}

IOutgoingMessageProvider* Lobby::getOutgoingMessageProvider(const char* buffer)
{
	assert(buffer != NULL);
	IOutgoingMessageProvider* provider = Space::getOutgoingMessageProvider(buffer);
	if (provider != NULL)
	{
		return provider;
	}

	std::string command = getCommandSection(buffer);
	return NULL;
}

IIncomingMessageProvider* Lobby::getIncomingMessageProvider(const char* buffer)
{
	assert(buffer != NULL);
	IIncomingMessageProvider* provider = Space::getIncomingMessageProvider(buffer);
	if (provider != NULL)
	{
		return provider;
	}
	
	std::string command = getCommandSection(buffer);
	return NULL;
}

IExecutable* Lobby::getExecutor(const char* buffer)
{
	assert(buffer != NULL);
	IExecutable* executor = Space::getExecutor(buffer);
	if (executor != NULL)
	{
		return executor;
	}
	
	std::string command = getCommandSection(buffer);
	return NULL;

}