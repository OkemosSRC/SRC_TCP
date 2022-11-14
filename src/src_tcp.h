#ifndef SOLAR_TCP_SRC_TCP_H
#define SOLAR_TCP_SRC_TCP_H

#include "crc/CRC.h"
#include <cstdint>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
/**
 * @brief SolarTcpPacket struct
 */
struct SolarTcpPacket
{
    uint8_t type;
    uint16_t length;
    uint32_t crc;
    char data[];
};

extern uint16_t count;

/**
 * @brief SolarTcpPacketHeader struct
 */
struct SolarTcpPacketHeader
{
    uint32_t timestamp = time (nullptr);
    uint16_t sequence = count++;
    uint16_t sender = 0;
    uint16_t receiver = 0;
};

/**
 * @brief SolarTcpPacket struct
 */
struct SolarTcp
{
    SolarTcpPacketHeader *header;
    SolarTcpPacket *packet;
};

/**
 * @brief Server and Client pseudo addresses
 * @note used to identify the sender and receiver
 */
enum DEVICES
{
    SERVER = 0x1B39,
    CLIENT = 0x25E0
};

/**
 * @brief Packet types
 * @note used to identify packet type
 * @note 0x00 - Information packet
 * @note 0x01 - Data packet
 * @note 0x02 - Acknowledgement packet
 * @note 0x03 - Response packet
 * @note 0x04 - Synchronization packet
 * @note 0x05 - Error packet
 */
enum PACKET_TYPE
{
    INFO = 0x00,
    DATA = 0x01,
    ACK = 0x02,
    RSP = 0x03,
    SYN = 0x04,
    ERR = 0x05
};

/**
 * @brief Create a SolarTcpPacket struct
 * @param length uint8_t, length of data
 * @param data char*, a char array
 * @param packetType One of the following: INFO, DATA, ACK, RSP, SYN, ERR
 * @return SolarTcpPacket*
 */

SolarTcpPacket *createPacket (uint8_t length, char *data,
                              PACKET_TYPE packetType);

/**
 * @brief Create a SolarTcpPacketHeader struct
 * @param devices One of the following: SERVER, CLIENT
 * @return
 */
SolarTcpPacketHeader *createPacketHeader (DEVICES devices);

/**
 * @brief Convert an ASCII string to a hex string
 * @param ascii char*, a char array of ASCII characters
 * @param output char*, a char array to store the output hex string
 */
void string2hexString (char *input, char *output);

/**
 * @brief Create a SolarTcp struct
 * @param header SolarTcpPacketHeader*
 * @param packet SolarTcpPacket*
 * @return SolarTcp*
 */
SolarTcp *createSolarTcp (SolarTcpPacketHeader *header,
                          SolarTcpPacket *packet);

/**
 * @brief Convert a SolarTcp struct to raw data
 * @param packet
 * @return char* Raw data to be sent
 */
char *SolarTcpRaw (SolarTcp *packet);

#endif // SOLAR_TCP_SRC_TCP_H
