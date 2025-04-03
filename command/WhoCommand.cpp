/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoCommand.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:01:53 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/03 13:02:45 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "WhoCommand.hpp"

std::map<int, std::string> WhoCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
	return std::map<int, std::string>();
}