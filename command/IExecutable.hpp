/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IExecutable.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:38:54 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/04 20:59:44 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Server;

class IExecutable
{

public:
	virtual ~IExecutable() {};
	virtual void execute(Server& server,  const int clientSocket, const char* buffer) = 0;

};