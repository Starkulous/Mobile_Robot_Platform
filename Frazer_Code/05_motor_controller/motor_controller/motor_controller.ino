#include <EthernetENC.h>
#include <EthernetUdp.h>

#define enableLeft 2
#define enableRight 3
#define pwmLeft 4
#define pwmRight 5

int motorState = 0; // + driving, 0 stopping, - reversing

#define PACKET_SIZE 10

// Right
// byte mac[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x03};
// IPAddress ip(192, 168, 137, 3);
// unsigned int localPort = 8888;

// left
byte mac[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x04};
IPAddress ip(192, 168, 137, 4);
unsigned int localPort = 8888;

char packetBuffer[PACKET_SIZE];
char ReplyBuffer[] = "OK";

EthernetUDP Udp;

void setup()
{
    pinMode(enableLeft, OUTPUT);
    pinMode(enableRight, OUTPUT);
    pinMode(pwmLeft, OUTPUT);
    pinMode(pwmRight, OUTPUT);

    digitalWrite(enableLeft, LOW);
    digitalWrite(enableRight, LOW);
    analogWrite(pwmLeft, 0);
    analogWrite(pwmRight, 0);

    motorState = 0;

    Ethernet.begin(mac, ip);

    Serial.begin(115200);
    while (!Serial)
    {
    }
    
    Udp.begin(localPort);

}

void loop()
{

    switch (motorState)
    {
        case +1:
        {
            // left

            digitalWrite(enableLeft, HIGH);
            digitalWrite(enableRight, HIGH);
            analogWrite(pwmLeft, 255);
            analogWrite(pwmRight, 0);
            break;
        }
        case -1:
        {
            // right

            digitalWrite(enableLeft, HIGH);
            digitalWrite(enableRight, HIGH);
            analogWrite(pwmLeft, 0);
            analogWrite(pwmRight, 255);
            break;
        }
        case 0:
        {
            // stopping

            digitalWrite(enableLeft, LOW);
            digitalWrite(enableRight, LOW);
            analogWrite(pwmRight, 0);
            analogWrite(pwmLeft, 0);
            break;
        }
        default:
            break;
    }

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

        if (strcmp(packetBuffer, "forward") == 0)
        {
            // forward

            Serial.println("Driving!");

            motorState = 1; // driving

        } 
        else if(strcmp(packetBuffer, "reverse") == 0)
        {
            // reverse

            Serial.println("Reversing!");

            motorState = -1; // reversing
        }
        else {
            // stop
                    
            Serial.println("Stopping!");

            motorState = 0; // stopping

        }
    }

    for (size_t i = 0; i < PACKET_SIZE; i++)
    {
        packetBuffer[i] = 0;
    }
}
