/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:36:20 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/08 20:47:20 by sejjeong         ###   ########.fr       */
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
	

	// 다 손보기...
	char temp[MAX_BUFFER] = { 0, };
	strcpy(temp, buffer);
	const char* command = std::strtok(temp, " ");
	assert(std::strncmp(command, "USER", std::strlen("USER")) == 0);
	
	const char* username = std::strtok(NULL, " ");
	const char* hostname = std::strtok(NULL, " ");
	const char* servername = std::strtok(NULL, " ");
	// 뒤쪽을 다 갖고와야 함
	const char* realname = std::strtok(NULL, " ");

	if (realname == NULL || servername == NULL || hostname == NULL || username == NULL
	|| server.isInvalidNameFormatted(username))
	{
		return;
	}
	server.trySetUsernameInLoggedSpace(clientSocket, username);
}
