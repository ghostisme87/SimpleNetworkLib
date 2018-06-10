#ifndef TCPSECURE_H
#define TCPSECURE_H

#include "network.h"

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

class TcpSecure : public Network
{
public:
    TcpSecure();

    virtual ~TcpSecure();

    virtual int initialize(const char *host, short port);

    virtual int connect();

    virtual int write(unsigned long long _offset, const void *buffer, unsigned long long lenght);

    virtual int read(unsigned long long _offset, void *_buffer, unsigned long long lenght);

    virtual void disconnect();

    virtual int reconnect();

    virtual void close();

private:
    SSL *m_ssl;
    SSL_CTX *m_ctx;

};

#endif // TCPSECURE_H
