/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMessageCommunicator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:15:59 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/01 18:41:57 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>

class Server;

class IMessageCommunicator
{
public:
	virtual ~IMessageCommunicator() {};
	virtual std::string getMessageToSend(const Server& server, const int clientSocket, const char* buffer) = 0;
	virtual std::string getMessageToRecive(const Server& server, const int clientSocket, const char* buffer) = 0;
	virtual std::vector<int> getTargetSockets(const Server& server, const int clientSocket, const char* buffer) = 0;

};