 				SELECT
----------------------------------------------------------------------------------------------------------------------------------
	fd_set readset;
	FD_ZERO(&readset);
	
	int max=-1;
	
	for(i=0;i<no_of_file_descriptors;i++)
	{
		FD_SET(fd[i], &readset);
		if(fd[i]>max)
		max=fd[i];		
	}
	
	int rv = select(max + 1, &readset, NULL, NULL, NULL);

	if (rv == -1) 
	{
		perror("select");
	}
	
	else if (rv == 0) 
	{
    		printf("Timeout occurred!\n");
	} 
	
	else 
	{
		int i;
		// check for events 
		for(i=0;i<no_of_file_descriptors;i++)
    		if (FD_ISSET(fd[i], &readset)) 
		{

    		}
	}
 	
				pthread
----------------------------------------------------------------------------------------------------------------------------------
 	
 	void do_thread_service(void *arg)
	{
		int *args= (int*)arg ;
 	
	}
	
	pthread_t t_service;
 	if(pthread_create(&t_service,NULL,(void*)&do_thread_service ,(void*)args)!=0)
	perror("\npthread_create ");
 	


                             RSA Server
----------------------------------------------------------------------------------------------------------------------------------
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>

int main()
{    
    mpz_t p , q , n , p_1 , q_1 , phi_n , e , d , bits_512 , random , rem , M , C , gcd;
    mpz_inits(p , q , n , p_1 , q_1 , phi_n , e , d , bits_512 , random , rem , e , d , M , C , gcd , NULL);

    char* buffer;
    buffer = malloc(100000);
    
    mpz_ui_pow_ui(bits_512 , 2 , 512);
    
    gmp_randstate_t state;
    gmp_randinit_default(state);
    
    struct timeval t;
    gettimeofday(&t , NULL);
    int seed = t.tv_usec;
    
    gmp_randseed_ui(state , seed);
    
    mpz_urandomb(random , state , 512);
    mpz_add(p , bits_512 , random);
    mpz_nextprime(p , p);
    
    mpz_urandomb(random , state , 512);
    mpz_add(q , bits_512 , random);
    mpz_nextprime(q , q);
    
    mpz_sub_ui(p_1 , p , 1);
    mpz_sub_ui(q_1 , q , 1);
    
    mpz_mul(n , p , q);
    mpz_mul(phi_n , p_1 , q_1);
    
    mpz_urandomb(random , state , 512);
    mpz_add(e , bits_512 , random);
    mpz_gcd (gcd , e , phi_n);         
    while(mpz_cmp_ui(gcd , 1) != 0)
    {
        mpz_urandomb(random , state , 512);
        mpz_add(e , bits_512 , random);
        mpz_gcd (gcd , e , phi_n);         
    }
    
    mpz_invert(d , e , phi_n);

    int sfd = socket(AF_INET , SOCK_STREAM , 0);
    if(sfd < 0)
    {
        printf("Error in creating socket\n");
        fflush(stdout);   
    }

    struct sockaddr_in addr;
    bzero((char*)&addr , sizeof(addr));

    addr.sin_family = AF_INET ;
    addr.sin_addr.s_addr = INADDR_ANY ;
    addr.sin_port = htons(2000);

    if( bind(sfd , (struct sockaddr *) &addr , sizeof(addr)) < 0 )
    {
        printf("Error in binding\n");
        fflush(stdout);
    }
   
    listen(sfd , 7);
    socklen_t cli_len = sizeof(struct sockaddr_in);
    int nsfd = accept(sfd , (struct sockaddr *) &addr , &cli_len);
    if(nsfd < 0)
    {
        printf("Error in accept\n");
        fflush(stdout);
    }
    
    else
    {
        printf("\nsuccessfully connected\n");
    }

    gmp_printf("\nn is - %Zd\n" , n);   
    mpz_get_str(buffer , 62 , n);
    write(nsfd , buffer , 10000);

    gmp_printf("\ne is - %Zd\n" , e);   
    mpz_get_str(buffer , 62 , e);
    write(nsfd , buffer , 10000);

    read(nsfd , buffer , 10000);
    mpz_set_str(C , buffer , 62);
    gmp_printf("\nC is - %Zd\n" , C);

    mpz_powm(M , C , d , n);
    gmp_printf("\nM is - %Zd \n" , M);
    mpz_get_str(buffer , 62 , M);
    printf("\nThe message is - %s\n" , buffer);
}


                                      RSA Client
--------------------------------------------------------------------------------------------------------------------------------                                     


#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>

int main()
{    
    mpz_t n , e , M , C;
    mpz_inits(n , e , M , C , NULL);
    
    char* buffer;
    buffer = malloc(10000);
    
    int sfd = socket(AF_INET , SOCK_STREAM , 0);
    if(sfd < 0)
    {
        printf("Error in creating socket\n");
        fflush(stdout);   
    }

    struct sockaddr_in addr;
    bzero((char*)&addr , sizeof(addr));

    addr.sin_family = AF_INET ;
    addr.sin_addr.s_addr = INADDR_ANY ;
    addr.sin_port = htons(2000);


    if(connect(sfd , (struct sockaddr *) &addr , sizeof(addr)) < 0)
    {
        printf("Error in connect");
        fflush(stdout);
    }
    
    else
    {
        printf("\nsuccessfully connected\n");
    }

    read(sfd , buffer , 10000);
    mpz_set_str(n , buffer , 62);
    gmp_printf("\nn is - %Zd\n" , n);   

    read(sfd , buffer , 10000);
    mpz_set_str(e , buffer , 62);
    gmp_printf("\ne is - %Zd\n" , e);   


    printf("\nEnter the message - ");
    scanf("%s" , buffer);
    mpz_set_str(M , buffer , 62); 
    gmp_printf("\nM is - %Zd\n" , M);   

    
    mpz_powm(C , M , e , n);
    gmp_printf("\nC is - %Zd \n" , C);
    mpz_get_str(buffer , 62 , C);
    write(sfd , buffer , 10000);
}


									Python_Client_server
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Server
------
import sys
import socket

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the port
server_address = ('localhost', 10000)
print >>sys.stderr, 'starting up on %s port %s' % server_address
sock.bind(server_address)

# Listen for incoming connections
sock.listen(1)

while True:
    # Wait for a connection
    print >>sys.stderr, 'waiting for a connection'
    connection, client_address = sock.accept()

    try:
        print >>sys.stderr, 'connection from', client_address

        # Receive the data in small chunks and retransmit it
        while True:
            data = connection.recv(16)
            print >>sys.stderr, 'received "%s"' % data
            if data:
                print >>sys.stderr, 'sending data back to the client'
                connection.sendall(data)
            else:
                print >>sys.stderr, 'no more data from', client_address
                break
            
    finally:
        # Clean up the connection
        connection.close()

--------------------------------------------------------------------------------------------------------------
Client
-------

import socket
import sys

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
server_address = ('localhost', 10000)
print >>sys.stderr, 'connecting to %s port %s' % server_address
sock.connect(server_address)

try:
    
    # Send data
    message = 'This is the message.  It will be repeated.'
    print >>sys.stderr, 'sending "%s"' % message
    sock.sendall(message)

    # Look for the response
    amount_received = 0
    amount_expected = len(message)
    
    while amount_received < amount_expected:
        data = sock.recv(16)
        amount_received += len(data)
        print >>sys.stderr, 'received "%s"' % data

finally:
    print >>sys.stderr, 'closing socket'
    sock.close()
									
