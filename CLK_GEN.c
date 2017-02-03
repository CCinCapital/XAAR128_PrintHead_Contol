/*
 * CLK_GEN.c
 *
 *  Created on: Dec 2, 2016
 *      Author: Can Chen
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"

//	******CLK_GEN_Init()******
//	Configures PD0 as 1MHz 50% DutyCycle Output
//	Input	-	none
//	Output	-	PWM signal
void CLK_GEN_Init(void){
	//	Set the clocking of the device
	ROM_SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
	//	Set the PWM clock configuration
	ROM_SysCtlPWMClockSet(SYSCTL_PWMDIV_4);
	//	Enables a peripheral
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
	//	Wait for the PWM1 module to be ready
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1)){}
	//	Enable Ports
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	//	Configures pins for use by the PWM peripheral
	ROM_GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0);
	//	Configures the alternate function of a GPIO pin
	ROM_GPIOPinConfigure(GPIO_PD0_M1PWM0);

	//	Configure a PWM generator
	ROM_PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
	//	Sets the period of a PWM generator, Measured in PWM clock ticks
	ROM_PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, 10);
	//	Sets the pulse width for the specified PWM output, Defined as the number of PWM clock ticks
	ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, 5);
	//	Enables or disables PWM outputs
	ROM_PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true);
	//	Enables the timer/counter for a PWN generator block
	ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_0);
}
