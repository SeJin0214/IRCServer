/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandShower.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:10:29 by sejjeong          #+#    #+#             */
/*   Updated: 2025/03/31 17:10:29 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IIncomingMessageProvider.hpp"

class CommandShower : public IIncomingMessageProvider
{
public:
    std::string getIncomingMessage(const Server& server, const int clientSocket, const char* buffer);

};