/*
 * XAAR128.h
 *
 *  Created on: Dec 2, 2016
 *      Author: Can Chen
 */

#ifndef XAAR128_H_
#define XAAR128_H_

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

void XAAR128_Init(void);
void Xaar128_PowerUp(void);
void XAAR128_DATA_Write(uint8_t data);
void XAAR128_Fire(void);
void Xaar128_PowerDown(void);

#endif /* XAAR128_H_ */
