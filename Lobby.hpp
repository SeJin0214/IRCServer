/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lobby.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:01:32 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/01 18:42:35 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Space.hpp"

class Lobby : public Space
{

public:
	virtual ~Lobby();
	std::string getCommandList() const;
	IMessageCommunicator* getMessageCommunicator(const char* buffer);
	IExecutable* getExecutor(const char* buffer);
private:

};