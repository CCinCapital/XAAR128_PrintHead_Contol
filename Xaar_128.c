/*
 * Xaar_128.c
 *
 *  Created on: Dec 3, 2016
 *      Author: Can Chen
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "driverlib/rom.h"
#include "driverlib/ssi.h"


void XAAR_128_Init(void){
	//	Set the clocking of the device
	ROM_SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
	//	Enables a peripheral
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI2);
	//	Wait for the SSI2 module to be ready
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI2)){}
	//	Enable Ports
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	//	Configures pins for use by the SSI2 peripheral
	ROM_GPIOPinTypeSSI(GPIO_PORTB_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
	//	Enable SSI2 Function
	ROM_GPIOPinConfigure(GPIO_PB4_SSI2CLK);
	ROM_GPIOPinConfigure(GPIO_PB5_SSI2FSS);
	ROM_GPIOPinConfigure(GPIO_PB6_SSI2RX);
	ROM_GPIOPinConfigure(GPIO_PB7_SSI2TX);
	//	Sets the pad configuration for the specified pins
	ROM_GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
	//	Configures the synchronous serial interface
	ROM_SSIConfigSetExpClk(SSI2_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_2, SSI_MODE_MASTER, 1000000, 8);
	// 	Enable the SSI module.
	ROM_SSIEnable(SSI2_BASE);
}


void XAAR_128_DATA_Put(uint8_t data){
	SSIDataPut(SSI2_BASE, data);
}
