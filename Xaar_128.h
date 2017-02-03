/*
 * Xaar_128.h
 *
 *  Created on: Dec 3, 2016
 *      Author: Can Chen
 */

#ifndef XAAR_128_H_
#define XAAR_128_H_

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

void XAAR_128_Init(void);
void XAAR_128_DATA_Put(uint8_t data);

#endif /* XAAR_128_H_ */
