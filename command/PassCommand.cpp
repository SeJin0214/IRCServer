/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:44:17 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/06 15:03:18 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <cstring>
#include "Util.hpp"
#include "PassCommand.hpp"

#include <iostream>
void PassCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	assert(std::strncmp(buffer, "PASS ", std::strlen("PASS ")) == 0);
	
	size_t startIndex = std::strlen("PASS ");
	char temp[MAX_BUFFER] = { 0, };
	strcpy(temp, buffer + startIndex);

	assert(std::strncmp(temp, buffer + startIndex, std::strlen(temp)) == 0);
	if (Util::generateHash65599(temp) == server.getPassword())
	{
		server.trySetAuthenticatedInLoggedSpace(clientSocket);
	}
}
