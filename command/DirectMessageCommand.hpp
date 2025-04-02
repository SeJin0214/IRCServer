/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectMessageCommand.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:21:16 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/02 11:25:47 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IOutgoingMessageProvider.hpp"
#include "IIncomingMessageProvider.hpp"

class DirectMessageCommand : public IOutgoingMessageProvider, public IIncomingMessageProvider
{

public:
    std::string getOutgoingMessage(const Server& server, const int clientSocket, const char* buffer);
    std::string getIncomingMessage(const Server& server, const int clientSocket, const char* buffer);
    std::vector<int> getTargetSockets(const Server& server, const int clientSocket, const char* buffer);

};