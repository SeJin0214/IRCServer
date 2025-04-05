/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorCommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:53:02 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 13:37:51 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "ErrorCommand.hpp"

std::vector<std::pair<int, std::string> > ErrorCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
	return std::vector<std::pair<int, std::string> >();
}
