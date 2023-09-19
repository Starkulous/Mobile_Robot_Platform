#include <Ethernet.h>
#include <EthernetClient.h>

#define UDP_TX_PACKET_MAX_SIZE 576

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 137, 3);
EthernetServer server(8888);

void setup()
{
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin(115200);
  while (!Serial){}
  Serial.println("Server is ready");
}

void loop()
{
  EthernetClient client = server.available(); // Check for client connections

  if (client) 
  {
    Serial.println("Client connected");

    while (client.connected()) 
    {
      if (client.available()) 
      {
        char c = client.read();
        Serial.println("c"); // Print received character (byte)
        client.write("OK");
      }
    }

    Serial.println("Client disconnected");
  }
}
