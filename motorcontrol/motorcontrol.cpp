#define PART_TM4C123AH6PM

#include "motorcontrol.h"

#include "pins_energia.h"

#include "inttypes.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"

/**
 * This struct is used to store the params used to initialize the PWM enabled pins
 */
typedef struct
{
    enum F
    {
        PORT_TO_ENABLE = 0,
        PWM_TO_ENABLE = 1,
        PINCONFIGURE_CODE = 2,
        PORTBASE = 3,
        PIN = 4,
        PWM_GENERATOR = 5,
        PWM_GEN_MODE = 6,
        PWM_BASE = 7,
        PWM_OUT = 8,
        PWM_OUTPUT_STATE = 9
    };
    
    unsigned int params[10];
} PWMParams;

// Collection of parameters used to initialize the PWM enabled pins
PWMParams params[16] =
{
    {SYSCTL_PERIPH_GPIOB,SYSCTL_PERIPH_PWM0,GPIO_PB6_M0PWM0,GPIO_PORTB_BASE,GPIO_PIN_6,PWM_GEN_0,PWM_GEN_MODE_DOWN,PWM0_BASE,PWM_OUT_0,PWM_OUT_0_BIT},
    {SYSCTL_PERIPH_GPIOB,SYSCTL_PERIPH_PWM0,GPIO_PB7_M0PWM1,GPIO_PORTB_BASE,GPIO_PIN_7,PWM_GEN_0,PWM_GEN_MODE_DOWN,PWM0_BASE,PWM_OUT_1,PWM_OUT_1_BIT},
    {SYSCTL_PERIPH_GPIOB,SYSCTL_PERIPH_PWM0,GPIO_PB4_M0PWM2,GPIO_PORTB_BASE,GPIO_PIN_4,PWM_GEN_1,PWM_GEN_MODE_DOWN,PWM0_BASE,PWM_OUT_2,PWM_OUT_2_BIT},
    {SYSCTL_PERIPH_GPIOB,SYSCTL_PERIPH_PWM0,GPIO_PB5_M0PWM3,GPIO_PORTB_BASE,GPIO_PIN_5,PWM_GEN_1,PWM_GEN_MODE_DOWN,PWM0_BASE,PWM_OUT_3,PWM_OUT_3_BIT},
    {SYSCTL_PERIPH_GPIOE,SYSCTL_PERIPH_PWM0,GPIO_PE4_M0PWM4,GPIO_PORTE_BASE,GPIO_PIN_4,PWM_GEN_2,PWM_GEN_MODE_DOWN,PWM0_BASE,PWM_OUT_4,PWM_OUT_4_BIT},
    {SYSCTL_PERIPH_GPIOE,SYSCTL_PERIPH_PWM0,GPIO_PE5_M0PWM5,GPIO_PORTE_BASE,GPIO_PIN_5,PWM_GEN_2,PWM_GEN_MODE_DOWN,PWM0_BASE,PWM_OUT_5,PWM_OUT_5_BIT},
    {SYSCTL_PERIPH_GPIOC,SYSCTL_PERIPH_PWM0,GPIO_PC4_M0PWM6,GPIO_PORTC_BASE,GPIO_PIN_4,PWM_GEN_3,PWM_GEN_MODE_DOWN,PWM0_BASE,PWM_OUT_6,PWM_OUT_6_BIT},
    {SYSCTL_PERIPH_GPIOC,SYSCTL_PERIPH_PWM0,GPIO_PC5_M0PWM7,GPIO_PORTC_BASE,GPIO_PIN_5,PWM_GEN_3,PWM_GEN_MODE_DOWN,PWM0_BASE,PWM_OUT_7,PWM_OUT_7_BIT},
    {SYSCTL_PERIPH_GPIOD,SYSCTL_PERIPH_PWM1,GPIO_PD0_M1PWM0,GPIO_PORTD_BASE,GPIO_PIN_0,PWM_GEN_0,PWM_GEN_MODE_DOWN,PWM1_BASE,PWM_OUT_0,PWM_OUT_0_BIT},
    {SYSCTL_PERIPH_GPIOD,SYSCTL_PERIPH_PWM1,GPIO_PD1_M1PWM1,GPIO_PORTD_BASE,GPIO_PIN_1,PWM_GEN_0,PWM_GEN_MODE_DOWN,PWM1_BASE,PWM_OUT_1,PWM_OUT_1_BIT},
    {SYSCTL_PERIPH_GPIOA,SYSCTL_PERIPH_PWM1,GPIO_PA6_M1PWM2,GPIO_PORTA_BASE,GPIO_PIN_6,PWM_GEN_1,PWM_GEN_MODE_DOWN,PWM1_BASE,PWM_OUT_2,PWM_OUT_2_BIT},
    {SYSCTL_PERIPH_GPIOA,SYSCTL_PERIPH_PWM1,GPIO_PA7_M1PWM3,GPIO_PORTA_BASE,GPIO_PIN_7,PWM_GEN_1,PWM_GEN_MODE_DOWN,PWM1_BASE,PWM_OUT_3,PWM_OUT_3_BIT},
    {SYSCTL_PERIPH_GPIOF,SYSCTL_PERIPH_PWM1,GPIO_PF0_M1PWM4,GPIO_PORTF_BASE,GPIO_PIN_0,PWM_GEN_2,PWM_GEN_MODE_DOWN,PWM1_BASE,PWM_OUT_4,PWM_OUT_4_BIT},
    {SYSCTL_PERIPH_GPIOF,SYSCTL_PERIPH_PWM1,GPIO_PF1_M1PWM5,GPIO_PORTF_BASE,GPIO_PIN_1,PWM_GEN_2,PWM_GEN_MODE_DOWN,PWM1_BASE,PWM_OUT_5,PWM_OUT_5_BIT},
    {SYSCTL_PERIPH_GPIOF,SYSCTL_PERIPH_PWM1,GPIO_PF2_M1PWM6,GPIO_PORTF_BASE,GPIO_PIN_2,PWM_GEN_3,PWM_GEN_MODE_DOWN,PWM1_BASE,PWM_OUT_6,PWM_OUT_6_BIT},
    {SYSCTL_PERIPH_GPIOF,SYSCTL_PERIPH_PWM1,GPIO_PF3_M1PWM7,GPIO_PORTF_BASE,GPIO_PIN_3,PWM_GEN_3,PWM_GEN_MODE_DOWN,PWM1_BASE,PWM_OUT_7,PWM_OUT_7_BIT}
};

