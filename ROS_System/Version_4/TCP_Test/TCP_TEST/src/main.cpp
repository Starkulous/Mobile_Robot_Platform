#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x03 }; // Replace with your Ethernet shield/module's MAC address
IPAddress ip(192, 168, 137, 3); // Set your Arduino's IP address
unsigned int serverPort = 8888; // TCP server port

EthernetServer server(serverPort); // Create a server object

void setup() {
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait for serial port to initialize
  }
  Serial.println("Server is ready");
}

void loop() {
  EthernetClient client = server.available(); // Check for client connections

  if (client) {
    Serial.println("Client connected");

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.print(c); // Print received character (byte)

        // Send the received character back to the client
        client.write(c);
      }
    }

    client.stop(); // Close the connection
    Serial.println("\nClient disconnected");
  }
}
