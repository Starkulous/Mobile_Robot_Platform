# **Test Code**

The following code was used to get the motors to turn.

```c++
delay(100);
digitalWrite(enableLeft, HIGH);
digitalWrite(enableRight, HIGH);
analogWrite(pwmLeft, 0);
analogWrite(pwmRight, 255);

delay(5000);

digitalWrite(enableLeft, LOW);
digitalWrite(enableRight, LOW);
analogWrite(pwmLeft, 0);
analogWrite(pwmRight, 0);

delay(100);

digitalWrite(enableLeft, HIGH);
digitalWrite(enableRight, HIGH);
analogWrite(pwmLeft, 255);
analogWrite(pwmRight, 0);

delay(5000);

digitalWrite(enableLeft, LOW);
digitalWrite(enableRight, LOW);
analogWrite(pwmLeft, 0);
analogWrite(pwmRight, 0);
```

One thing I figured out was that both pins needed to be enabled in order for the motor to turn.
