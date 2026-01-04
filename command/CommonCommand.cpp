/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommonCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:09:53 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/07 16:46:33 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdio>
#include "CommonCommand.hpp"
#include <arpa/inet.h>

std::string CommonCommand::getPrefixMessage(const User& user, const int clientsocket)
{
	return (":" + user.getNickname() + "!" + user.getUsername() + "@" + getHostIP(clientsocket));
}

std::string CommonCommand::getHostIP(const int sockfd)
{
    struct sockaddr_storage addr;
    socklen_t addr_len = sizeof(addr);
    char ip_str[INET_ADDRSTRLEN];

    if (getsockname(sockfd, (struct sockaddr*)&addr, &addr_len) == -1)
	{
        perror("getsockname 실패");
        return "";
    }
    if (addr.ss_family == AF_INET)
	{
        struct sockaddr_in *s = (struct sockaddr_in *)&addr;
        inet_ntop(AF_INET, &s->sin_addr, ip_str, sizeof(ip_str));
	}
	std::string ret(ip_str);
	return (ret);
}
