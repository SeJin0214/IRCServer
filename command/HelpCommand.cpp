/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HelpCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:26:49 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/02 11:27:27 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "HelpCommand.hpp"

std::string HelpCommand::getIncomingMessage(const Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
	return "";
}
