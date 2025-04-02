/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Util.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:54:10 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/02 10:51:49 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "Util.hpp"

unsigned int Util::generateHash65599(const char* str)
{
	assert(str != NULL);
	unsigned int	hash = 0;

	for (size_t i = 0; str[i] != '\0'; ++i)
	{
		hash = 65599 * hash + str[i];
	}
	return (hash ^ (hash >> 16));
}
