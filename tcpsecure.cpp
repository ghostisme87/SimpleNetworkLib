#include "tcpsecure.h"

TcpSecure::TcpSecure()
{

}

TcpSecure::~TcpSecure()
{

}


int TcpSecure::initialize(const char *host, short port)
{
    Network::initialize(host, port);
    SSL_load_error_strings();
    SSL_library_init();

    OpenSSL_add_all_algorithms();

    m_ctx = SSL_CTX_new(SSLv23_client_method());

    SSL_CTX_set_options(m_ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_COMPRESSION);

    return 0;
}

int TcpSecure::connect()
{
    Network::connect();
    m_ssl = SSL_new(m_ctx);
    if(!SSL_set_fd(m_ssl, m_socket)){
        return -1;
    }
    if(1 != SSL_connect(m_ssl)){
        return -1;
    }
    return 0;
}



int TcpSecure::write(unsigned long long _offset, const void *buffer, unsigned long long lenght)
{
     int rv = SSL_write(m_ssl, buffer, lenght);
     return rv;
}

int TcpSecure::read(unsigned long long _offset, void *_buffer, unsigned long long lenght)
{
    int rv = SSL_read(m_ssl, _buffer, lenght);
    return rv;
}

void TcpSecure::disconnect()
{
    SSL_shutdown(m_ssl);
    SSL_free(m_ssl);

    Network::disconnect();
}

int TcpSecure::reconnect()
{
    disconnect();
    return connect();
}

void TcpSecure::close()
{
    SSL_CTX_free(m_ctx);
    Network::close();
}


