/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelCommandShower.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:03:14 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/02 11:04:29 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IIncomingMessageProvider.hpp"

class ChannelCommandShower : public IIncomingMessageProvider
{
public:
    std::string getIncomingMessage(const Server& server, const int clientSocket, const char* buffer);

};