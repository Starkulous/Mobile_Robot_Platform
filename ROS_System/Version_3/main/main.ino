#include <EthernetENC.h>
#include <EthernetUdp.h>

#define enableLeft 4
#define pwmLeft 6
#define enableRight 3
#define pwmRight 5

#define PACKET_SIZE 10

int PWMValue;

//// Right
 byte mac[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x03};
 IPAddress ip(192, 168, 137, 3);
 unsigned int localPort = 8888;

// left
// byte mac[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x04};
// IPAddress ip(192, 168, 137, 4);
// unsigned int localPort = 8888;

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

    PWMValue = 100;

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
        if(strcmp(packetBuffer, "stop") == 0) 
        {
            // stop
            Serial.println("Stopping!");
          
            digitalWrite(enableLeft, LOW);
            analogWrite(pwmLeft, 0);
            digitalWrite(enableRight, LOW);
            analogWrite(pwmRight, 0);
        }
        if (strcmp(packetBuffer, "forward") == 0)
        {
            // forward
            Serial.println("Driving!");

            digitalWrite(enableLeft, HIGH);
            analogWrite(pwmLeft, PWMValue);
            digitalWrite(enableRight, HIGH);
            analogWrite(pwmRight, 0);
        } 
        
        if(strcmp(packetBuffer, "reverse") == 0)
        {
            // reverse 
            Serial.println("Reversing!");

            digitalWrite(enableLeft, HIGH);
            analogWrite(pwmLeft, 0);
            digitalWrite(enableRight, HIGH);
            analogWrite(pwmRight, PWMValue);
        }

        if(strcmp(packetBuffer, "left") == 0)
        {
            //Left
            Serial.println("Turning Left!");

            // Right Motor
            digitalWrite(enableLeft, HIGH);
            analogWrite(pwmLeft, PWMValue);
            digitalWrite(enableRight, HIGH);
            analogWrite(pwmRight, 0);

            // Left Motor

          //  digitalWrite(enableLeft, HIGH);
          //  analogWrite(pwmLeft, 0);
          //  digitalWrite(enableRight, HIGH);
          //  analogWrite(pwmRight, PWMValue);
        }
        if(strcmp(packetBuffer, "right") == 0)
        {
            // right
            Serial.println("Turning Right!");

            //Right Motor
            digitalWrite(enableLeft, HIGH);
            analogWrite(pwmLeft, 0);
            digitalWrite(enableRight, HIGH);
            analogWrite(pwmRight, PWMValue);

            //Left Motor
          //  digitalWrite(enableLeft, HIGH);
          //  analogWrite(pwmLeft, PWMValue);
          //  digitalWrite(enableRight, HIGH);
          //  analogWrite(pwmRight, 0);
        }
        if(strcmp(packetBuffer, "increase") == 0)
        {
            // PWM Increase
            Serial.println("increasing PWM");
            if (PWMValue < 255)
            {
                PWMValue = PWMValue + 5;
            }          
        }
        if(strcmp(packetBuffer, "decrease") == 0)
        {
            // PWM decrease
            Serial.println("decreasing PWM");
            if (PWMValue > 0)
            {
                PWMValue = PWMValue - 5;
            }
        }
    }

    for (size_t i = 0; i < PACKET_SIZE; i++)
    {
        packetBuffer[i] = 0;
    }
}
