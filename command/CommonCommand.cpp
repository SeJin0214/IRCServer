/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommonCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:09:53 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 11:47:25 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommonCommand.hpp"

std::string CommonCommand::getPrefixMessage(const User& user, int clientsocket)
{
	return (":"+ user.getNickname() + "!" + user.getUsername() + "@" + getHostIP(clientsocket));
}

std::string CommonCommand::getPrefixMessage(const User& user, const int clientSocket)
{
	(void) user;
	(void) clientSocket;
	return "";
}

std::string CommonCommand::getHostIP(int sockfd)
{
    struct sockaddr_storage addr;
    socklen_t addr_len = sizeof(addr);
    char ip_str[AF_INET];

    // 소켓의 로컬 주소 정보 가져오기
    if (getsockname(sockfd, (struct sockaddr*)&addr, &addr_len) == -1)
	{
        perror("getsockname 실패");
        return;
    }
    
    // IP 주소를 문자열로 변환
    if (addr.ss_family == AF_INET)
	{
        struct sockaddr_in *s = (struct sockaddr_in *)&addr;
        inet_ntop(AF_INET, &s->sin_addr, ip_str, sizeof(ip_str));
	}
	std::string ret(ip_str);
	return (ret);
}