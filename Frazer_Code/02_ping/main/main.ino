#include <EthernetENC.h>
#include <EthernetUdp.h>

#define UDP_TX_PACKET_MAX_SIZE 576

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 137, 3);

unsigned int localPort = 8888;

char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
char ReplyBuffer[] = "OK";

EthernetUDP Udp;

void setup()
{
    Ethernet.begin(mac, ip);

    Serial.begin(115200);
    while (!Serial)
    {
    }
    
    Udp.begin(localPort);
}

void loop()
{
    int packetSize = Udp.parsePacket();
    if (packetSize)
    {
        Serial.print("Received packet of size ");
        Serial.println(packetSize);
        Serial.print("From ");
        IPAddress remote = Udp.remoteIP();
        for (int i = 0; i < 4; i++)
        {
            Serial.print(remote[i], DEC);
            if (i < 3)
            {
                Serial.print(".");
            }
        }
        Serial.print(", port ");
        Serial.println(Udp.remotePort());

        Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
        Serial.println("Contents:");
        Serial.println(packetBuffer);

        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        Udp.write(ReplyBuffer);
        Udp.endPacket();
    }
    delay(10);
}
