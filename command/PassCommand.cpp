/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:44:17 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/04 20:59:28 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "PassCommand.hpp"

std::vector<std::pair<int, std::string> > PassCommand::getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer) const
{
	assert(buffer != NULL);
	(void) server;
	(void) clientSocket;
	// 여기서 User를 읽어서, 순서가 올바르지 않으면 튕겨내기
	return std::vector<std::pair<int, std::string> >();
}
