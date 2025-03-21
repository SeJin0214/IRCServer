#include "Server.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "사용법: " << argv[0] << " <포트>\n";
        return EXIT_FAILURE;
    }
    
    int port = std::atoi(argv[1]);
    Server server(port);
    
    try {
        server.run();
    } catch (const std::exception& e) {
        std::cerr << "서버 실행 중 오류 발생: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return 0;
}