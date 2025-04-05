/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOutgoingMessageProvider.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:33:05 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/04 20:59:42 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <string>
#include <map>
#include "Server.hpp"
#include <iostream>
#include "Message.hpp"
#include "CommonCommand.hpp"
#include <sstream>
class IOutgoingMessageProvider
{
public:
	virtual ~IOutgoingMessageProvider() {};
 
	// 여러 줄을 보내야 한다면
	// message class를 하나 만들어야 한다.
	
	virtual Message getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer) = 0;
  	virtual std::vector<std::pair<int, std::string> > getSocketAndMessages(const Server& server, const int clientSocket, const char* buffer) const = 0;
 };