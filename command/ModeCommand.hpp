/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:37:32 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/03 11:37:45 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IOutgoingMessageProvider.hpp"

class ModeCommand : public IOutgoingMessageProvider
{
public:
    std::map<int, std::string> getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer);
    
};