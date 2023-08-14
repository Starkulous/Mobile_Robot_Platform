#define enableLeft 4
#define pwmLeft 5
#define enableRight 3
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
analogWrite(pwmLeft, 255);
digitalWrite(enableRight, HIGH);
analogWrite(pwmRight, 0);
delay(1000);
digitalWrite(enableLeft, HIGH);
analogWrite(pwmLeft, 0);
digitalWrite(enableRight, HIGH);
analogWrite(pwmRight, 255);
delay(1000);
}
