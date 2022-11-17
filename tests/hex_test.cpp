#include "../src/src_tcp.h"
#include <gtest/gtest.h>
TEST(src_tcp, hexString2string)
{
	std::string input = "48656C6C6F20576F726C6421";
	std::string output = hexString2string(input);
	EXPECT_EQ(output, "Hello World!");
}
TEST(src_tcp, string2hexString)
{
	char input[] = "Hello World!";
	char *output = (char *)malloc(sizeof(char) * 50);
	string2hexString(input, output);
	std::string output_str = output;
	EXPECT_EQ(output_str, "48656C6C6F20576F726C6421");
}
