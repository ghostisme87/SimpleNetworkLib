#ifndef NETWORK_H
#define NETWORK_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>


#ifndef _WINDOWS
typedef int SOCKET;
#endif

class Network
{
public:
    Network();
    virtual ~Network();

    virtual int initialize(
            const char* host
            , short port
            );

    virtual int connect();

    virtual int write(
            unsigned long long _offset
            , const void* buffer
            , unsigned long long lenght
            ) = 0;

    virtual int read(
            unsigned long long _offset
            , void* _buffer
            , unsigned long long lenght
            ) = 0;

    virtual void close();
    virtual void disconnect();
    virtual bool isInitialized() const;

    virtual int reconnect();

protected:
    virtual int get_host_by_name(
            /*in*/const char* host
            , /*out*/ struct sockaddr_in **addr
            );


protected:
    SOCKET m_socket = 0;
    struct sockaddr_in *m_addr = nullptr;
    bool m_isInitialized = false;
};

#endif // NETWORK_H
