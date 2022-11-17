#include "../src/src_tcp.h"
#include <gtest/gtest.h>
TEST(src_tcp, changeCase)
{
	char input[] = "Hello World!";
	changeCase(input, UPPER);
	std::string input_str = input;
	EXPECT_EQ(input_str, "HELLO WORLD!");
	changeCase(input, LOWER);
	input_str = input;
	EXPECT_EQ(input_str, "hello world!");
}
