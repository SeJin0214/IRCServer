/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IIncomingMessageProvider.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:15:59 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/02 11:12:39 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>
#include "Server.hpp"

class IIncomingMessageProvider
{
public:
	virtual ~IIncomingMessageProvider() {};
	virtual std::string getIncomingMessage(const Server& server, const int clientSocket, const char* buffer) = 0;

};