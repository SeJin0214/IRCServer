/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lobby.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:01:32 by sejjeong          #+#    #+#             */
/*   Updated: 2026/01/05 02:44:56 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Space.hpp"

class Lobby : public Space
{

public:
	~Lobby() override = default;
	std::shared_ptr<IOutgoingMessageProvider> getOutgoingMessageProvider(const char* buffer) const override;
	std::shared_ptr<IExecutable> getExecutor(const char* buffer) const override;
private:

};
