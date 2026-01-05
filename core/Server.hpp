/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:49:47 by sejjeong          #+#    #+#             */
/*   Updated: 2026/01/06 05:06:56 by sejjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <sys/socket.h>
#include <sys/types.h>
#include <unordered_map>
#include <vector>
#include "Channel.hpp"
#include "Lobby.hpp"
#include "LoggedInSpace.hpp"
#include "Result.hpp"

enum { MAX_BUFFER = 512 };

class Server
{

public:
	Server(const char* port, const char* password);
	~Server();
	Server(const Server&) = delete;
	Server& operator=(const Server&) = delete;
	
	bool run();
	Result<User> findUser(const int clientSocket) const;
	Result<std::pair<int, User> > findUser(const std::string& nickname) const;
	const std::string& getServerName() const;
	unsigned int getPassword() const;
	bool trySetAuthenticatedInLoggedSpace(const int clientSocket);
	bool trySetNicknameInLoggedSpace(const int clientSocket, const std::string& nickname);
	bool trySetUsernameInLoggedSpace(const int clientSocket, const std::string& username);

	void loginToServer(const int clientSocket, User* user);

	void leaveServer(const int clientSocket);
	bool enterUserInLobby(const int clientSocket, User* user);
	User* exitUserInLobbyOrNull(const int clientSocket);
	bool enterUserInChannel(const int clientSocket, const std::string& title);
	User* exitUserInChannel(const int clientSocket, const std::string& title);
	
	void exitAllSpaces(const int clientSocket);
	Channel* findChannelOrNull(const std::string& title) const;
	const std::unordered_map<std::string, Channel*>& loadChannels() const;
	bool isDuplicatedNickname(const char* buffer) const;
	
private:
	Lobby mLobby;
	LoggedInSpace mLoggedInSpace;
	std::unordered_map<std::string, Channel*> mChannels;
	std::string mName;
	int mServerSocket;
	bool mbRunning;
	const int mPort;
	const unsigned int mPassword;
	
	fd_set getFdSet() const;
	int getMaxFd() const;
	std::vector<const Space*> getSpaces() const;
	std::vector<Space*> getSpaces();
	User* findUserInAllSpace(const int clientSocket) const;
	Channel* findChannelOrNull(const int clientSocket) const;
	const Space* findSpace(const int clientSocket) const;
	Channel* createChannel(const std::string& title);
	
	void acceptClient();
	bool sendToClient(const int clientSocket, const char* message);
	void handleClientMessage(const int clientSocket);
	void ExecuteCommandByProtocol(const int clientSocket, const char* buffer);
	bool isInvalidPassword(const char* password) const;

};
