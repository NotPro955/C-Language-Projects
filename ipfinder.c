#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int ac,char **av){
	struct addrinfo ip;
	struct addrinfo *result;
	struct addrinfo *temp;
	int check;
	char buffer[INET6_ADDRSTRLEN];

	memset(&ip,0,sizeof(ip));
	ip.ai_family = AF_UNSPEC;
	ip.ai_socktype = SOCK_STREAM;

	check = getaddrinfo(av[1],0,&ip,&result);
	if(check !=0){
		fprintf(stderr,"error: %s\n",gai_strerror(check));
		return 1;
	}

	temp = result;

	printf("The IP Address for %s:\n",av[1]);
	while(temp != NULL){
		if(temp->ai_family == AF_INET){
			struct sockaddr_in *IPv4 = (struct sockaddr_in *)temp->ai_addr;
			inet_ntop(temp->ai_family,&(IPv4->sin_addr),buffer,sizeof(buffer));
			printf("IPv4: %s\n",buffer);
		}
		else{
			struct sockaddr_in6 *IPv6 = (struct sockaddr_in6 *)temp->ai_addr;
			inet_ntop(temp->ai_family,&(IPv6->sin6_addr),buffer,sizeof(buffer));
			printf("IPv6: %s\n",buffer);
		}
		temp = temp->ai_next;
	}
	return 0;
}
