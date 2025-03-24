#include "Server.hpp"

bool Server::isPasswordInvalid(std::string password)
{
    // 8자리 16자리 대문자, 소문자, 숫자
    if (password.length() < 8  || password.length() > 16)
    {
        return false;
    }
    for (size_t i = 0; i < password.length(); ++i)
    {
        if (!(std::isalnum(password[i]) || std::isupper(password[i])))
        {
            return false;
        }
    }
    return true;
}

/// @brief TODO: sejjeong이 파싱 호출부 변경할 것
/// @param port 
/// @param password 
Server::Server(const char *port, const char *password) : mPort(std::atoi(port))
{
    std::string pw = password;
    if (isPasswordInvalid(pw))
        mPassword = Util::generateHash65599(pw);
    else
        error("비밀번호는 8~16자리, 대소문자, 숫자로만 이루어져야합니다.");


    // 소켓 초기화 및 설정
    initializeSocket();
    setupAddress();
    bindSocket();
    startListening();
    
    // 파일 디스크립터 세트 초기화
    FD_ZERO(&mMaster);
    
    // 서버 소켓을 마스터 세트에 추가
    FD_SET(mServerSocket, &mMaster);
    
    // 표준 입력을 마스터 세트에 추가
    FD_SET(STDIN_FILENO, &mMaster);
    
    // 현재 최대 fd 설정
    mFdmax = mServerSocket;
    
    // 표준 입력을 논블로킹 모드로 설정
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    
    std::cout << "서버가 " << mPort << " 포트에서 실행 중입니다..." << std::endl;
}

Server::~Server()
{
    stop();
}

void Server::error(const std::string& msg)
{
    std::cerr << msg << std::endl;
    exit(EXIT_FAILURE);
}

void Server::initializeSocket()
{
    mServerSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mServerSocket < 0)
        error("소켓 생성 실패");

    int opt = 1;
    if (setsockopt(mServerSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        error("setsocket 실패");
    }
}

void Server::setupAddress()
{
    memset(&mServerAddr, 0, sizeof(mServerAddr));
    mServerAddr.sin_family = AF_INET;
    mServerAddr.sin_addr.s_addr = INADDR_ANY;
    mServerAddr.sin_port = htons(mPort);
}

void Server::bindSocket()
{
    if (bind(mServerSocket, (struct sockaddr*)&mServerAddr, sizeof(mServerAddr)) < 0)
        error("바인딩 실패");
}

void Server::startListening()
{
    if (listen(mServerSocket, 5) < 0)
        error("listen 실패");
}

int Server::acceptClient(struct sockaddr_in &clientAddr, socklen_t &clientLen)
{
    int clientSocket = accept(mServerSocket, (struct sockaddr *)&clientAddr, &clientLen);
    
    if (clientSocket < 0) {
        error("accept 실패");
        return -1;
    }
    
    // 마스터 세트에 새 연결 추가
    FD_SET(clientSocket, &mMaster);
    
    // 최대 파일 디스크립터 갱신
    if (clientSocket > mFdmax)
    {
        mFdmax = clientSocket;
    }
    
    // 클라이언트 소켓 목록에 추가
    mclientSockets.push_back(clientSocket);
    
    // 로그인 성공 여부
    std::string passwordMsg = "password 를 입력해주세요.\r\n";
    sendToClient(clientSocket, passwordMsg);

    char buffer[512] = {0};
    
    // 클라이언트로부터 데이터 수신
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    std::string str(buffer);
    buffer[(str).length() - 1] = 0;
    if (bytesRead <= 0)
    {
        // 연결 종료 또는 오류
        if (bytesRead == 0)
        {
            std::cout << "클라이언트 연결 종료" << std::endl;
        }
        else
        {
            error("recv 실패");
        }
        // 클라이언트 제거
        removeClient(clientSocket);
    } 
    else
    {
        if (isPasswordInvalid(buffer) && mPassword == Util::generateHash65599(buffer))
        {
            // 클라이언트 정보 출력
            char clientIP[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN);
            std::cout << "클라이언트 연결: " << clientIP << ":" << ntohs(clientAddr.sin_port) << std::endl;
            
            // 환영 메시지 전송
            std::string welcomeMsg = "IRC 서버에 오신 것을 환영합니다!\r\n";
            sendToClient(clientSocket, welcomeMsg);
        }
        else
        {
            passwordMsg = "password가 맞지 않습니다.\r\n";
            sendToClient(clientSocket, passwordMsg);
            removeClient(clientSocket);
        }
    }
    return clientSocket;
}

