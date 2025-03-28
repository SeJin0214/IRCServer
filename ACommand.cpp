/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:19:08 by sejjeong          #+#    #+#             */
/*   Updated: 2025/03/28 12:28:44 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ACommand.hpp"

ACommand::ACommand(const std::string messageToSend, const std::vector<int>& clientSockets)
: mMessageToSend(messageToSend)
, mClientSockets(clientSockets)
{
	
}

std::string ACommand::getMessageToSend()
{
	return mMessageToSend;
}

std::vector<int> ACommand::getClientSockets()
{
	return mClientSockets;
}