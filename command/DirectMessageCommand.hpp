/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectMessageCommand.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:21:16 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/03 12:53:36 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IOutgoingMessageProvider.hpp"

class DirectMessageCommand : public IOutgoingMessageProvider
{

public:
    std::map<int, std::string> getSocketAndMessages(Server& server, const int clientSocket, const char* buffer);

};