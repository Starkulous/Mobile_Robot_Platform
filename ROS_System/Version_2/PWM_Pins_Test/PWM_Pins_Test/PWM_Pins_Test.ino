#define PWM_PIN3 3
#define PWM_PIN5 5
#define PWM_PIN6 6
#define PWM_PIN9 9
#define PWM_PIN10 10
#define PWM_PIN11 11

void setup() {
  pinMode(PWM_PIN3, OUTPUT);
  pinMode(PWM_PIN5, OUTPUT);
  pinMode(PWM_PIN6, OUTPUT);
  pinMode(PWM_PIN9, OUTPUT);
  pinMode(PWM_PIN10, OUTPUT);
  pinMode(PWM_PIN11, OUTPUT);

}

void loop() {
 analogWrite(PWM_PIN3, 100);
 analogWrite(PWM_PIN9, 255);
 analogWrite(PWM_PIN10, 255);
 analogWrite(PWM_PIN11, 255);

 analogWrite(PWM_PIN5, 150);
 analogWrite(PWM_PIN6, 150);

 delay(10);

 analogWrite(PWM_PIN3, 0);
 analogWrite(PWM_PIN9, 0);
 analogWrite(PWM_PIN10, 0);
 analogWrite(PWM_PIN11, 0);

 analogWrite(PWM_PIN5, 0);
 analogWrite(PWM_PIN6, 0);
 delay(10);
}
