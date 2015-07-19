#pragma once
#ifndef _MOTORCONTROL_H_
#define _MOTORCONTROL_H_

/**
 * Supported pins:
 * PB_6, PB_7, PB_4, PB_5, PE_4, PE_5, PC_4, PC_5,
 * PD_0, PD_1, PA_6, PA_7, PF_0, PF_1, PF_2, PF_3
 * 
 * PB6    NOT recommended! SHORTED to PB7 via 0ohm resistor.
 * PB7    NOT recommended! SHORTED to PB6 via 0ohm resistor.
 * PD0    NOT recommended! SHORTED to PD1 via 0ohm resistor.
 * PD1    NOT recommended! SHORTED to PD0 via 0ohm resistor.
 * PF0    NOT recommended! User button connected to the same pin.
 *
 */

class Motorcontrol
{
  public:
    void attach(unsigned char pin, unsigned int freq, unsigned int starting_pulse_width_in_us = 0);

    void write(unsigned long value_in_us);
	void writePercent(double duty_percent);
    void reset() {  write(default_pulse_width_);  }
	
    unsigned char getPin(){return pin_;}
    unsigned int pwm_value;
    
  private:
    unsigned char pin_;
    unsigned int freq_;
    unsigned int default_pulse_width_;
};


#endif
