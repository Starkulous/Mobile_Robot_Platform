#define enableLeft 2
#define pwmLeft 3
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

digitalWrite(enableLeft, LOW);
analogWrite(pwmLeft, 0);
digitalWrite(enableRight, HIGH);
analogWrite(pwmRight, 255);
}
