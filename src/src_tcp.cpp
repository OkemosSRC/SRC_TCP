#include "src_tcp.h"

SolarTcpPacket *
createPacket (uint8_t length, char *data, PACKET_TYPE packetType)
{
    auto *packet = (SolarTcpPacket *)malloc (sizeof (SolarTcpPacket) + length);
    if (packet == nullptr)
        {
            perror ("malloc");
        }
    // using malloc instead of new because we need to use free later
    packet->type = packetType;
    packet->length = length;
    memcpy (packet->data, data, length);
    return packet;
}

SolarTcpPacketHeader *
createPacketHeader (DEVICES devices)
{
    if (devices == SERVER)
        {
            auto *header = new SolarTcpPacketHeader{};
            header->sender = SERVER;
            header->receiver = CLIENT;
            return header;
        }
    if (devices == CLIENT)
        {
            auto *header = new SolarTcpPacketHeader{};
            header->sender = CLIENT;
            header->receiver = SERVER;
            return header;
        }
    return nullptr;
}

SolarTcp *
createSolarTcp (SolarTcpPacketHeader *header, SolarTcpPacket *packet)
{
    auto *solarTcp = new SolarTcp{ header, packet };
    return solarTcp;
}

char *
SolarTcpRaw (SolarTcp *packet)
{
    char *buffer = new char[32 + packet->packet->length + 8];
    sprintf (buffer, "%08x", packet->header->timestamp);
    sprintf (buffer + 8, "%04x", packet->header->sequence);
    sprintf (buffer + 12, "%04x", packet->header->sender);
    sprintf (buffer + 16, "%04x", packet->header->receiver);
    sprintf (buffer + 20, "%02x", packet->packet->type);
    // padding
    sprintf (buffer + 22, "%02x", 0);
    sprintf (buffer + 24, "%04x", packet->packet->length);
    // padding
    sprintf (buffer + 28, "%04x", 0);
    // padding
    memcpy (buffer + 32, packet->packet->data, packet->packet->length);

    uint32_t crc
        = CRC::Calculate (buffer, 31 + packet->packet->length, CRC::CRC_32 ());

    packet->packet->crc = crc;
    // padding
    sprintf (buffer + 31 + packet->packet->length,
             "%08x", // + 31 to skip the null terminator
             packet->packet->crc);
    return buffer;
}
