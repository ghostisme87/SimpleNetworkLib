#ifndef TCP_H
#define TCP_H
#include "network.h"


class Tcp : public Network
{
public:
    Tcp();

    virtual ~Tcp();

    virtual int write(unsigned long long _offset, const void *buffer, unsigned long long lenght);

    virtual int read(unsigned long long _offset, void *_buffer, unsigned long long lenght);
};

#endif // TCP_H
