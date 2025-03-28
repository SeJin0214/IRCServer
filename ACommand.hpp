/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:19:06 by sejjeong          #+#    #+#             */
/*   Updated: 2025/03/28 12:26:07 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>

class ACommand
{

public:
	ACommand(const std::string messageToSend, const std::vector<int>& clientSockets);
	virtual std::string getMessageToSend() = 0;
	std::vector<int> getClientSockets();
private:
	std::string mMessageToSend;
	std::vector<int> mClientSockets;
};