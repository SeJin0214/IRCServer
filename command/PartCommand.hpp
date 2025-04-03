/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:41:14 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/03 12:17:12 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IOutgoingMessageProvider.hpp"

class PartCommand : public IOutgoingMessageProvider
{
public:
    std::map<int, std::string> getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer);
    
};