/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:41:48 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/04 21:00:17 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "PartCommand.hpp"

std::vector<std::pair<int, std::string> > PartCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	// lobby에서 입력시 서버 반응 x
	// 127.000.000.001.32790-127.000.000.001.06667: PART #channel
	// 127.000.000.001.06667-127.000.000.001.32790: :donkim3!root@127.0.0.1 PART :#channel

	(void) server;
	(void) clientSocket;
	return std::vector<std::pair<int, std::string> >();
}

void PartCommand::execute(Server& server, const int clientSocket, const char* buffer)
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
}
