#include "src_tcp.h"

uint16_t count = 0; // Counter for the number of packets sent

int main()
{
	char data[] = "Hello World!";
	SolarTcpPacket *packet = createPacket(sizeof(data), data, DATA);
	SolarTcpPacketHeader *header = createPacketHeader(SERVER);
	SolarTcp *solarTcp = createSolarTcp(header, packet);
	char *rawSolarData = SolarTcpRaw(solarTcp);

	std::cout << "Solar TCP Packet Header" << std::endl;
	std::cout << "Timestamp: " << solarTcp->header->timestamp << std::endl;
	std::cout << "Sequence: " << solarTcp->header->sequence << std::endl;
	std::cout << "Sender: " << solarTcp->header->sender << std::endl;
	std::cout << "Receiver: " << solarTcp->header->receiver << std::endl;
	std::cout << "Solar TCP Packet" << std::endl;
	std::cout << "Type: " << std::hex << solarTcp->packet->type << std::dec
		  << std::endl;
	std::cout << "Length: " << solarTcp->packet->length << std::endl;
	std::cout << "Data: " << solarTcp->packet->data << std::endl;
	std::cout << "CRC: " << std::hex << solarTcp->packet->crc << std::dec
		  << std::endl;
	std::cout << "Raw: " << rawSolarData << std::endl;
	std::cout << "Raw Length: " << strlen(rawSolarData) << std::endl;
	std::cout << std::endl;

	// Parse the raw data
	SolarRcvTcp *parsedData = RawToSolarTcp(rawSolarData);
	if (parsedData == nullptr) {
		perror("RawToSolarTcp");
	}

	std::cout << "Solar TCP Packet Header" << std::endl;
	std::cout << "Timestamp: " << parsedData->header->timestamp
		  << std::endl;
	std::cout << "Sequence: " << parsedData->header->sequence << std::endl;
	std::cout << "Sender: " << parsedData->header->sender << std::endl;
	std::cout << "Receiver: " << parsedData->header->receiver << std::endl;
	std::cout << "Solar TCP Packet" << std::endl;
	std::cout << "Type: " << std::hex << parsedData->packet->type
		  << std::dec << std::endl;
	std::cout << "Length: " << parsedData->packet->length << std::endl;
	std::cout << "Data: " << parsedData->packet->data << std::endl;
	std::cout << "CRC: " << std::hex << parsedData->packet->crc << std::dec
		  << std::endl;
	std::cout << "Raw: " << rawSolarData << std::endl;
	std::cout << "Raw Length: " << strlen(rawSolarData) << std::endl;
	std::cout << std::endl;
	free(solarTcp->packet); // free because we used malloc
	delete solarTcp->header; // delete because we used new
	delete solarTcp;
	free(parsedData->packet);
	delete parsedData->header;
	delete parsedData;
	return 0;
}