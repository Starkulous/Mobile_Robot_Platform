#include <EthernetENC.h>
#include <EthernetUdp.h>

#define enableLeft 2
#define pwmLeft 3
#define enableRight 4
#define pwmRight 5

#define PACKET_SIZE 10

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 137, 4);

unsigned int localPort = 8888;

char packetBuffer[PACKET_SIZE];
char ReplyBuffer[] = "OK";

EthernetUDP Udp;

void setup()
{
    pinMode(enableLeft, OUTPUT);
    pinMode(pwmLeft, OUTPUT);
    pinMode(enableRight, OUTPUT);
    pinMode(pwmRight, OUTPUT);

    digitalWrite(enableLeft, LOW);
    analogWrite(pwmLeft, 0);
    digitalWrite(enableRight, LOW);
    analogWrite(pwmRight, 0);

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

        Udp.read(packetBuffer, PACKET_SIZE);
        Serial.println("Contents:");
        Serial.println(packetBuffer);
        
        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        Udp.write(ReplyBuffer);
        Udp.endPacket();
    }

    if (strcmp(packetBuffer, "forward") == 0)
    {
        // forward

        digitalWrite(enableLeft, HIGH);
        analogWrite(pwmLeft, 255);
        digitalWrite(enableRight, LOW);
        analogWrite(pwmRight, 0);

    } 
    else if(strcmp(packetBuffer, "reverse") == 0)
    {
        // reverse

        digitalWrite(enableLeft, LOW);
        analogWrite(pwmLeft, 0);
        digitalWrite(enableRight, HIGH);
        analogWrite(pwmRight, 255);
    }
    else {
        // stop
                
        digitalWrite(enableLeft, LOW);
        analogWrite(pwmLeft, 0);
        digitalWrite(enableRight, LOW);
        analogWrite(pwmRight, 0);

    }

    for (size_t i = 0; i < PACKET_SIZE; i++)
    {
        packetBuffer[i] = 0;
    }

    delay(10);
}
