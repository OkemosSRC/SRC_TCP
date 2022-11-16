#include "src_tcp.h"
#include <chrono>
#include <thread>

int main()
{
	SolarTcpPacketHeader::sequence =
		0; // place this before the header is created
	while (true) {
		char data[] = "Hello World!";
		SolarTcpPacket *packet = createPacket(sizeof(data), data, DATA);
		SolarTcpPacketHeader *header = createPacketHeader(SERVER);
		SolarTcp *solarTcp = createSolarTcp(header, packet);
		char *rawSolarData = SolarTcpRaw(solarTcp);
		std::cout << "Solar TCP Packet Header" << std::endl;
		std::cout << "Timestamp: " << solarTcp->header->timestamp
			  << std::endl;
		std::cout << "Sequence: " << SolarTcpPacketHeader::sequence
			  << std::endl;
		std::cout << "Sender: " << solarTcp->header->sender
			  << std::endl;
		std::cout << "Receiver: " << solarTcp->header->receiver
			  << std::endl;
		std::cout << "Solar TCP Packet" << std::endl;
		std::cout << "Type: " << std::hex << solarTcp->packet->type
			  << std::dec << std::endl;
		std::cout << "Length: " << solarTcp->packet->length
			  << std::endl;
		std::cout << "Data: " << solarTcp->packet->data << std::endl;
		std::cout << "CRC: " << std::hex << solarTcp->packet->crc
			  << std::dec << std::endl;
		std::cout << "Raw: " << rawSolarData << std::endl;
		std::cout << "Raw Length: " << strlen(rawSolarData)
			  << std::endl;
		std::cout << std::endl;

		// Parse the raw data
		SolarRcvTcp *parsedData = RawToSolarTcp(rawSolarData);
		if (parsedData == nullptr) {
			perror("RawToSolarTcp");
		}

		std::cout << "Solar TCP Packet Header" << std::endl;
		std::cout << "Timestamp: " << parsedData->header->timestamp
			  << std::endl;
		std::cout << "Sequence: " << parsedData->header->sequence
			  << std::endl;
		std::cout << "Sender: " << parsedData->header->sender
			  << std::endl;
		std::cout << "Receiver: " << parsedData->header->receiver
			  << std::endl;
		std::cout << "Solar TCP Packet" << std::endl;
		std::cout << "Type: " << std::hex << parsedData->packet->type
			  << std::dec << std::endl;
		std::cout << "Length: " << parsedData->packet->length
			  << std::endl;
		std::cout << "Data: " << parsedData->packet->data << std::endl;
		std::cout << "CRC: " << std::hex << parsedData->packet->crc
			  << std::dec << std::endl;
		std::cout << "Raw: " << rawSolarData << std::endl;
		std::cout << "Raw Length: " << strlen(rawSolarData)
			  << std::endl;
		std::cout << std::endl;
		free(solarTcp->packet); // free because we used malloc
		delete solarTcp;
		delete parsedData->packet;
		delete parsedData->header;
		SolarTcpPacketHeader::sequence++;
		std::this_thread::sleep_for(std::chrono::nanoseconds(10));
		std::this_thread::sleep_until(std::chrono::system_clock::now() +
					      std::chrono::seconds(1));
	}
	return 0;
}