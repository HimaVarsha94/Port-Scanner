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

int start, end;
struct hostent *hostaddr;
 
void *core1(); //this core functions run the threads on core1
void *core2(); //this core functions run the threads on core2
void *core3();
void *core4();

int main(int argc, char **argv)
{

   pthread_t p1, p2, p3, p4; 
   int ret1, ret2, ret3, ret4;

   start = 0;//starting port number
   end   = 65535; //ending port number

   hostaddr = gethostbyname( argv[1] ); //function which returns IPv4 or IPv6 addresses of the given name if its not already given


   if (argc < 2 )//if incorrect arguments have been passed
   {
      printf("Usage: ./output <IPaddress> \n");
      printf("--------------------------------------------\n");
      return (EINVAL);
   }
   int k1 = start;
   int k2 = (end -start)/4;

   ret1 = pthread_create( &p1, NULL, core1, NULL);//this function creates a thread which executes core1 function which has no arguments
   ret2 = pthread_create( &p2, NULL, core2, NULL);//this creates a thread which executes core2 function which has no arguments
   ret3 = pthread_create( &p3, NULL, core3, NULL);
   ret4 = pthread_create( &p4, NULL, core4, NULL);

   pthread_join( p1, NULL);//this function waits for the given thread to finish execution before parent completes
   pthread_join( p2, NULL);//this function waits for the given thread to finish execution before parent completes
   pthread_join( p3, NULL); 
   pthread_join( p4, NULL); 

   exit(EXIT_SUCCESS);//exits on success
}

void *core1()
{
   struct hostent *hostaddr1;   //To be used for IPaddress
   struct sockaddr_in servaddr1;
   int rval1;         //socket descriptor for connect  
   int sd1, port1;
   /*******************************************************
   Setting cpu affinity
   ********************************************************/
   
   cpu_set_t cpu1;
   CPU_ZERO(&cpu1);
   CPU_SET(0,&cpu1);
   pthread_setaffinity_np(pthread_self(),sizeof(cpu1),&cpu1);

   for(port1 = start; port1 < (end-start)/4; port1++)//we divide all ports into 4 parts and this 'for' loop executes one fourth of total loops
   {    

      sd1 = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //created the tcp socket,PF_INET is for internet protocol,since its tcp we have stream of packets(SOCK_STREAM)


      if (sd1 == -1)//returns -1 if an error occurs
      {
         printf("Error in creating a socket\n");
      }  
 
      memset( &servaddr1, 0, sizeof(servaddr1));
    
      servaddr1.sin_family = AF_INET;
      servaddr1.sin_port = htons(port1); //converts the unsigned short integer hostshort from host byte order to network byte order.
       
      hostaddr1 = hostaddr; 
       
      memcpy(&servaddr1.sin_addr, hostaddr1->h_addr, hostaddr1->h_length);//copies the address into sin_addr of servaddr structure
         
      rval1 = connect(sd1, (struct sockaddr *) &servaddr1, sizeof(servaddr1));
      if (rval1 == -1)
      {
         //printf("Port %d is closed\n", port1);
         close(sd1);
      }
      else
         printf("Port %d is open\n",port1);
       
      close(sd1); 
   }
}
void *core2()
{
   struct hostent *hostaddr2;   //To be used for IPaddress
   struct sockaddr_in servaddr2;
   int rval2;         //socket descriptor for connect  
   int sd2, port2;

   cpu_set_t cpu2;
   CPU_ZERO(&cpu2);
   CPU_SET(0,&cpu2);
   pthread_setaffinity_np(pthread_self(),sizeof(cpu2),&cpu2);

   for(port2 = (end-start)/4; port2 < (end-start)/2; port2++)
   {  
      sd2 = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); 
      if (sd2 == -1)
      {
         printf("Error in creating a socket\n");
      }  
 
      memset( &servaddr2, 0, sizeof(servaddr2));
    
      servaddr2.sin_family = AF_INET;
      servaddr2.sin_port = htons(port2);
       
      hostaddr2 = hostaddr; //get the ip 1st argument
       
      memcpy(&servaddr2.sin_addr, hostaddr2->h_addr, hostaddr2->h_length);
                
      rval2 = connect(sd2, (struct sockaddr *) &servaddr2, sizeof(servaddr2));
      if (rval2 == -1)
      {
         //printf("Port %d is closed\n", port2);
         close(sd2);
      }
      else
         printf("Port %d is open\n",port2);
       
      close(sd2); 
   }
}
void *core3()
{
   struct hostent *hostaddr3;   //To be used for IPaddress
   struct sockaddr_in servaddr3;
   int rval3;         //socket descriptor for connect  
   int sd3;
   int port3;

   cpu_set_t cpu3;
   CPU_ZERO(&cpu3);
   CPU_SET(0,&cpu3);
   pthread_setaffinity_np(pthread_self(),sizeof(cpu3),&cpu3);

   for(port3 = (end-start)/2; port3 < (3*(end-start))/4; port3++)
   {
   //portno is ascii to int second argument    
      sd3 = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //created the tcp socket
      if (sd3 == -1)
      {
         printf("Error in creating a socket\n");
      }  
 
      memset( &servaddr3, 0, sizeof(servaddr3));
    
      servaddr3.sin_family = AF_INET;
      servaddr3.sin_port = htons(port3); //set the portno
      hostaddr3 = hostaddr; 
       
      memcpy(&servaddr3.sin_addr, hostaddr3->h_addr, hostaddr3->h_length);
       
      rval3 = connect(sd3, (struct sockaddr *) &servaddr3, sizeof(servaddr3));
      if (rval3 == -1)
      {
         //printf("Port %d is closed\n", port3);
         close(sd3);
      }
      else
         printf("Port %d is open\n",port3);
       
      close(sd3); 
   }
}
void *core4()
{
   struct hostent *hostaddr4;   //To be used for IPaddress
   struct sockaddr_in servaddr4;
   int rval4;         //socket descriptor for connect  
   int sd4, port4;

   cpu_set_t cpu4;
   CPU_ZERO(&cpu4);
   CPU_SET(0,&cpu4);
   pthread_setaffinity_np(pthread_self(),sizeof(cpu4),&cpu4);

   for(port4 = (3*(end-start))/4; port4 < end; port4++)
   {    
      sd4 = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //created the tcp socket
      if (sd4 == -1)
      {
         printf("Error in creating a socket\n");
      }  
      memset( &servaddr4, 0, sizeof(servaddr4));
      servaddr4.sin_family = AF_INET;
      servaddr4.sin_port = htons(port4); 
       
      hostaddr4 = hostaddr; //get the ip 1st argument
       
      memcpy(&servaddr4.sin_addr, hostaddr4->h_addr, hostaddr4->h_length);
      rval4 = connect(sd4, (struct sockaddr *) &servaddr4, sizeof(servaddr4));
      if (rval4 == -1)
      {
         close(sd4);
      }
      else
         printf("Port %d is open\n",port4);
       
      close(sd4); 
   }
}
