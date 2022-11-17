#include "../src/src_tcp.h"
#include <gtest/gtest.h>
TEST(src_tcp, create_solar)
{
	char input[] = "Hello World!";
	SolarTcpPacket *packet = createPacket(12, input, DATA);
	SolarTcpPacketHeader *header = createPacketHeader(SERVER);
	SolarTcp *solarTcp = createSolarTcp(header, packet);

	EXPECT_EQ(packet->type, DATA);
	EXPECT_EQ(packet->length, 12);
	std::string packet_str = packet->data;
	EXPECT_EQ(packet_str, input);

	EXPECT_EQ(header->sender, SERVER);
	EXPECT_EQ(header->receiver, CLIENT);

	EXPECT_EQ(solarTcp->header->sender, SERVER);
	EXPECT_EQ(solarTcp->header->receiver, CLIENT);
	EXPECT_EQ(solarTcp->packet->type, DATA);
	EXPECT_EQ(solarTcp->packet->length, 12);
	std::string solarTcp_str = solarTcp->packet->data;
	EXPECT_EQ(solarTcp_str, input);
}