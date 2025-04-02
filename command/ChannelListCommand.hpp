/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelListCommand.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:29:46 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/02 11:46:46 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IIncomingMessageProvider.hpp"

class ChannelListCommand : public IIncomingMessageProvider
{
public:
    std::string getIncomingMessage(const Server& server, const int clientSocket, const char* buffer);

};