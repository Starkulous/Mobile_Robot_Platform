#include <SPI.h>
#include <Ethernet.h>

#define enableLeft 4
#define pwmLeft 6
#define enableRight 3
#define pwmRight 5

#define PACKET_SIZE 10

int PWMValue;

// Right
byte mac[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x03};
IPAddress ip(192, 168, 137, 3);
unsigned int localPort = 8888;

// left
// byte mac[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x04};
// IPAddress ip(192, 168, 137, 4);
// unsigned int localPort = 8888;

EthernetServer server(serverPort);

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
  server.begin();
  Serial.begin(115200);
  while (!Serial){}
}

void loop()
{
  EthernetClient client = server.available();

  if (client)
  {
    if(client.available())
    {
      if(client.read() == 'S') 
      {
        Serial.println("Stopping!");
        
        digitalWrite(enableLeft, LOW);
        analogWrite(pwmLeft, 0);
        digitalWrite(enableRight, LOW);
        analogWrite(pwmRight, 0);
      }
      if (client.read() == 'F')
      {
        Serial.println("Driving!");
        //left
        // digitalWrite(enableLeft, HIGH);
        // analogWrite(pwmLeft, 0);
        // digitalWrite(enableRight, HIGH);
        // analogWrite(pwmRight, PWMValue);
        //right
        digitalWrite(enableLeft, HIGH);
        analogWrite(pwmLeft, PWMValue);
        digitalWrite(enableRight, HIGH);
        analogWrite(pwmRight, 0);
      } 
      if(client.read() == 'B')
      { 
        Serial.println("Reversing!");
        //left
        // digitalWrite(enableLeft, HIGH);
        // analogWrite(pwmLeft, PWMValue);
        // digitalWrite(enableRight, HIGH);
        // analogWrite(pwmRight, 0);
        //right
        digitalWrite(enableLeft, HIGH);
        analogWrite(pwmLeft, 0);
        digitalWrite(enableRight, HIGH);
        analogWrite(pwmRight, PWMValue);
      }

      if(client.read() == 'L')
      {
        Serial.println("Turning Left!");

        digitalWrite(enableLeft, HIGH);
        analogWrite(pwmLeft, PWMValue);
        digitalWrite(enableRight, HIGH);
        analogWrite(pwmRight, 0);
      }
      if(client.read() == 'R')
      {
        Serial.println("Turning Right!");

        digitalWrite(enableLeft, HIGH);
        analogWrite(pwmLeft, 0);
        digitalWrite(enableRight, HIGH);
        analogWrite(pwmRight, PWMValue);
      }
      if(client.read() == 'P')
      {
        Serial.println("increasing PWM");
        if (PWMValue < 255)
        {
          PWMValue = PWMValue + 5;
        }          
      }
      if(client.read() == 'N')
      {
        Serial.println("decreasing PWM");
        if (PWMValue > 0)
        {
          PWMValue = PWMValue - 5;
        }
      }
    }
    client.stop();
  }
}
