//Header file for our ip header and udp header structures.
  
// The packet length
#define PCKT_LEN 8192
  
// Can create separate header file (.h) for all headers' structure
// The IP header's structure
struct ipheader {
 unsigned char      iph_ihl:4;// IP Header Length
 unsigned char      iph_ver:4;//Internet Protocol
 unsigned char      iph_tos;//Type of Service
 unsigned short int iph_len;//Length of IP datagram. Must include UDP size.
 unsigned short int iph_ident;//ID sequence number.
 unsigned char      iph_flag;
 unsigned short int iph_offset;//Fragment offset-used for broken datagrams
 unsigned char      iph_ttl;//Time to live-amount of hops before packet is discarded.
 unsigned char      iph_protocol;//Transport layer protocol.UDP(17)
 unsigned short int iph_chksum;//Checksum total.Everytime header changes must be recalculated.
 unsigned int       iph_sourceip;//Source IP must be converted into binary. inet_pton()
 unsigned int       iph_destip;//Destination IP ""
};
  
// UDP header's structure
struct udpheader {
 unsigned short int udph_srcport;
 unsigned short int udph_destport;
 unsigned short int udph_len;
 unsigned short int udph_chksum;
};
