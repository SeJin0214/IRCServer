/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:36:20 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 19:30:19 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <cstring>
#include <cstddef>
#include "UserCommand.hpp"
#include "Server.hpp"

void UserCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	assert(std::strncmp(buffer, "USER ", std::strlen("USER ")) == 0);
	
	size_t startIndex = std::strlen("USER ");
	char formattedString[MAX_BUFFER] = { 0, };
	strcpy(formattedString, buffer + startIndex);
	formattedString[std::strlen(formattedString) - 1] = '\0';

	assert(std::strncmp(formattedString, buffer + startIndex, std::strlen(formattedString)) == 0);
	char* username = strtok(formattedString, " ");
	server.trySetUsernameInLoggedSpace(clientSocket, username);
}
