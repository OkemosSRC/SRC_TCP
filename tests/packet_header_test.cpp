#include "../src/src_tcp.h"
#include <gtest/gtest.h>

TEST(src_tcp, SolarTcpPacketHeader)
{
	SolarTcpPacketHeader *a = createPacketHeader(SERVER);
	EXPECT_EQ(a->sender, SERVER);
	EXPECT_EQ(a->receiver, CLIENT);
	SolarTcpPacketHeader *b = createPacketHeader(CLIENT);
	EXPECT_EQ(b->sender, CLIENT);
	EXPECT_EQ(b->receiver, SERVER);
}