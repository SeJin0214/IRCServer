/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:50:03 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/05 11:38:18 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
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
#include "Result.hpp"
#include "IOutgoingMessageProvider.hpp"
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
	else if (isInvalidPasswordFormatted(password))
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

std::vector<const Space *> Server::getSpaces() const
{
	std::vector<const Space *> spaces;
	for (size_t i = 0; i < mChannels.size(); ++i)
	{
		spaces.push_back(mChannels[i]);
	}
	spaces.push_back(&mLobby);
	spaces.push_back(&mLoggedInSpace);
	return spaces;
}

/* getter */
fd_set Server::getFdSet() const
{
	fd_set master;
	
	FD_ZERO(&master);
	
	FD_SET(mServerSocket, &master);
	FD_SET(STDIN_FILENO, &master);

	std::vector<const Space *> spaces = getSpaces();
	for (size_t i = 0; i < spaces.size(); ++i)
	{
		std::vector<int> fdSet = spaces[i]->getFdSet();
		for (size_t i = 0; i < fdSet.size(); ++i)
		{
			FD_SET(fdSet[i], &master);
		}
	}
	return master;
}

int Server::getMaxFd() const
{
	int maxFd = mServerSocket;

	std::vector<const Space *> spaces = getSpaces();
	for (size_t i = 0; i < spaces.size(); ++i)
	{
		std::vector<int> fdSet = spaces[i]->getFdSet();
		for (size_t i = 0; i < fdSet.size(); ++i)
		{
			if (fdSet[i] > maxFd)
			{
				maxFd = fdSet[i];
			}
		}
	}
	return maxFd;
}

const Space* Server::findSpace(const int clientSocket) const
{
	std::vector<const Space *> spaces = getSpaces();
	for (size_t i = 0; i < spaces.size(); ++i)
	{
		Result<User> result = spaces[i]->findUser(clientSocket);
		if (result.hasSucceeded())
		{
			return spaces[i];
		}
	}
	assert(false);
	return NULL;
}

bool Server::addChannel(const std::string& title)
{
	Channel* existedChannel = findChannelOrNull(title);
	if (existedChannel->getTitle() == title)
	{
		return false;
	}
	Channel* newChannel = new Channel(title, "");
	mChannels.push_back(newChannel);
	return true;
}

Result<User> Server::findUser(const int clientSocket)
{
	for (size_t i = 0; i < mChannels.size(); ++i)
	{
		Result<User> result = mChannels[i]->findUser(clientSocket);
		if (result.hasSucceeded())
		{
			return result;
		}
	}
	Result<User> result = mLobby.findUser(clientSocket);
	if (result.hasSucceeded())
	{
		return result;
	}
	Result<User> emptyUser(User(), false);
	return emptyUser;
}

// return <socket, User>
Result<std::pair<int, User> > Server::findUser(const std::string nickname)
{
	for (size_t i = 0; i < mChannels.size(); ++i)
	{
		Result<std::pair<int, User> > result = mChannels[i]->findUser(nickname);
		if (result.hasSucceeded())
		{
			return result;
		}
	}
	Result<std::pair<int, User> > result = mLobby.findUser(nickname);
	if (result.hasSucceeded())
	{
		return result;
	}
	std::pair<int, User> socketAndUser(-1, User());
	Result<std::pair<int, User> > emptyUser(socketAndUser, false);
	return emptyUser;
}

Channel* Server::findChannelOrNull(const std::string title) const
{
	for (size_t i = 0; i < mChannels.size(); ++i)
	{
		Channel* channel = mChannels[i];
		if (channel->getTitle() == title)
		{
			return channel;
		}
	}
	return NULL;
}

Channel* Server::findChannelOrNull(const int clientSocket) const
{
	for (size_t i = 0; i < mChannels.size(); ++i)
	{
		Channel* channel = mChannels[i];
		Result<User> result = channel->findUser(clientSocket);
		if (result.hasSucceeded())
		{
			return channel;
		}
	}
	return NULL;
}

bool Server::trySetAuthenticatedInLoggedSpace(const int clientSocket)
{
	Channel* channel = findChannelOrNull(clientSocket);
	return channel->trySetAuthenticated(clientSocket);
}

bool Server::trySetNicknameInLoggedSpace(const int clientSocket, const std::string& nickname)
{
	Channel* channel = findChannelOrNull(clientSocket);
	return channel->trySetNickname(clientSocket, nickname);
}

bool Server::trySetUsernameInLoggedSpace(const int clientSocket, const std::string& username)
{
	Channel* channel = findChannelOrNull(clientSocket);
	return channel->trySetUsername(clientSocket, username);
}

bool Server::enterUserInLobby(const int clientSocket, const User& user)
{
	return mLobby.enterUser(clientSocket, user);
}

bool Server::exitUserInLobby(const int clientSocket)
{
	mLobby.exitUser(clientSocket);
	return true;
}

bool Server::enterUserInChannel(const int clientSocket, const User& user, const std::string& title)
{
	Channel* channel = findChannelOrNull(title);
	return channel->enterUser(clientSocket, user);
}

bool Server::exitUserInChannel(const int clientSocket, const std::string& title)
{
	Channel* channel = findChannelOrNull(title);
	channel->exitUser(clientSocket);
	return true;
}

