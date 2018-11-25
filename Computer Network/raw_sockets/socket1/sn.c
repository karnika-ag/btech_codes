// sn.c 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
void packet_dump(const unsigned char *buf, const unsigned int len) { 
unsigned char c; 
int i,j; 
for(i = 0; i < len; i++) { 
printf("%02x ", buf[i]); 
if((i % 16) == 15 || (i == len-1)) { 
for(j = 0; j < 15 - (i % 16); j++) 
printf(" "); printf("| "); 
for(j = (i - (i % 16)); j <= i; j++) { 
c = buf[j]; 
if((c > 31) && (c < 127)) 
printf("%c", c); 
else printf("."); 
} 
printf("\n"); 
} 
} 
} 
int main() 
{ 
int received_length, sock_fd; 
int i; 
u_char buf[5000]; 
if((sock_fd = socket(PF_INET, SOCK_RAW, IPPROTO_UDP)) == -1) { 
printf("errro: socket"); 
exit(1); 
} 
for(i = 0; i < 40; i++) 
{ 
received_length = recv(sock_fd, buf, 4000, 0); 
printf("%d byte packet\n", received_length); 
packet_dump(buf, received_length); 
} 
} 
//- See more at: http://www.bogotobogo.com/cplusplus/sockets_server_client.php#sthash.Enr23mEN.dpuf
