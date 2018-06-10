#include "network.h"
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <memory>
#include <string.h>

#define HTTP "http"

Network::Network()
{

}

Network::~Network()
{

}

int Network::initialize(const char *host, short port)
{
    int rv = 0;
    //m_addr = new struct sockaddr_in();

    rv = get_host_by_name(host, &m_addr);
    if(rv){
        return rv;
    }

    m_addr->sin_family = AF_INET;
    m_addr->sin_port = htons(port);

    m_isInitialized = true;
    return 0;
}

int Network::connect()
{
    if(nullptr == m_addr){
        return -1;
    }
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(0>=m_socket){
        return errno;
    }

    int rv = 0;
    int ka = 1;
    setsockopt(m_socket, SOL_SOCKET, SO_KEEPALIVE,  &ka, sizeof(ka));
    rv = ::connect(m_socket, (struct sockaddr*)m_addr, sizeof(*m_addr));
    if(rv){
        return errno;
    }
    return 0;
}

void Network::close()
{
    m_isInitialized = false;
}

void Network::disconnect()
{
    ::close(m_socket);
}

bool Network::isInitialized() const
{
    return m_isInitialized;
}

int Network::reconnect()
{
    disconnect();
    return connect();
}

int Network::get_host_by_name(const char *host, struct sockaddr_in **addr)
{
    int rv = 0;
    if(!inet_aton(host, &addr[0]->sin_addr)){
        struct addrinfo hints, *res, *ptr;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;

        hints.ai_socktype = SOCK_STREAM;
        rv = getaddrinfo(host, HTTP, &hints, &res);
        if(rv){
            return errno;
        }

        SOCKET s = ::socket(AF_INET, SOCK_STREAM, 0);
        for(ptr = res; ptr != NULL; ptr = ptr->ai_next){
            addr[0] = (struct sockaddr_in*)ptr->ai_addr;
            rv = ::connect(s, (struct sockaddr*)addr[0], sizeof(sockaddr_in));
            if(rv){
                continue;
            }else{
                ::close(s);
                //                addr = (struct sockaddr_in*)ptr->ai_addr;
                //printf(inet_ntoa(addr[0]->sin_addr));
                break;
            }
            return errno;
        }

    }else{
        addr[0]->sin_addr.s_addr = inet_addr(host);
        return 0;
    }
    return 0;
}
