#include "../src/src_tcp.h"
#include <gtest/gtest.h>
TEST(src_tcp, SolarTcpPacketHeaderSequence)
{
	SolarTcpPacketHeader::sequence = 0;
	EXPECT_EQ(SolarTcpPacketHeader::sequence, 0);
	SolarTcpPacketHeader::sequence++;
	EXPECT_EQ(SolarTcpPacketHeader::sequence, 1);
}