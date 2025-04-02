/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOutgoingMessageProvider.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:33:05 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/02 11:12:37 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <string>
#include <vector>
#include "Server.hpp"
#include <iostream>
class IOutgoingMessageProvider
{
public:
	virtual ~IOutgoingMessageProvider() {};
	virtual std::string getOutgoingMessage(const Server& server, const int clientSocket, const char* buffer) = 0;
	virtual std::vector<int> getTargetSockets(const Server& server, const int clientSocket, const char* buffer) = 0;
};