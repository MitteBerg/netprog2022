#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char const* argv[])
{



int sockfd , clen , clientfd;
struct sockaddr_in saddr , caddr;
char* hello = "Hello ";
char buffer[1024] = { 0 };
unsigned short port = 8784;
if (( sockfd = socket(AF_INET , SOCK_STREAM , 0)) <0)
{
    printf("Error creating socket\n");
    return -1;

}

memset(&saddr , 0, sizeof(saddr));
saddr.sin_family = AF_INET;
saddr.sin_addr.s_addr = htonl(INADDR_ANY);
saddr.sin_port = htons(port);

if (bind(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) <0)
{
    printf("Error binding\n");
    return -1;

}

if (listen(sockfd, 5 )<0)
{
    printf("Error listening\n");
    return -1;

}
else 
{
    printf("Listen to port: %d\n", port);
}

clen = sizeof(caddr);
if ((clientfd = accept(sockfd, (struct sockaddr * ) &caddr, &clen))  < 0)
{
    printf("Error accepting connection\n");
    return -1;
}
send(sockfd, hello, strlen(hello), 0);
    printf(" message sent\n");
    clen = read(sockfd, buffer, 1024);
    printf("%s\n", buffer);
 
    
    close(clientfd);
    return 0;
}