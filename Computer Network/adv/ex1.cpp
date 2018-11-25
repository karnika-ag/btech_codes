#include <iostream>
#include <string>
#include <crafter.h>

/* Collapse namespaces */
using namespace std;
using namespace Crafter;

int main() {

        /* Create a Raw layer with some data on it... */
        RawLayer hello("Hello ");
        RawLayer world("World!");

        /* Create a packet to hold both layers */
        Packet packet = hello / world;

        /* You can print the packet in your screen in different formats */
        packet.Print();     /* Human-readable */
        packet.HexDump();   /* Machine-readable */
        packet.RawString(); /* A C hex string  */

        /* And last but not least, you can write the packet on the wire :-) */
        packet.Send("wlan0");

        return 0;
}
