#include "./libnet_test.h"
int main(int argc, char *argv[])
{
int c, i, j, build_ip;
char *cp;
libnet_t *l;
libnet_ptag_t ip, ipo;
libnet_ptag_t udp;
char *payload;
u_short payload_s;
struct libnet_stats ls;
u_long src_ip, dst_ip;
u_short src_prt, dst_prt;
u_char opt[20];
char errbuf[LIBNET_ERRBUF_SIZE];
printf("libnet 1.1 packet shaping: UDP + IP options[raw]\n");
l = libnet_init(LIBNET_RAW4, NULL, errbuf); 
if (l == NULL)
{
fprintf(stderr, "libnet_init() failed: %s\n", errbuf);
exit(EXIT_FAILURE);
}
src_ip = 0;
dst_ip = 0;
src_prt = 0;
dst_prt = 0;
payload = NULL;
payload_s = 0;
ip = ipo = udp = 0;
while ((c = getopt(argc, argv, "d:s:p:")) != EOF)
{
switch (c)
{
// `ip.ip.ip.ip.port`
case 'd':
if (!(cp = strrchr(optarg, '.')))
{
usage(argv[0]);
}
*cp++ = 0;
dst_prt = (u_short)atoi(cp);
if ((dst_ip = libnet_name2addr4(l, optarg, LIBNET_RESOLVE)) == -1)
{
fprintf(stderr, "Bad destination IP address: %s\n", optarg); exit(EXIT_FAILURE);
}
break;
case 's':
if (!(cp = strrchr(optarg, '.')))
{
usage(argv[0]);
}
*cp++ = 0;
src_prt = (u_short)atoi(cp);
if ((src_ip = libnet_name2addr4(l, optarg, LIBNET_RESOLVE)) == -1)
{
fprintf(stderr, "Bad source IP address: %s\n", optarg);
exit(EXIT_FAILURE);
}
break;
case 'p':
payload = optarg;
payload_s = strlen(payload);
break;
default:
exit(EXIT_FAILURE);
}
}
if (!src_ip || !src_prt || !dst_ip || !dst_prt)
{
usage(argv[0]);
exit(EXIT_FAILURE);
}
for (build_ip = 0, i = 0; i < 10; i++)
{
udp = libnet_build_udp(
src_prt, /* source port */
dst_prt + i, /* destination port */
LIBNET_UDP_H + payload_s, /* packet length */
0, /* checksum */
(uint8_t*)payload, /* payload */
payload_s, /* payload size */
l, /* libnet handle */
udp); /* libnet id */
if (udp == -1)
{
fprintf(stderr, "Can't build UDP header: %s\n", libnet_geterror(l));
goto bad;
}
if (1)
{
build_ip = 0;
/* this is not a legal options string */
for (j = 0; j < 20; j++)
{
opt[j] = libnet_get_prand(LIBNET_PR2);
}
ipo = libnet_build_ipv4_options(
opt,
20,
l,
ipo);
if (ipo == -1)
{
fprintf(stderr, "Can't build IP options: %s\n", libnet_geterror(l));
goto bad;
}
ip = libnet_build_ipv4(
LIBNET_IPV4_H + 20 + payload_s + LIBNET_UDP_H, /* length */
0, /* TOS */
242, /* IP ID */
0, /* IP Frag */
64, /* TTL */
IPPROTO_UDP, /* protocol */
0, /* checksum */
src_ip,
dst_ip,
NULL, /* payload */
0, /* payload size */
l, /* libnet handle */
ip); /* libnet id */
if (ip == -1)
{
fprintf(stderr, "Can't build IP header: %s\n", libnet_geterror(l));
goto bad;
}
}
/*
* Write it to the wire.
*/
fprintf(stderr, "%d byte packet, ready to go\n",
libnet_getpacket_size(l));
c = libnet_write(l);
if (c == -1)
{
fprintf(stderr, "Write error: %s\n", libnet_geterror(l));
goto bad;
}
else
{
fprintf(stderr, "Wrote %d byte UDP packet; check the wire.\n", c);
}
}
libnet_stats(l, &ls);
fprintf(stderr, "Packets sent: %lld\n"
"Packet errors: %lld\n"
"Bytes written: %lld\n",
(long long)ls.packets_sent, (long long)ls.packet_errors,
(long long)ls.bytes_written);
libnet_destroy(l);
return (EXIT_SUCCESS);
bad:
libnet_destroy(l);
return (EXIT_FAILURE);
}
void
usage(char *name)
{
fprintf(stderr,
"usage: %s -s source_ip.source_port -d destination_ip.destination_port"
" [-p payload]\n",
name);
}
