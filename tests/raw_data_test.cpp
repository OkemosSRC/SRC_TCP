#include "../src/src_tcp.h"
#include <gtest/gtest.h>
TEST(src_tcp, SolarTcpRaw)
{
	char data[] = "Hello World!";
	SolarTcpPacket *packet = createPacket(sizeof(data), data, DATA);
	SolarTcpPacketHeader *header = createPacketHeader(SERVER);
	SolarTcp *solarTcp = createSolarTcp(header, packet);
	char *rawSolarData = SolarTcpRaw(solarTcp);
	SolarRcvTcp *parsedData = RawToSolarTcp(rawSolarData);
	if (parsedData == nullptr) {
		perror("RawToSolarTcp");
	}
	std::string a = parsedData->packet->data;
	std::string b = solarTcp->packet->data;
	EXPECT_EQ(parsedData->packet->crc, solarTcp->packet->crc);
	EXPECT_EQ(parsedData->packet->length, solarTcp->packet->length);
	EXPECT_EQ(parsedData->packet->type, solarTcp->packet->type);
	EXPECT_EQ(a, b);
	EXPECT_EQ(parsedData->header->sequence, solarTcp->header->sequence);
	EXPECT_EQ(parsedData->header->timestamp, solarTcp->header->timestamp);
}