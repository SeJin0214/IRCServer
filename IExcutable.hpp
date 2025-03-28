/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IExcutable.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:38:54 by sejjeong          #+#    #+#             */
/*   Updated: 2025/03/28 11:41:52 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Server.hpp"

class IExcutable
{

public:
	virtual void execute(Server& server) = 0;

};