// 클라이언트 제거
void Server::removeClient(int clientSocket)
{
    // 소켓 닫기
    close(clientSocket);
    
    // 마스터 세트에서 제거
    FD_CLR(clientSocket, &mMaster);
    
    // 클라이언트 목록에서 제거
    std::vector<int>::iterator it = std::find(mclientSockets.begin(), mclientSockets.end(), clientSocket);
    if (it != mclientSockets.end())
    {
        mclientSockets.erase(it);
    }
    
}

// 클라이언트 메시지 처리
void Server::handleClientMessage(int clientSocket)
{
    char buffer[1024] = {0};
    
    // 클라이언트로부터 데이터 수신
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    
    if (bytesRead <= 0)
    {
        // 연결 종료 또는 오류
        if (bytesRead == 0) {
            std::cout << "클라이언트 연결 종료" << std::endl;
        }
        else
        {
            error("recv 실패");
        }
        
        // 클라이언트 제거
        std::cout << "클라이언트 연결 종료 (소켓 " << clientSocket << ")" << std::endl;
        removeClient(clientSocket);
    } 
    else
    {
        // 받은 데이터 처리
        std::cout << "수신 (소켓 " << clientSocket << "): " << buffer;
        
        // 다른 모든 클라이언트에게 메시지 전달
        std::string forwardMsg = "클라이언트 " + std::string(buffer);
        broadcastMessage(forwardMsg, clientSocket);  // 발신자 제외하고 브로드캐스트
        
        // 메시지에 대한 응답
        std::string response = "메시지가 다른 클라이언트에게 전달되었습니다.\r\n";
        sendToClient(clientSocket, response);
    }
}

// 서버 입력 처리
void Server::handleServerInput()
{
    std::string input;
    std::getline(std::cin, input);
    
    if (!input.empty())
    {
        // 모든 클라이언트에게 메시지 전송
        std::string serverMsg = "서버: " + input + "\n";
        broadcastMessage(serverMsg);  // 모든 클라이언트에게 브로드캐스트
        
        std::cout << "메시지 전송됨: " << serverMsg;
    }
}

// 서버 실행
void Server::run()
{
    fd_set read_fds;  // select()에서 사용할 임시 파일 디스크립터 세트
    
    // 메인 루프
    while(true)
    {
        read_fds = mMaster; // 마스터 세트 복사
        
        // select() 호출로 이벤트 대기
        if (select(mFdmax + 1, &read_fds, NULL, NULL, NULL) == -1)
        {
            error("select 실패");
        }
        
        // 모든 파일 디스크립터 확인
        for(int i = 0; i <= mFdmax; i++)
        {
            if (FD_ISSET(i, &read_fds))
            { // i에 이벤트 발생
                if (i == mServerSocket)
                {
                    // 새 연결 요청 처리
                    struct sockaddr_in clientAddr;
                    socklen_t clientLen = sizeof(clientAddr);
                    acceptClient(clientAddr, clientLen);
                } 
                else if (i == STDIN_FILENO)
                {
                    // 서버 콘솔에서 입력 처리
                    handleServerInput();
                } 
                else
                {
                    // 클라이언트로부터 데이터 수신
                    handleClientMessage(i);
                    // i int vector users [i] 
                    // users 1024
                    // 0 1024
                    // 0(n) 

                    // map
                    // O(1)
                    // O(log n)
                    // 
                }
            }
        }
    }
}

// 서버 중지
void Server::stop()
{
    // 모든 클라이언트 소켓 닫기
    for (std::vector<int>::const_iterator it = mclientSockets.begin(); it != mclientSockets.end(); ++it)
    {
        close(*it);
    }
    
    // 서버 소켓 닫기
    close(mServerSocket);
    
    mclientSockets.clear();
}

// 클라이언트에게 메시지 전송
void Server::sendToClient(int clientSocket, const std::string &message)
{
    send(clientSocket, message.c_str(), message.length(), 0);
}

// 모든 클라이언트에게 메시지 브로드캐스트
void Server::broadcastMessage(const std::string &message, int excludeSocket)
{
    for (std::vector<int>::const_iterator it = mclientSockets.begin(); it != mclientSockets.end(); ++it)
    {
        if (*it != excludeSocket)
        {  // 제외할 소켓 확인
            sendToClient(*it, message);
        }
    }
}