#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sqlite3.h>
#include <sstream>
#include <algorithm>
#include <boost/algorithm/string/replace.hpp>



#define PORT 9000
#define CLIENT_IP "192.168.0.157"
int local_socket=0; //change to 1 to test locally, 0 to test remotely


char message[] = "{\"param\":1}";
char buf[sizeof(message)];

int main()
{
    printf("Client started\r\n");
    std::clock_t ts,tn;

    int sock,sender;
    struct sockaddr_in addr;

    sender = socket(AF_INET, SOCK_STREAM, 0);
    if(sender < 0)
    {
        perror("sender not inited");
        exit(1);
    }

    ts = std::clock();

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT); // или любой другой порт...
    if(local_socket==1)
        addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); //local
    else
        inet_pton(AF_INET, CLIENT_IP, &addr.sin_addr.s_addr); //remote

    if(connect(sender, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }
    tn=std::clock()-ts;
    printf ("\r\nTo connect to socket: %f seconds",((float)tn)/CLOCKS_PER_SEC);

    ts = std::clock();
    send(sender, message, sizeof(message), 0);
    recv(sender, buf, sizeof(message), 0);
    tn=std::clock()-ts;
    printf ("\r\nResponse in: %f seconds",((float)tn)/CLOCKS_PER_SEC);


    printf("\r\nServer says: %s\r\n",buf);

    close(sender);

    return 0;
}