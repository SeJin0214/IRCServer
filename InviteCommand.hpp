/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:31:36 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/01 18:31:36 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IMessageCommunicator.hpp"
#include "IExecutable.hpp"

class InviteCommand : public IMessageCommunicator, public IExecutable
{

public:
    std::string getMessageToSend(const Server& server, const int clientSocket, const char* buffer);
    std::string getMessageToRecive(const Server& server, const int clientSocket, const char* buffer);
    std::vector<int> getTargetSockets(const Server& server, const int clientSocket, const char* buffer);
    void execute(Server& server, const int clientSocket, const char* buffer);

};