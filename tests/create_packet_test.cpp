#include "../src/src_tcp.h"
#include <gtest/gtest.h>
TEST(src_tcp, createPacket)
{
	char input[] = "Hello World!";
	SolarTcpPacket *packet = createPacket(12, input, DATA);
	EXPECT_EQ(packet->type, DATA);
	EXPECT_EQ(packet->length, 12);
	std::string packet_str = packet->data;
	EXPECT_EQ(packet_str, input);
}