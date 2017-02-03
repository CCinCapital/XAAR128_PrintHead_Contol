#include "CLK_GEN.h"
#include "Xaar_128.h"
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

int main(void){
	//CLK_GEN_Init();
	XAAR_128_Init();

//	Xaar128_PowerUp();
	uint8_t i;

//	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0);
//	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);
	for(i = 0; i < 8; i = i + 1){
		XAAR_128_DATA_Put(0xFF);
	}
	SysCtlDelay(100);
//	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5);
//	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0);
	for(i = 0; i < 8; i = i + 1){
		XAAR_128_DATA_Put(0xAA);
	}
	SysCtlDelay(100);
//	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);

	SysCtlDelay(150);
//	XAAR128_Fire();
	SysCtlDelay(10000000);

//	Xaar128_PowerDown();

	while(1){

	}
}
