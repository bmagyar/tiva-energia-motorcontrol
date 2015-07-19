#include <motorcontrol.h>

#define LED RED_LED

Motorcontrol m1;

unsigned int servo_pos = 1500;

void setup()
{
  Serial.begin(9600);
  m1.attach(PB_6, 50, 1500);
  
  pinMode(LED, OUTPUT); 
}

void loop()
{
  m1.write(servo_pos);
  servo_pos = (servo_pos+300) % 3000;
  Serial.println(m1.pwm_value);
  
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second 
}
