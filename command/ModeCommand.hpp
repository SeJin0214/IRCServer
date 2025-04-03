/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:37:32 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/03 12:49:09 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IExecutable.hpp"
#include "IOutgoingMessageProvider.hpp"

class ModeCommand : public IOutgoingMessageProvider, public IExecutable
{
public:
    std::map<int, std::string> getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer);
    void execute(Server& server, const int clientSocket, const char* buffer);
    
};