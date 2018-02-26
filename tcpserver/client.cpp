#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 9000


char message[] = "{\"param\":1}";
char buf[sizeof(message)];

int main()
{
    printf("Client started\r\n");

    int sock,sender;
    struct sockaddr_in addr;

    sender = socket(AF_INET, SOCK_STREAM, 0);
    if(sender < 0)
    {
        perror("sender not inited");
        exit(1);
    }


    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT); // или любой другой порт...
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sender, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }

    send(sender, message, sizeof(message), 0);
    recv(sender, buf, sizeof(message), 0);

    printf("Server says: %s\r\n",buf);

    close(sender);

    return 0;
}