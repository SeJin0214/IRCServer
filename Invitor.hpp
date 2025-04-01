/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invitor.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:45:30 by sejjeong          #+#    #+#             */
/*   Updated: 2025/03/31 18:45:30 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IMessageCommunicator.hpp"
#include "IExecutable.hpp"

class Invitor : public IMessageCommunicator, public IExecutable
{

public:
    std::string getMessageToSend(const Server& server, const int clientSocket, const char* buffer);
    std::string getMessageToRecive(const Server& server, const int clientSocket, const char* buffer);
    std::vector<int> getTargetSockets(const Server& server, const int clientSocket, const char* buffer);
    void execute(Server& server, const int clientSocket, const char* buffer);

};