/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HelpCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:47:17 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/02 12:47:17 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IIncomingMessageProvider.hpp"

class HelpCommand : public IIncomingMessageProvider
{
    
public:
    std::string getIncomingMessage(const Server& server, const int clientSocket, const char* buffer);

};