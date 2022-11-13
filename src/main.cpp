#include "src_tcp.h"

uint16_t count = 0;

int
main ()
{
    char data[] = "Hello World!";
    for (int i = 0; i < 20; i++)
        {
            SolarTcpPacket *packet = createPacket (sizeof (data), data, DATA);
            SolarTcpPacketHeader *header = createPacketHeader (SERVER);
            SolarTcp *solarTcp = createSolarTcp (header, packet);
            char *rawSolarData = SolarTcpRaw (solarTcp);

            std::cout << "Solar TCP Packet Header" << std::endl;
            std::cout << "Timestamp: " << solarTcp->header->timestamp
                      << std::endl;
            std::cout << "Sequence: " << solarTcp->header->sequence
                      << std::endl;
            std::cout << "Sender: " << solarTcp->header->sender << std::endl;
            std::cout << "Receiver: " << solarTcp->header->receiver
                      << std::endl;
            std::cout << "Solar TCP Packet" << std::endl;
            std::cout << "Type: " << solarTcp->packet->type << std::endl;
            std::cout << "Length: " << solarTcp->packet->length << std::endl;
            std::cout << "Data: " << solarTcp->packet->data << std::endl;
            std::cout << "CRC: " << std::hex << solarTcp->packet->crc
                      << std::dec << std::endl;
            std::cout << "Raw: " << rawSolarData << std::endl;
            std::cout << "Raw Length: " << strlen (rawSolarData) << std::endl;
            std::cout << std::endl;
            free (solarTcp->packet); // free because we used malloc
            delete solarTcp->header; // delete because we used new
        }
    return 0;
}