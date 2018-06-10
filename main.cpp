#include <iostream>
#include "network.h"
#include "tcpsecure.h"
#include "tcp.h"
#include <string.h>
#include <memory>

using namespace std;

int main(int argc, char *argv[])
{
    std::unique_ptr<Network> net(new TcpSecure());
    if(net->initialize("google.com", 443)){
        std::cout << "Error init" << std::endl;
        return 0;
    }
    int rv = 0;
    if((rv = net->connect())){
        std::cout << "Connection error " << rv << std::endl;
        return 0;
    }


    std::string str = "GET / HTTP/1.1\r\nHost: www.google.com\r\nConnection: close\r\n\r\n";
    rv = net->write(0, str.c_str(), str.length());
    if(0 >= rv){
        std::cout << "Send error" << std::endl;
        return errno;
    }

    char buffer[1024];
    rv = 0;
    while(net->read(0, buffer, 1024)){
        std::cout << buffer;
    }


    std::cout << buffer << std::endl;
    net->disconnect();


    net->close();
    cout << "Hello World!" << endl;
    return 0;
}
