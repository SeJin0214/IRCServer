/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommonCommand.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:08:38 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 13:37:50 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "User.hpp"

class CommonCommand
{
public:
	static std::string getPrefixMessage(const User& user, const int clientSocket);
};