// TODO: i == STDIN_FILENO 일 때, 서버 콘솔에서 입력 처리, 서버 운영자 명령어 처리
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
		
		for (int i = 0; i <= maxFd; ++i)
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
			
			}
			else
			{
				handleClientMessage(i);
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
	
	
	User user;
	mLoggedInSpace.enterUser(clientSocket, user);
}

/**
 *  recv max 512 byte
*/
bool Server::attemptReceiveValidData(const int clientSocket, char *buffer, bool (Server::*isInvalid)(const char *) \
const, const char *message, const int maxCount)
{
	int i = 0;
	for (i = 0; i < maxCount; ++i)
	{
		const int readLength = recv(clientSocket, buffer, MAX_BUFFER, 0);
		buffer[readLength - 1] = '\0';

		if (readLength == MAX_BUFFER)
		{
			clearStream(clientSocket);
		}

		if (readLength < 0)
		{
			std::cerr << "데이터 수신 실패" << std::endl;
			assert(false);
			return false;
		}
		if ((this->*isInvalid)(buffer) == false)
		{
			break;
		}
		sendToClient(clientSocket, message);
	}
	if (i == maxCount)
	{
		return false;
	}
	return true;
}

void Server::clearStream(const int socket)
{
	char buffer[MAX_BUFFER] = { 0, };
	while (recv(socket, buffer, sizeof(buffer), 0) > MAX_BUFFER - 1)
	{
		continue;
	}
}

// TODO: 명령어 실행 구현
void Server::handleClientMessage(const int clientSocket)
{
	// 안녕
	char buffer[MAX_BUFFER] = { 0, };
	
	const int readLength = recv(clientSocket, buffer, MAX_BUFFER, 0);
	clearStream(clientSocket);
	if (readLength > 500)
	{
		// max message
		return;
	}
	else if (readLength == 0)
	{
		// User에 버퍼 담아 두기
		return;
	}
	
	const Space* space = findSpace(clientSocket);

	IOutgoingMessageProvider* outgoingMessageProvider = space->getOutgoingMessageProvider(buffer);

	std::vector<std::pair<int, std::string> > socketAndMessages = outgoingMessageProvider->getSocketAndMessages(*this, clientSocket, buffer);
	for (size_t i = 0; i < socketAndMessages.size(); ++i)
	{
		std::pair<int, std::string> socketAndMessage = socketAndMessages[i];
		sendToClient(socketAndMessage.first, socketAndMessage.second.c_str());
	}

	IExecutable* executor = space->getExecutor(buffer);
	if (executor != NULL)
	{
		executor->execute(*this, clientSocket, buffer);
	}

	delete outgoingMessageProvider;
	delete executor;
}

void Server::stop()
{
	mbRunning = false;
}

bool Server::isDuplicatedUsername(const char* buffer) const
{
	for (size_t i = 0; i < mChannels.size(); ++i)
	{
		std::vector<std::string> usernames = mChannels[i]->getUsernames();
		for (size_t i = 0; i < usernames.size(); i++)
		{
			if (usernames[i] == buffer)
			{
				return true;
			}
		}
	}
	std::vector<std::string> usernames = mLobby.getUsernames();
	for (size_t i = 0; i < usernames.size(); i++)
	{
		if (usernames[i] == buffer)
		{
			return true;
		}
	}
	return false;
}

bool Server::isDuplicatedNickname(const char* buffer) const
{
	for (size_t i = 0; i < mChannels.size(); ++i)
	{
		std::vector<std::string> nicknames = mChannels[i]->getNicknames();
		for (size_t i = 0; i < nicknames.size(); i++)
		{
			if (nicknames[i] == buffer)
			{
				return true;
			}
		}
	}
	std::vector<std::string> nicknames = mLobby.getNicknames();
	for (size_t i = 0; i < nicknames.size(); i++)
	{
		if (nicknames[i] == buffer)
		{
			return true;
		}
	}
	return false;
}

// TODO: 에러처리 구현
bool Server::sendToClient(const int clientSocket, const char* message)
{
    send(clientSocket, message, std::strlen(message), 0);
	// 에러 처리
	return (true);
}

bool Server::isInvalidPortNumber(const char* port) const
{
    size_t length = std::strlen(port);
    if (!(length == 4 || length == 5))
        return true;
    int value = atoi (port);
    if (!(value >= 1024 && value <= 65535))
        return true;
    return false;
}

bool Server::isInvalidPassword(const char* password) const
{
	bool bSucceeded;
	if (isInvalidPasswordFormatted(password))
	{
		return true;
	}

	bSucceeded = mPassword != Util::generateHash65599(password);
	return bSucceeded;
}

// 8 ~ 16  min Uppercase, lowercase, digit
bool Server::isInvalidPasswordFormatted(const char* password) const
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

bool Server::isInvalidNameFormatted(const char* password) const
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

void Server::QuitServer(const int clientSocket)
{
	Channel* channel = findChannelOrNull(clientSocket);
	if (channel != NULL)
	{
		channel->exitUser(clientSocket);
		if (channel->getUserCount() == 0)
		{
			for (std::vector<Channel *>::iterator it = mChannels.begin(); it != mChannels.end(); ++it)
			{
				if ((*it)->getTopic() == channel->getTopic())
				{
					mChannels.erase(it);
					break;
				}
			}
			delete channel;
		}
	}
	else
	{
		mLobby.exitUser(clientSocket);
	}
	close(clientSocket);
}