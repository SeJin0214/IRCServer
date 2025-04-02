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
#include "IOutgoingMessageProvider.hpp"
#include "IIncomingMessageProvider.hpp"
#include "IExecutable.hpp"

class InviteCommand : public IOutgoingMessageProvider, public IIncomingMessageProvider, public IExecutable
{

public:
    std::string getOutgoingMessage(const Server& server, const int clientSocket, const char* buffer);
    std::string getIncomingMessage(const Server& server, const int clientSocket, const char* buffer);
    std::vector<int> getTargetSockets(const Server& server, const int clientSocket, const char* buffer);
    void execute(Server& server, const int clientSocket, const char* buffer);

};