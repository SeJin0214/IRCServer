/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lobby.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:02:15 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/02 13:14:45 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "Lobby.hpp"

Lobby::~Lobby()
{
	
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