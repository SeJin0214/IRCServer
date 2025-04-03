/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lobby.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:48:49 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/03 10:50:54 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <cstring>
#include <string>
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