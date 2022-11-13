# SRC TCP/IP Stack

A pseudo TCP/IP stack for the SRC Telemetry System.

## Usage

```c++
#include "src/src_tcp.h"

uint16_t count = 0; // Counter for the number of packets sent and received

int
main ()
{
    char data[] = "Hello World!"; // Data to send
    SolarTcpPacket *packet = createPacket (sizeof (data), data, DATA); // Create a packet with the data length, data, and type
    SolarTcpPacketHeader *header = createPacketHeader (SERVER); // Create a packet header with the type
    SolarTcp *solarTcp = createSolarTcp (header, packet); // Create a SolarTcp object with the header and packet
    char *rawSolarData = SolarTcpRaw (solarTcp); // Get the raw data from the SolarTcp object to send over the network
    std::cout << "Solar TCP Packet Header" << std::endl;
    std::cout << "Timestamp: " << solarTcp->header->timestamp << std::endl;
    std::cout << "Sequence: " << solarTcp->header->sequence << std::endl;
    std::cout << "Sender: " << solarTcp->header->sender << std::endl;
    std::cout << "Receiver: " << solarTcp->header->receiver << std::endl;
              << std::endl;
    std::cout << "Solar TCP Packet" << std::endl;
    std::cout << "Type: " << solarTcp->packet->type << std::endl;
    std::cout << "Length: " << solarTcp->packet->length << std::endl;
    std::cout << "Data: " << solarTcp->packet->data << std::endl;
    std::cout << "CRC: " << std::hex << solarTcp->packet->crc << std::dec
              << std::endl;
    std::cout << "Raw: " << rawSolarData << std::endl;
    std::cout << "Raw Length: " << strlen (rawSolarData) << std::endl;
    std::cout << std::endl;
    free (solarTcp->packet); // packet is allocated using malloc, use free
    delete solarTcp->header; // header is allocated using new, use delete
    return 0;
}
```

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Packet Structure

| Field     | Size (bytes) | Description                   |
|-----------|--------------|-------------------------------|
| Timestamp | 4            | Timestamp of the packet       |
| Sequence  | 2            | Sequence number of the packet |
| Sender    | 1            | Sender of the packet          |
| Receiver  | 1            | Receiver of the packet        |
| Type      | 1            | Type of the packet            |
| Length    | 2            | Length of the data            |
| Data      | Length       | Data to send                  |
| CRC       | 4            | CRC of the packet             |

## License
The CRC library is licensed under the BSD License. The rest of the code is licensed under the MIT License.
A copy of the MIT License can be found [here](LICENSE).
