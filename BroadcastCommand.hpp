/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BroadcastCommand.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:30:47 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/01 18:30:47 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once
#include "IMessageCommunicator.hpp"

class BroadcastCommand : public IMessageCommunicator
{
    std::string getMessageToSend(const Server& server, const int clientSocket, const char* buffer);
    std::string getMessageToRecive(const Server& server, const int clientSocket, const char* buffer);
    std::vector<int> getTargetSockets(const Server& server, const int clientSocket, const char* buffer);
};