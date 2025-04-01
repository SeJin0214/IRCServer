/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lobby.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:02:15 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/01 18:45:46 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lobby.hpp"

Lobby::~Lobby()
{
	
}

std::string Lobby::getCommandList() const
{
	return "";
}

IMessageCommunicator* Lobby::getMessageCommunicator(const char* buffer)
{
	(void) buffer;
	return NULL;
}

IExecutable* Lobby::getExecutor(const char* buffer)
{
		(void) buffer;
	return NULL;

}