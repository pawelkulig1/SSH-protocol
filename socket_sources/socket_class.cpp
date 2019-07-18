#include "socket_class.h"
#include <arpa/inet.h>

SocketClass::SocketClass()
{
    sock = socket(PF_INET, SOCK_STREAM, 0);
    sockaddr_in sa;
    sa.sin_family = PF_INET;
    sa.sin_port = htons(5005);
    in_addr i_a;
    i_a.s_addr = htonl(0x0000);
    sa.sin_addr = i_a; 

    conn = connect(sock, (sockaddr *) &sa, sizeof(sa));


}
