/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhoCommand.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:00:57 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/04 20:59:24 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IOutgoingMessageProvider.hpp"

class WhoCommand : public IOutgoingMessageProvider
{
public:
 
    Message getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer);
      std::vector<std::pair<int, std::string> > getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer) const;
 
};