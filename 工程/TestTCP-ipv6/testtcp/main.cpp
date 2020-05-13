//
//  main.cpp
//  testtcp
//
//  Created by admin on 2020/4/22.
//  Copyright © 2020 admin. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstring>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <map>

//int main() {
//    std::cout << "This is client" << std::endl;
//    // socket
//    int client = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
//    if (client == -1) {
//        std::cout << "Error: socket" << std::endl;
//        return 0;
//    }
//    // connect
//
//    struct sockaddr_in serverAddr;
//    serverAddr.sin_family = AF_INET6;
//    serverAddr.sin_port = htons(9933);
//    serverAddr.sin_addr.s_addr = inet_addr("fec0:3016::ec3b:b98a:e70c:badd");
//    if (connect(client, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
//        std::cout << "Error: connect" << std::endl;
//        return 0;
//    }
//    std::cout << "...connect" << std::endl;
//    char data[255];
//    char buf[255];
//    while (true) {
//        std::cin >> data;
//        send(client, data, strlen(data), 0);
//        if (strcmp(data, "exit") == 0) {
//            std::cout << "...disconnect" << std::endl;
//            break;
//        }
//        memset(buf, 0, sizeof(buf));
//        int len = recv(client, buf, sizeof(buf), 0);
//        buf[len] = '\0';
//        std::cout << buf << std::endl;
//    }
//    close(client);
//    return 0;
//}

static bool isIPV6Net(const std::string domainStr = "ipv6.s21.ls.im30app.com")
{
    bool isIPV6Net = false;

    struct addrinfo *result = nullptr,*curr;

    struct sockaddr_in6 dest;
    bzero(&dest, sizeof(dest));

    dest.sin6_family  = AF_INET6;

    int ret = getaddrinfo(domainStr.c_str(),nullptr,nullptr,&result);
    if (ret == 0)
    {
        for (curr = result; curr != nullptr; curr = curr->ai_next)
        {
            switch (curr->ai_family)
            {
                case AF_INET6:
                {
                    isIPV6Net = true;
                    break;
                }
                case AF_INET:

                    break;

                default:
                    break;
            }
        }
    }

    freeaddrinfo(result);

    return isIPV6Net;
}

static std::string domainToIP(const char* pDomain)
{
    if (isIPV6Net())
    {
        struct addrinfo hint;
        memset(&hint, 0x0, sizeof(hint));
        hint.ai_family = AF_INET6;
        hint.ai_flags = AI_V4MAPPED;

        addrinfo* answer = nullptr;
        getaddrinfo(pDomain, nullptr, &hint, &answer);

        if (answer != nullptr)
        {
            char hostname[1025] = "";

            getnameinfo(answer->ai_addr,answer->ai_addrlen,hostname,1025,nullptr,0,0);

            char ipv6[128] = "";
            memcpy(ipv6,hostname,128);

            std::cout<<"domainToIP addrStr:"<<ipv6<<std::endl;

            return ipv6;
        }

        freeaddrinfo(answer);
    }
    else
    {
        struct hostent* h = gethostbyname(pDomain);
        if( h != NULL )
        {
            unsigned char* p = (unsigned char *)(h->h_addr_list)[0];
            if( p != NULL )
            {
                char ip[16] = {0};
                sprintf(ip, "%u.%u.%u.%u", p[0], p[1], p[2], p[3]);
                return ip;
            }
        }
    }
    return "";
}

void testTCP()
{
    auto m_host = domainToIP("ipv6.s21.ls.im30app.com");  // 将域名转换成ipv6的地址
    int sockfd, len;
    struct sockaddr_in6 dest;
    char buffer[1024];

    int m_hSocket = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    // 创建socket
    if (m_hSocket < 0) {
        std::cout << "Error: connect" << std::endl;
    }

    // 初始化服务器地址肯端口信息
    bzero(&dest, sizeof(dest));
    dest.sin6_family = AF_INET6;
    dest.sin6_port = htons(9933);
    if (inet_pton(AF_INET6, m_host.c_str(), &dest.sin6_addr) < 0) {
        std::cout << "Error: connect" << std::endl;
    }

    int iss = connect(m_hSocket, (struct sockaddr*) &dest, sizeof(dest));

    // 连接服务器
    if (iss != 0) {
        std::cout << "Error: connect" << std::endl;
        return;
    }
    std::cout << "OK: connect" << std::endl;
}

typedef std::map<int, int> format;

int main()
{
    format::value_type a[] = {
        format::value_type(1, 2),
        format::value_type(2, 3)
    };
    
    format _format(a, a+2);
    for (auto iter = _format.begin(); iter != _format.end(); ++iter){
        std::cout<<"key: "<<iter->first<<"  value: " << iter->second<<std::endl;
    }
    
}
