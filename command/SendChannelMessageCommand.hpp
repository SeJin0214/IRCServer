/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendChannelMessageCommand.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:23:53 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/02 11:26:05 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IOutgoingMessageProvider.hpp"
#include "IIncomingMessageProvider.hpp"

class SendChannelMessageCommand : public IOutgoingMessageProvider, public IIncomingMessageProvider
{

public:
    std::string getOutgoingMessage(const Server& server, const int clientSocket, const char* buffer);
    std::string getIncomingMessage(const Server& server, const int clientSocket, const char* buffer);
    std::vector<int> getTargetSockets(const Server& server, const int clientSocket, const char* buffer);

};