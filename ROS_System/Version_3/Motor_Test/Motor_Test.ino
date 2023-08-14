#define enableLeft 3
#define pwmLeft 6
#define enableRight 4
#define pwmRight 5

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
  // put your main code here, to run repeatedly:

digitalWrite(enableLeft, HIGH);
analogWrite(pwmLeft, 50);
digitalWrite(enableRight, HIGH);
analogWrite(pwmRight, 0);
delay(1000);
digitalWrite(enableLeft, HIGH);
analogWrite(pwmLeft, 0);
digitalWrite(enableRight, HIGH);
analogWrite(pwmRight, 50);
delay(1000);
}
