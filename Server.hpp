#pragma once

#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <functional>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <vector>
#include <algorithm>
#include "Util.hpp"

class Server
{    
public:
    Server(const char *port, const char *password);
    ~Server();
        
    void run(); // 메인 루프 실행
    void stop(); // 서버 중지

private:
    int mServerSocket;
    int mPort;
    struct sockaddr_in mServerAddr;
    std::vector<int> mclientSockets;
    fd_set mMaster;
    int mFdmax;
    unsigned int mPassword;
        
    // 내부 유틸리티 함수들
    bool isPasswordInvalid(std::string password);
    void error(const std::string &msg);
    void initializeSocket(); //소켓생성
    void setupAddress();  //주소설정
    void bindSocket();  //소켓에 주소 바인딩
    void startListening();  //listen() 함수 호출
    int acceptClient(struct sockaddr_in &clientAddr, socklen_t &clientLen); //요청 수락, accept 반환
    void removeClient(int clientSocket); //클라이언트 종료
    void handleClientMessage(int clientSocket); //받은메세지 처리
    void handleServerInput(); // 서버에서 입력된 메세지 처리
    void sendToClient(int clientSocket, const std::string &message);
    void broadcastMessage(const std::string &message, int excludeSocket = -1);
    
};