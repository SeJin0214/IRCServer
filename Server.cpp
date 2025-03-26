/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:40:43 by sejjeong          #+#    #+#             */
/*   Updated: 2025/03/26 15:54:01 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>
#include "Server.hpp"
#include "Space.hpp"
#include "Util.hpp"
#define SYSCALL_FAIL (-1)

Server::Server(const char* port, const char* password)
: mbRunning(false)
, mPort(std::atoi(port))
, mPassword(Util::generateHash65599(password))
{
	if (isInvalidPortNumber(port))
	{
		std::cerr << "옳지 않은 port 번호, 6660~6670 사이로 넣어야 합니다." << std::endl;
		exit(EXIT_FAILURE);
	}
	else if (isInvalidPassword(password))
	{
		std::cerr << "비밀번호는 8~16자리, 대소문자, 숫자로만 이루어져야합니다." << std::endl;
		exit(EXIT_FAILURE);
	}

	mServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mServerSocket == SYSCALL_FAIL)
	{
		std::cerr << "fail socket" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	int on = 1;
	if (setsockopt(mServerSocket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int)) == -1)
	{
		std::cerr << "fail setsocketopt" << std::endl;
		exit(EXIT_FAILURE);
	}

	sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(sockaddr_in));
	serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(mPort);
	if (bind(mServerSocket, (const sockaddr *)&serverAddr, sizeof(sockaddr_in)) == SYSCALL_FAIL)
	{
		std::cerr << "fail bind" << std::endl;
		exit(EXIT_FAILURE);
	}

	const size_t MAX_PENDING_CONNECTIONS = 100;
	if (listen(mServerSocket, MAX_PENDING_CONNECTIONS) == SYSCALL_FAIL)
	{
		std::cerr << "fail listen" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	std::cout << "서버가 " << mPort << " 포트에서 실행 중입니다..." << std::endl;
}

Server::~Server()
{
	close(mServerSocket);
	mbRunning = false;
}

/* getter */
fd_set Server::getFdSet() const
{
	fd_set master;
	
	FD_ZERO(&master);
	
	FD_SET(mServerSocket, &master);
	FD_SET(STDIN_FILENO, &master);
	std::map<std::string, Channel>::const_iterator it = mChannels.begin();
	while (it != mChannels.end())
	{
		std::vector<int> fdSet = it->second.getFdSet();
		for (size_t i = 0; i < fdSet.size(); ++i)
		{
			FD_SET(fdSet[i], &master);
		}
		++it;
	}
	std::vector<int> fdSet = lobby.getFdSet();
	for (size_t i = 0; i < fdSet.size(); ++i)
	{
		FD_SET(fdSet[i], &master);
	}
	++it;
	return master;
}

int Server::getMaxFd() const
{
	int maxFd = 0;

	std::map<std::string, Channel>::const_iterator it = mChannels.begin();
	while (it != mChannels.end())
	{
		std::vector<int> fdSet = it->second.getFdSet();
		for (size_t i = 0; i < fdSet.size(); ++i)
		{
			if (fdSet[i] > maxFd)
			{
				maxFd = fdSet[i];
			}
		}
		++it;
	}
	std::vector<int> fdSet = lobby.getFdSet();
	for (size_t i = 0; i < fdSet.size(); ++i)
	{
		if (fdSet[i] > maxFd)
		{
			maxFd = fdSet[i];
		}
	}
	return maxFd;
}

bool Server::run()
{
	mbRunning = true;
	
	while (mbRunning)
	{
		fd_set temp_fds = getFdSet();
		int maxFd = getMaxFd();
		if (select(maxFd + 1, &temp_fds, NULL, NULL, NULL) == SYSCALL_FAIL)
		{
			assert(false);
		}
		
		for (int i = 0; i < maxFd; ++i)
		{
			if (FD_ISSET(i, &temp_fds) == false)
			{
				continue;
			}
			else if (i == mServerSocket)
			{
				acceptClient();
			}
			else if (i == STDIN_FILENO)
			{
				// 서버 콘솔에서 입력 처리
				// 서버 운영자 명령어
			}
			else
			{
				// 클라 메시지
				// 채널에게만 메시지를 보내기
				
				// dm 보내는 거 
				// /r 보통 이런 문자열로 함 
				// 운영자일 경우 뭐어쩌구저쩌구
				// 
			}
		}
	}
	return (true);
}

