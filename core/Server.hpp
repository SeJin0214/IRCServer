/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:49:47 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/04 20:59:17 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <sys/socket.h>
#include <sys/types.h>
#include <map>
#include "Channel.hpp"
#include "Lobby.hpp"
#include "LoggedInSpace.hpp"
#include "Result.hpp"

class Server
{
	
public:
	Server(const char* port, const char* password);
	~Server();
	bool run();
	Result<std::pair<int, User> > findUser(const std::string nickname);
	Channel* findChannelOrNull(const std::string topic) const;
	Channel* findChannelOrNull(const int clientSocket) const;
	bool addChannel(const std::string& topic);
	void QuitServer(const int clientSocket);
private:
	enum { MAX_BUFFER = 512 };
	Lobby mLobby;
	LoggedInSpace mLoggedInSpace;
	std::vector<Channel *> mChannels;
	int mServerSocket;
	bool mbRunning;
	const int mPort;
	const unsigned int mPassword;
	
	// 채널 토픽 세터 만들기
	fd_set getFdSet() const;
	int getMaxFd() const;
	std::vector<const Space*> getSpaces() const;
	void stop();
	const Space* findSpace(const int clientSocket) const;
	void acceptClient();
	void clearStream(const int socket);
	bool sendToClient(const int clientSocket, const char* message);
	void handleClientMessage(const int clientSocket);
	bool isDuplicatedUsername(const char* buffer) const;
	bool isDuplicatedNickname(const char* buffer) const;
	bool isInvalidPortNumber(const char* port) const;
	bool isInvalidPasswordFormatted(const char* password) const;
	bool isInvalidPassword(const char* password) const;
	bool isInvalidNameFormatted(const char* password) const;
	bool attemptReceiveValidData(const int clientSocket, char *buffer, \
		bool (Server::*isInvalid)(const char *) const, const char *message, const int maxCount);

};