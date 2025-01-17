#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit functions */
#include <sys/socket.h> /* socket, connect */ 
#include <unistd.h> /* read, wirte, close */
#include <string.h> /* memcopy, memset */
#include <netinet/in.h> /* sockaddr_in, sockaddr */
#include <netdb.h> /* hostent, gethostbyname */
//#include <fcntl.h>
#include <netinet/tcp.h>
#include <sys/types.h>


#define BUFFER_SIZE 1024


int socket_connect(char *host, in_port_t port){

	struct hostent *hp;
	struct sockaddr_in addr;
	int on = 1, sock;     

	if((hp = gethostbyname(host)) == NULL){
		herror("gethostbyname");
		exit(1);
	}
	bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));

	if(sock == -1){
		perror("setsockopt");
		exit(1);
	}
	
	if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1){
		perror("connect");
		exit(1);

	}
	return sock;

}

int main (int argc, char *argv[]){

	int fd;
	char buffer[BUFFER_SIZE];

	if(argc < 3){
		perror("Usage: ./Sub2MainKiller url port \n");
		exit(1);
	}

	fd = socket_connect(argv[1], atoi(argv[2])); 
	write(fd, "GET /\r\n", strlen("GET /\r\n")); // write(fd, char[]*, len);  
	bzero(buffer, BUFFER_SIZE);
	
	while(read(fd, buffer, BUFFER_SIZE - 1) != 0){
		fprintf(stderr, "%s", buffer);
		bzero(buffer, BUFFER_SIZE);
	}

	shutdown(fd, SHUT_RDWR); 
	close(fd); 
	return 0;
}
