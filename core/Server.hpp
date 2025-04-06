/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:49:47 by sejjeong          #+#    #+#             */
/*   Updated: 2025/04/06 15:08:47 by sejjeong         ###   ########.fr       */
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

enum { MAX_BUFFER = 512 };

// 쪼갠다면, 전체 Space와 comunicator가 있을 듯
class Server
{
	
public:
	Server(const char* port, const char* password);
	~Server();
	bool run();

	std::string getServerName() const;
	unsigned int getPassword() const;
	Result<User> findUser(const int clientSocket);
	Result<std::pair<int, User> > findUser(const std::string nickname);
	bool trySetAuthenticatedInLoggedSpace(const int clientSocket);
	bool trySetNicknameInLoggedSpace(const int clientSocket, const std::string& nickname);
	bool trySetUsernameInLoggedSpace(const int clientSocket, const std::string& username);
	void enterServer(const int clientSocket, const User& user);
	bool enterUserInLobby(const int clientSocket, const User& user);
	bool exitUserInLobby(const int clientSocket);
	bool enterUserInChannel(const int clientSocket, const User& user, const std::string& title);
	bool exitUserInChannel(const int clientSocket, const std::string& title);
	bool addChannel(const std::string& title);
	void leaveServer(const int clientSocket);
	bool isDuplicatedNickname(const char* buffer) const;
	void executeOutgoing(const int clientSocket);
	// private으로 옮길 수도 있음
	Channel* findChannelOrNull(const std::string title) const;
	Channel* findChannelOrNull(const int clientSocket) const;
	
private:
	Lobby mLobby;
	LoggedInSpace mLoggedInSpace;
	std::vector<Channel *> mChannels;
	std::string mName;
	int mServerSocket;
	bool mbRunning;
	const int mPort;
	const unsigned int mPassword;
	
	// 채널 토픽 세터 만들기
	fd_set getFdSet() const;
	int getMaxFd() const;
	std::vector<const Space*> getSpaces() const;
	std::vector<Space*> getSpaces();
	const Space* findSpace(const int clientSocket) const;
	void acceptClient();
	bool sendToClient(const int clientSocket, const char* message);
	void handleClientMessage(const int clientSocket);
	void ExecuteCommandByProtocol(const int clientSocket, const char* buffer);
	bool isDuplicatedUsername(const char* buffer) const;
	bool isInvalidPortNumber(const char* port) const;
	bool isInvalidPasswordFormatted(const char* password) const;
	bool isInvalidPassword(const char* password) const;
	bool isInvalidNameFormatted(const char* password) const;

};