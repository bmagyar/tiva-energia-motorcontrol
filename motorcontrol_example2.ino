#include <motorcontrol.h>

Motorcontrol m1;

void setup()
{
  Serial.begin(9600);
  m1.attach(PF_1, 50, 1500);
}

void loop()
{
  for(double i=5; i<=10; i+=0.2)
  {
    m1.writePercent(i);
    Serial.println(m1.pwm_value);
    delay(50);
  }
}
