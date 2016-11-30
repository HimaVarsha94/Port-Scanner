#define _GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <string.h>	
#include <fcntl.h>
#include <sys/time.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <errno.h>
#include <strings.h>

int start, end;
struct hostent *hostaddr;
char datagram[4096] = "Test Message";

void *core1();
void *core2();
void *core3();
void *core4();

int main(int argc, char **argv)
{

	pthread_t p1, p2, p3, p4;
	int ret1, ret2, ret3, ret4;

	start = 1;
	end   = 1024;


	hostaddr = gethostbyname( argv[1] );

	if (argc < 2)
	{
		printf("Usage: ./output <IPaddress>\n");
		printf("--------------------------------------------------\n");
		return (EINVAL);
	}
	int k1 = start;
	int k2 = (end -start)/4;

	ret1 = pthread_create( &p1, NULL, core1, NULL);
	ret2 = pthread_create( &p2, NULL, core2, NULL);
	 
	pthread_join( p1, NULL);
	pthread_join( p2, NULL);
	 
	printf("\nFinished sending packets\n");

	exit(EXIT_SUCCESS);
}

void *core1()
{
	   struct hostent *hostaddr1;   //To be used for IPaddress
	   struct sockaddr_in servaddr1;
	   char buff1[] = "Ritu, Savit, Hima";
	   int rval1, retval1;    
	   int sd1, port1, rawsock1, iplen1;
	   fd_set r1;
	   struct timeval mytimeout1;
	   struct icmp *packet1;
	   struct ip *iphdr1;
	   struct servent *service1;
	   unsigned char recvbuff1[4096];

	   cpu_set_t cpu1;
	   CPU_ZERO(&cpu1);
	   CPU_SET(0,&cpu1);
	   pthread_setaffinity_np(pthread_self(),sizeof(cpu1),&cpu1);

	   sd1 = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP); //created the tcp socket
	   if (sd1 == -1)
	   {
	   	perror("Socket()\n");
	   	return (errno);
	   }  
	   
	   if((rawsock1 = socket(AF_INET,SOCK_RAW,IPPROTO_ICMP)) < 0)
	   {
	   	perror("socket()");
	   	exit(-1);
	   }

	   bcopy(&hostaddr->h_addr,&servaddr1.sin_addr.s_addr,sizeof(servaddr1.sin_addr));
	   servaddr1.sin_family = AF_INET;
	   mytimeout1.tv_sec = 10;
	   mytimeout1.tv_usec = 0;

	   for(port1 = start; port1 <end; port1++)
	   {
	      servaddr1.sin_port = htons(port1); //set the portno
	      
	      int retry = 0;

	      while(retry++ < 6)
	      {
	      	if((sendto(sd1,buff1,sizeof(buff1),0x0,(struct sockaddr *)&servaddr1,sizeof(servaddr1))) < 0)
	      	{
	      		perror("sendto");
	      		exit(-1);
	      	}
	      	FD_ZERO(&r1);
	      	FD_SET(rawsock1,&r1);
	      	retval1 = select((rawsock1+1),&r1,NULL,NULL,&mytimeout1);

	      	if(retval1)
	      	{
		      /* We got an answer lets check if its the one we want. */

	      		if((recvfrom(rawsock1,&recvbuff1,sizeof(recvbuff1),0x0,NULL,NULL)) < 0)
	      		{
	      			perror("Recv");
	      			exit(-1);
	      		}

			 iphdr1 = (struct ip *)recvbuff1;
			 iplen1 = iphdr1->ip_hl << 2;

			 packet1 = (struct icmp *)(recvbuff1 + iplen1);

			 if((packet1->icmp_type == ICMP_UNREACH) && (packet1->icmp_code == ICMP_UNREACH_PORT))
			 	break;

			}
			else
				continue;


		}
		if(retry >= 6)
		{
			if((service1 = getservbyport(htons(port1),"udp")) == NULL)
				fprintf(stdout,"Unknown port %u, open.\n",port1);
			else
				fprintf(stdout,"UDP service %s open.\n",service1->s_name);
			fflush(stdout);
		}


	}
}
void *core2()
{
	   struct hostent *hostaddr2;   //To be used for IPaddress
	   struct sockaddr_in servaddr2;
	   char buff2[] = "Ritu, Savit, Hima";
	   int rval2, retval2;    
	   int sd2, port2, rawsock2, iplen2;
	   fd_set r2;
	   struct timeval mytimeout2;
	   struct icmp *packet2;
	   struct ip *iphdr2;
	   struct servent *service2;
	   unsigned char recvbuff2[4096];

	   cpu_set_t cpu2;
	   CPU_ZERO(&cpu2);
	   CPU_SET(0,&cpu2);
	   pthread_setaffinity_np(pthread_self(),sizeof(cpu2),&cpu2);

	   sd2 = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP); //created the tcp socket
	   if (sd2 == -1)
	   {
	   	perror("Socket()\n");
	   	return (errno);
	   }  
	   
	   if((rawsock2 = socket(AF_INET,SOCK_RAW,IPPROTO_ICMP)) < 0)
	   {
	   	perror("socket()");
	   	exit(-1);
	   }

	   bcopy(&hostaddr->h_addr,&servaddr2.sin_addr.s_addr,sizeof(servaddr2.sin_addr));
	   servaddr2.sin_family = AF_INET;
	   mytimeout2.tv_sec = 10;
	   mytimeout2.tv_usec = 0;

	   for(port2 = start; port2 <end; port2++)
	   {
	      servaddr2.sin_port = htons(port2); //set the portno
	      
	      int retry = 0;

	      while(retry++ < 6)
	      {
	      	if((sendto(sd2,buff2,sizeof(buff2),0x0,(struct sockaddr *)&servaddr2,sizeof(servaddr2))) < 0)
	      	{
	      		perror("sendto");
	      		exit(-1);
	      	}
	      	FD_ZERO(&r2);
	      	FD_SET(rawsock2,&r2);
	      	retval2 = select((rawsock2+1),&r2,NULL,NULL,&mytimeout2);

	      	if(retval2)
	      	{
		      /* We got an answer lets check if its the one we want. */
	      		
	      		if((recvfrom(rawsock2,&recvbuff2,sizeof(recvbuff2),0x0,NULL,NULL)) < 0)
	      		{
	      			perror("Recv");
	      			exit(-1);
	      		}

			 iphdr2 = (struct ip *)recvbuff2;
			 iplen2 = iphdr2->ip_hl << 2;
			 
			 packet2 = (struct icmp *)(recvbuff2 + iplen2);

			 if((packet2->icmp_type == ICMP_UNREACH) && (packet2->icmp_code == ICMP_UNREACH_PORT))
			 	break;
			 
			}
			else
				continue;


		}
		if(retry >= 6)
		{
			if((service2 = getservbyport(htons(port2),"udp")) == NULL)
				fprintf(stdout,"Unknown port %u, open.\n",port2);
			else
				fprintf(stdout,"UDP service %s open.\n",service2->s_name);
			fflush(stdout);
		}
	}
}
