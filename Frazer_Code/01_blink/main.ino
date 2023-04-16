#define testLedPin 12
#define ledPin 13

void setup()
{
    pinMode(testLedPin, OUTPUT);
    pinMode(ledPin, OUTPUT);
    digitalWrite(testLedPin, LOW);
    digitalWrite(ledPin, LOW);
}

void loop()
{
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
}