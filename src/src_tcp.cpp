#include "src_tcp.h"

uint16_t SolarTcpPacketHeader::sequence;

SolarTcpPacket *createPacket(uint8_t length, char *data, PACKET_TYPE packetType)
{
	auto *packet =
		(SolarTcpPacket *)malloc(sizeof(SolarTcpPacket) + length);
	if (packet == nullptr) {
		perror("malloc");
	}
	packet->type = packetType;
	packet->length = length;
	memcpy(packet->data, data, length);
	return packet;
}

void changeCase(char *str, CASE c)
{
	int i = 0;
	while (str[i] != '\0') {
		if (c == LOWER) {
			str[i] = (char)tolower(str[i]);
		} else {
			str[i] = (char)toupper(str[i]);
		}
		i++;
	}
}

void string2hexString(char *input, char *output)
{
	int loop = 0;
	int i = 0;
	while (input[loop] != '\0') {
		sprintf((char *)(output + i), "%02X", input[loop]);
		loop += 1;
		i += 2;
	}
}

std::string hexString2string(const char *hex_input)
{
#if VERBOSE == 1
	printf("hexString2string: %s\n", hex_input);
#endif
	std::string output;
	int i = 0;
	while (*(hex_input + i) != '\0') {
		char str[3];
		str[0] = *(hex_input + i);
		str[1] = *(hex_input + i + 1);
		str[2] = '\0';
		char c = (char)strtol(str, (char **)(str[2]), 16);
		output.push_back(c);
		i += 2;
	}
	return output;
}

std::string hexString2string(const std::string &hex_input)
{
	std::string ascii_out;
	for (size_t i = 0; i < hex_input.length(); i += 2) {
		std::string part = hex_input.substr(i, 2);
		char ch = (char)stoul(part, nullptr, 16);
		ascii_out += ch;
	}
	return ascii_out;
}

SolarTcpPacketHeader *createPacketHeader(DEVICES devices)
{
	if (devices == SERVER) {
		auto *header = new SolarTcpPacketHeader{};
		header->sender = SERVER;
		header->receiver = CLIENT;
		return header;
	}
	if (devices == CLIENT) {
		auto *header = new SolarTcpPacketHeader{};
		header->sender = CLIENT;
		header->receiver = SERVER;
		return header;
	}
	return nullptr;
}

SolarTcp *createSolarTcp(SolarTcpPacketHeader *header, SolarTcpPacket *packet)
{
	auto *solarTcp = new SolarTcp{ header, packet };
	return solarTcp;
}

char *SolarTcpRaw(SolarTcp *packet)
{
	char *dataHex = (char *)malloc(packet->packet->length * 2);
	string2hexString(packet->packet->data, dataHex);
	int packetLength = packet->packet->length * 2;
	char *buffer = new char[32 + packetLength + 8];
	sprintf(buffer, "%08x", packet->header->timestamp);
	sprintf(buffer + 8, "%04x", packet->header->sequence);
	sprintf(buffer + 12, "%04x", packet->header->sender);
	sprintf(buffer + 16, "%04x", packet->header->receiver);
	sprintf(buffer + 20, "%02x", packet->packet->type);
	sprintf(buffer + 22, "%02x", 0);
	sprintf(buffer + 24, "%04x", packetLength);
	sprintf(buffer + 28, "%04x", 0);
	memcpy(buffer + 32, dataHex, packetLength);
	changeCase(buffer, LOWER);
	uint32_t crc = CRC::Calculate(buffer, 30 + packetLength, CRC::CRC_32());
	packet->packet->crc = crc;
	sprintf(buffer + 30 + packetLength,
		"%08x", // + 30 to skip the null terminator
		packet->packet->crc);
	changeCase(buffer, LOWER);
	free(dataHex);
	return buffer;
}

SolarRcvTcp *RawToSolarTcp(char *raw)
{
	char *lengthOfRaw = (char *)malloc(5);
	memcpy(lengthOfRaw, raw + 24, 4);
	lengthOfRaw[4] = '\0';
	int packetLength = (int)strtol(lengthOfRaw, nullptr, 16);
#if VERBOSE
	printf("PacketLength: %d\n", packetLength);
#endif
	int rawLength = packetLength + 30;
#if VERBOSE
	printf("RawLength: %d\n", rawLength);
#endif
	uint32_t crcCheck = CRC::Calculate(raw, rawLength, CRC::CRC_32());
	char *crcCheckString = (char *)malloc(9);
	sprintf(crcCheckString, "%08x", crcCheck);
	crcCheckString[8] = '\0';
	changeCase(crcCheckString, LOWER);
#if VERBOSE
	printf("CrcCheckString: %s\n", crcCheckString);
#endif
	char *crcString = (char *)malloc(9);
	memcpy(crcString, raw + rawLength, 8);
	crcString[8] = '\0';
	changeCase(crcString, LOWER);
#if VERBOSE
	printf("CrcString: %s\n", crcString);
#endif
	if (strcmp(crcString, crcCheckString) != 0) {
		printf("CRC check failed\n");
		return nullptr;
	} else {
#if VERBOSE
		printf("CRC check passed\n\n");
#endif
		// SOLAR TCP PACKET HEADER
		auto *header = new SolarTcpPacketRcvHeader{};
		char *timestamp = (char *)malloc(9);
		memcpy(timestamp, raw, 8);
		timestamp[8] = '\0';
		header->timestamp = strtol(timestamp, nullptr, 16);

		char *sequence = (char *)malloc(5);
		memcpy(sequence, raw + 8, 4);
		sequence[4] = '\0';
		header->sequence = strtol(sequence, nullptr, 16);

		char *sender = (char *)malloc(5);
		memcpy(sender, raw + 12, 4);
		sender[4] = '\0';
		header->sender = strtol(sender, nullptr, 16);

		char *receiver = (char *)malloc(5);
		memcpy(receiver, raw + 16, 4);
		receiver[4] = '\0';
		header->receiver = strtol(receiver, nullptr, 16);

		// SOLAR TCP PACKET
		auto *packet = new SolarTcpPacket{};
		char *type = (char *)malloc(3);
		memcpy(type, raw + 20, 2);
		type[2] = '\0';
		packet->type = strtol(type, nullptr, 16);

		char *length = (char *)malloc(5);
		memcpy(length, raw + 24, 4);
		length[4] = '\0';
		packet->length = strtol(length, nullptr, 16) / 2;

		char *data = (char *)malloc(packetLength);
		memcpy(data, raw + 32, packetLength);
		data[packetLength - 2] = '\0';
		std::string thing = hexString2string(data);
		memcpy(packet->data, (char *)thing.c_str(), packet->length);

		char *crc = (char *)malloc(9);
		memcpy(crc, raw + rawLength, 8);
		crc[8] = '\0';
		packet->crc = strtol(crc, nullptr, 16);

		auto *solarTcp = new SolarRcvTcp{ header, packet };
		// create new SolarTcp and copy the data into it
		// fix memory leaks
		free(timestamp);
		free(sequence);
		free(sender);
		free(receiver);
		free(length);
		free(data);
		free(crc);
		free(crcString);
		free(crcCheckString);
		free(lengthOfRaw);
		// Bug: free(type) causes data to be corrupted
		return solarTcp;
	}
}
