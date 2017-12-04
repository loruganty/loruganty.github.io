#include "csapp.h"
#include<stdio.h>
#include<string.h>  //strlen
#include<sys/socket.h>
#include<arpa/inet.h>   //inet_addr
#include<unistd.h>  //write

void echo(int connfd);
int main(int argc, char **argv)
{
int listenfd, connfd, port, clientlen;
int sock_fd;
struct sockaddr_in clientaddr;
struct hostent *hp;
char *haddrp;
FILE *image1;
if (argc != 2) {
fprintf(stderr, "usage: %s <port>\n", argv[0]);
exit(0);
}
port = atoi(argv[1]);
listenfd = Open_listenfd(port);
while (1) {
clientlen = sizeof(clientaddr);
connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
/* Determine the domain name and IP address of the client */
hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
sizeof(clientaddr.sin_addr.s_addr), AF_INET);
haddrp = inet_ntoa(clientaddr.sin_addr);
printf("server connected to %s (%s)\n", hp->h_name, haddrp);

printf("Reading Picture Size\n");
int size;

read(sock_fd, &size, sizeof(int));

//Read Picture Byte Array
printf("Reading Picture Byte Array\n");
char p_array[size];
fseek(image1, 0, SEEK_END);
size = ftell(image1);
fseek(image1, 0, SEEK_SET);
read(sock_fd, p_array, size);

//Convert it Back into Picture
printf("Converting Byte Array to Picture\n");
image1 = fopen("/home/lalitha/Downloads/EOS/LABS/tiny/Server/greyzilla.jpg", "wb");
fwrite(p_array, 1, sizeof(p_array), image1);

echo(connfd);
Close(connfd);
}
exit(0);
}