/**
 * Resolve the PIN code to the corresponding index in the array containing pwm parameters.
 * @param pin The pin to resolve
 */
unsigned char resolvePinToIndex(unsigned char pin)
{
    switch(pin)
    {
      case PB_6:
        return 0;
      case PB_7:
        return 1;
      case PB_4:
        return 2;
      case PB_5:
        return 3;
      case PE_4:
        return 4;
      case PE_5:
        return 5;
      case PC_4:
        return 6;
      case PC_5:
        return 7;
      case PD_0:
        return 8;
      case PD_1:
        return 9;
      case PA_6:
        return 10;
      case PA_7:
        return 11;
      case PF_0:
        return 12;
      case PF_1:
        return 13;
      case PF_2:
        return 14;
      case PF_3:
        return 15;
      default: // and now what?
        return 255;
    }
}

/**
 * This function initializes the PWM pin
 * @param pin For valid values @see resolvePinToIndex
 * @param freq The frequency of the signal
 * @param default_pulse_width_in_us The pulse width the pin will start outputting
 */
void Motorcontrol::attach(unsigned char pin, unsigned int freq, unsigned int default_pulse_width_in_us)
{
    pin_ = resolvePinToIndex(pin);
    freq_ = freq;
    
    unsigned int period_value = (SysCtlClockGet()/64)/freq_;
    pwm_value = (unsigned int)(default_pulse_width_in_us*((double)SysCtlClockGet()/64000000.0));

    if(pin_ != 255)
    {
      SysCtlPeripheralEnable(params[pin_].params[PWMParams::PORT_TO_ENABLE]);  //PORT enable
      SysCtlPeripheralEnable(params[pin_].params[PWMParams::PWM_TO_ENABLE]);  //PWM0 enable
      SysCtlPWMClockSet(SYSCTL_PWMDIV_64);  //sysclk=80MHz, PWM_clock=80MHz/64   1250->1ms
      GPIOPinConfigure(params[pin_].params[PWMParams::PINCONFIGURE_CODE]);  //configure pin as PWM output
      GPIOPinTypePWM(params[pin_].params[PWMParams::PORTBASE], params[pin_].params[PWMParams::PIN]);
      PWMGenConfigure(params[pin_].params[PWMParams::PWM_BASE], params[pin_].params[PWMParams::PWM_GENERATOR], params[pin_].params[PWMParams::PWM_GEN_MODE]);  //configure PWM module
      PWMGenPeriodSet(params[pin_].params[PWMParams::PWM_BASE], params[pin_].params[PWMParams::PWM_GENERATOR],period_value);  //set period time
      PWMPulseWidthSet(params[pin_].params[PWMParams::PWM_BASE], params[pin_].params[PWMParams::PWM_OUT],pwm_value);  //set default value
      PWMOutputState(params[pin_].params[PWMParams::PWM_BASE],params[pin_].params[PWMParams::PWM_OUTPUT_STATE], true);  //PWM output state
      PWMGenEnable(params[pin_].params[PWMParams::PWM_BASE], params[pin_].params[PWMParams::PWM_GENERATOR]);  //enable PWM gen
    }
}

/**
 * Set the pulse width of the signal
 * @value_in_us the new pulse width to generate
 */
void Motorcontrol::write(unsigned long value_in_us)
{
  if(pin_ != 255)
  {
    pwm_value = (unsigned int)(value_in_us*((double)SysCtlClockGet()/64000000.0));
    PWMPulseWidthSet(params[pin_].params[PWMParams::PWM_BASE], params[pin_].params[PWMParams::PWM_OUT],pwm_value);
  }
}

/**
 * Set the duty percent of the signal. This is equivalent to changing the pulse width but expressed in percentage.
 * @ duty_percent the new proportion of the high signal
 */
void Motorcontrol::writePercent(double duty_percent)
{
  // (percent/100) * 1.0/freq_ gives value in s
  // multiply it by 1.000.000 transforms it to microseconds
  // (percent*1000000)/(100*freq_) = (percent*10000)/freq_
   write( duty_percent * (10000.0/freq_) );
}
