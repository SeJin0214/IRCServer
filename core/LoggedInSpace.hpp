/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoggedInSpace.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:11:43 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 13:37:59 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Space.hpp"

class LoggedInSpace : public Space
{
	
public:
	IOutgoingMessageProvider* getOutgoingMessageProvider(const char* buffer) const;
	IExecutable* getExecutor(const char* buffer) const;
};