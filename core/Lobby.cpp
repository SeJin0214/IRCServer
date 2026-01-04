/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lobby.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:48:49 by sejjeong          #+#    #+#             */
/*   Updated: 2026/01/05 02:44:59 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <cstring>
#include <string>
#include "Lobby.hpp"
#include "ErrorCommand.hpp"

IOutgoingMessageProvider* Lobby::getOutgoingMessageProvider(const char* buffer) const
{
	assert(buffer != NULL);
	IOutgoingMessageProvider* provider = Space::getOutgoingMessageProvider(buffer);
	if (provider != NULL)
	{
		return provider;
	}
	return new ErrorCommand();
}

IExecutable* Lobby::getExecutor(const char* buffer) const
{
	assert(buffer != NULL);
	IExecutable* executor = Space::getExecutor(buffer);
	if (executor != NULL)
	{
		return executor;
	}
	return NULL;

}