void Server::acceptClient()
{
	struct sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
	const int clientSocket = accept(mServerSocket, (struct sockaddr *)&clientAddr, &clientLen);
	if (clientSocket < 0)
	{
		std::cerr << "클라이언트 연결 실패" << std::endl;
		assert(false);
		return;
	}

	const char* message = "password 를 입력해주세요.\r\n";
	sendToClient(clientSocket, message);

	char buffer[MAX_BUFFER] = { 0, };

	if (attemptReceiveValidData(clientSocket, buffer, &Server::isInvalidPassword) 
	&& mPassword == Util::generateHash65599(buffer))
    {
		char clientIP[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
		std::cout << "클라이언트 연결: " << clientIP << ":" << ntohs(clientAddr.sin_port) << std::endl;

		const char* welcomMessage = "IRC 서버에 오신 것을 환영합니다!\r\n";
		sendToClient(clientSocket, welcomMessage);
		if (acceptUser(clientSocket) == false)
		{
			close(clientSocket);
			return;
		}
	}
	else
	{
		const char* refusalMessage = "password가 일치 하지 않습니다. 다시 시도해 주세요.\r\n";
		sendToClient(clientSocket, refusalMessage);
		close(clientSocket);
	}
}



bool Server::acceptUser(const int clientSocket)
{
	const char* welcomMessage = "Username을 입력해주세요.\r\n";
	sendToClient(clientSocket, welcomMessage);
	char buffer[MAX_BUFFER] = {	0, };
	
	if (attemptReceiveValidData(clientSocket, buffer, &Server::isDuplicatedUsername) == false)
	{
		return false;
	}

	std::string username = buffer;

	if (attemptReceiveValidData(clientSocket, buffer, &Server::isDuplicatedNickname) == false)
	{
		return false;
	}

	std::string nickname = buffer;

	User user(username, nickname);
	lobby.enterUser(clientSocket, user);
	
	sendToClient(clientSocket, lobby.getHelpMessage().c_str());
	return true;
}

/**
 *  recv max 512 byte
*/
bool Server::attemptReceiveValidData(int clientSocket, char *buffer, bool (Server::*isInvalid)(const char *) const)
{
	const size_t MAX_COUNT = 3;
	size_t i = 0;
	for (i = 0; i < MAX_COUNT; ++i)
	{
		const int readLength = recv(clientSocket, buffer, MAX_BUFFER, 0);
		buffer[MAX_BUFFER - 1] = '\0';

		clearStream(clientSocket);

		if (readLength < 0)
		{
			std::cerr << "데이터 수신 실패" << std::endl;
			close(clientSocket);
			assert(false);
			return false;
		}
		if ((this->*isInvalid)(buffer))
		{
			continue;
		}
	}
	if (i == MAX_COUNT)
	{
		return false;
	}
	return true;
}

void Server::clearStream(int socket)
{
	char buffer[MAX_BUFFER] = { 0, };
	while (recv(socket, buffer, sizeof(buffer), 0) > 0)
	{
		continue;
	}
}

void Server::stop()
{
	mbRunning = false;
}

bool Server::isDuplicatedUsername(const char* buffer) const
{
	(void) buffer;
	return (false);
}

bool Server::isDuplicatedNickname(const char* buffer) const
{
	(void) buffer;
	return (false);
}

bool Server::sendToClient(int clientSocket, const char* message)
{
    send(clientSocket, message, std::strlen(message), 0);
	// 에러 처리
	return (true);
}

bool Server::isInvalidPortNumber(const char* port) const
{
	(void) port;
	return (false);
}

// 8 ~ 16  min Uppercase, lowercase, digit
bool Server::isInvalidPassword(const char* password) const
{
    const int length = std::strlen(password);
    if (length < 8  || length > 16)
    {
        return true;
    }
    for (int i = 0; i < length; ++i)
    {
        if (!(std::isalnum(password[i]) || std::isupper(password[i])))
        {
            return true;
        }
    }
    return false;
}
