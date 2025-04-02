/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lobby.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:02:15 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/02 10:53:23 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "Lobby.hpp"

Lobby::~Lobby()
{
	
}

std::string Lobby::getCommandList() const
{
	return "";
}

IOutgoingMessageProvider* Lobby::getOutgoingMessageProvider(const char* buffer)
{
	assert(buffer != NULL);
	return NULL;
}

IIncomingMessageProvider* Lobby::getIncomingMessageProvider(const char* buffer)
{
	assert(buffer != NULL);
	return NULL;
}

IExecutable* Lobby::getExecutor(const char* buffer)
{
	assert(buffer != NULL);
	return NULL;

}