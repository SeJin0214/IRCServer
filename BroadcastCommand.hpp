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
#include "IOutgoingMessageProvider.hpp"

class BroadcastCommand : public IOutgoingMessageProvider
{
    std::string getOutgoingMessage(const Server& server, const int clientSocket, const char* buffer);
    std::vector<int> getTargetSockets(const Server& server, const int clientSocket, const char* buffer);
};