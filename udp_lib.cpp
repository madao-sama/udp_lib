#include "udp_lib.hpp"

udp_client_server::udp_cs::udp_cs(int port){
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket creation failed");
        exit;
    }
    memset(&server.Addr_s, 0, sizeof(server.Addr_s));
    server.Addr_s.sin_family = AF_INET;
    server.Addr_s.sin_addr.s_addr = htonl(INADDR_ANY); // Listen on all available interfaces
    server.Addr_s.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&server.Addr_s, sizeof(server.Addr_s)) == -1) {
        perror("bind failed");
        close(sockfd);
        exit;
    }

    std::cout << "UDP server is listening everything on port " << port << std::endl;
}

udp_client_server::udp_cs::udp_cs(const std::string& addr, int port){
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket creation failed");
        exit;
    }
    memset(&server.Addr_s, 0, sizeof(server.Addr_s));
    server.Addr_s.sin_family = AF_INET;
    server.Addr_s.sin_addr.s_addr = inet_addr(addr.c_str()); // Listen on all available interfaces
    server.Addr_s.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&server.Addr_s, sizeof(server.Addr_s)) == -1) {
        perror("bind failed");
        close(sockfd);
        exit;
    }

    std::cout << "UDP server is listening on port " << port << "on ip: " << addr << std::endl;}

udp_client_server::udp_cs::~udp_cs(){
    close(sockfd);
}

std::string udp_client_server::udp_cs::get_server_addr(){
    char ip[36];
    inet_ntop(AF_INET, (in_addr_t*)&server.Addr_s.sin_addr.s_addr,ip,36);
    return ip;    
}

int udp_client_server::udp_cs::get_server_port(){   
    return ntohs(server.Addr_s.sin_port);

}

std::string udp_client_server::udp_cs::get_client_addr(){
    char ip[36];
    inet_ntop(AF_INET, (in_addr_t*)&client.Addr_s.sin_addr.s_addr,ip,36);
    return ip;
}
int udp_client_server::udp_cs::get_client_port(){
    return ntohs(client.Addr_s.sin_port);
}

int udp_client_server::udp_cs::send(const char *msg){
    // std::cout<<ntohs(client.Addr_s.sin_port)<<std::endl;
    if (sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&client.Addr_s, sizeof(client.Addr_s)) == -1) {
            perror("sendto failed");
            close(sockfd);
            return 1;
        }
    return 1;
}
int udp_client_server::udp_cs::send(const char *msg, const char* addr){
    // client.Addr_s.sin_port = server.Addr_s.sin_port;
    client.Addr_s.sin_addr.s_addr = inet_addr(addr);
    if (sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&client.Addr_s, sizeof(client.Addr_s)) == -1) {
        perror("sendto failed");
        close(sockfd);
        return -1;
    }
    return 1;
}
int udp_client_server::udp_cs::send(const char *msg, const char* addr, int port){
    // client.Addr_s.sin_port = htons(port);
    client.Addr_s.sin_addr.s_addr = inet_addr(addr);
    if (sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&client.Addr_s, sizeof(client.Addr_s)) == -1) {
        perror("sendto failed");
        close(sockfd);
        return -1;
    }
    return 1;
}
void udp_client_server::udp_cs::get(char* buf){
    char buffer[DEF_BUFFER_SIZE];
    memset(&client.Addr_s, 0, sizeof(client.Addr_s));
    socklen_t addrLen = sizeof(client.Addr_s);

    int recvLen = recvfrom(sockfd, buffer, DEF_BUFFER_SIZE, 0, (struct sockaddr *)&client.Addr_s, &addrLen);
    if (recvLen == -1) {
        perror("recvfrom failed");
        close(sockfd);
        strcpy(buf, "failed");
    }
    strcpy(buf,buffer);
    buf[recvLen] = '\0';
    client.Addr_s.sin_port = htons(ntohs(server.Addr_s.sin_port));
}

