/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lobby.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:01:32 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/03 10:40:28 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Space.hpp"

class Lobby : public Space
{

public:
	virtual ~Lobby();
	IOutgoingMessageProvider* getOutgoingMessageProvider(const char* buffer);
	IExecutable* getExecutor(const char* buffer);
private:

};