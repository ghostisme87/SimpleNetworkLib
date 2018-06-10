#include "tcp.h"

Tcp::Tcp()
{

}

Tcp::~Tcp()
{

}

int Tcp::write(unsigned long long _offset, const void *buffer, unsigned long long lenght)
{
    return send(m_socket, buffer, lenght, 0);;
}

int Tcp::read(unsigned long long _offset, void *_buffer, unsigned long long lenght)
{
    return recv(m_socket, _buffer, lenght, 0);;
}
