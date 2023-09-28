#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>

//Right
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x03}; 
IPAddress ip(192, 168, 137, 3); 
unsigned int serverPort = 8888;

//Left
// byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x04}; 
// IPAddress ip(192, 168, 137, 4); 
// unsigned int serverPort = 8888; 

EthernetServer server(serverPort); // Create a server object

#define enableLeft 4
#define pwmLeft 6
#define enableRight 3
#define pwmRight 5

int PWMValue;

void setup() {
  Ethernet.begin(mac, ip);
  server.begin();

  pinMode(enableLeft, OUTPUT);
  pinMode(enableRight, OUTPUT);
  pinMode(pwmLeft, OUTPUT);
  pinMode(pwmRight, OUTPUT);

  digitalWrite(enableLeft, LOW);
  digitalWrite(enableRight, LOW);
  analogWrite(pwmLeft, 0);
  analogWrite(pwmRight, 0);

  PWMValue = 100;

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
        if(c == 'S') 
        {
          Serial.println("Stopping!");
          
          digitalWrite(enableLeft, LOW);
          analogWrite(pwmLeft, 0);
          digitalWrite(enableRight, LOW);
          analogWrite(pwmRight, 0);
        }
        if (c == 'F')
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
        if(c == 'B')
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

        if(c == 'L')
        {
          Serial.println("Turning Left!");

          digitalWrite(enableLeft, HIGH);
          analogWrite(pwmLeft, PWMValue);
          digitalWrite(enableRight, HIGH);
          analogWrite(pwmRight, 0);
        }
        if(c == 'R')
        {
          Serial.println("Turning Right!");

          digitalWrite(enableLeft, HIGH);
          analogWrite(pwmLeft, 0);
          digitalWrite(enableRight, HIGH);
          analogWrite(pwmRight, PWMValue);
        }
        if(c == 'P')
        {
          Serial.println("increasing PWM");
          if (PWMValue < 255)
          {
            PWMValue = PWMValue + 5;
          }          
        }
        if(c == 'N')
        {
          Serial.println("decreasing PWM");
          if (PWMValue > 0)
          {
            PWMValue = PWMValue - 5;
          }
        }
      }
    }

    client.stop(); // Close the connection
    Serial.println("\nClient disconnected");
  }
}
