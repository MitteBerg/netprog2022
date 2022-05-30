#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int DNS(char *hostname, char *ip)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;
   
    if ( (he = gethostbyname( hostname ) ) == NULL) 
    {
        // get the host info
        herror("gethostbyname");
        return 1;
    }
 
    addr_list = (struct in_addr **) he->h_addr_list;
 
    for(i = 0; addr_list[i] != NULL; i++) 
    {
        //Return the first one;
        strcpy(ip, inet_ntoa(*addr_list[i]) );
        return 0;
    }
 
    return 1;
}

int main(int argc, char *argv[])
  {
  char*hostname = argv[1];
  char ip[100];
  DNS(hostname,ip);
  printf("Hostname: %s\n", hostname);
  printf("Host IP: %s", ip);
  return 0;
  }