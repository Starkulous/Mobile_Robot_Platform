#define enableLeft 11
#define pwmLeft 10
#define enableRight 5
#define pwmRight 6

void setup() {
    pinMode(enableLeft, OUTPUT);
    pinMode(pwmLeft, OUTPUT);
    pinMode(enableRight, OUTPUT);
    pinMode(pwmRight, OUTPUT);

    digitalWrite(enableLeft, LOW);
    analogWrite(pwmLeft, 0);
    digitalWrite(enableRight, LOW);
    analogWrite(pwmRight, 0);
}

void loop() {

digitalWrite(enableLeft, HIGH);
analogWrite(pwmLeft, 55);
digitalWrite(enableRight, HIGH);
analogWrite(pwmRight, 0);
delay(1000);
digitalWrite(enableLeft, HIGH);
analogWrite(pwmLeft, 0);
digitalWrite(enableRight, HIGH);
analogWrite(pwmRight, 55);
delay(1000);
}
