#ifndef __KEY_H
#define __KEY_H


#include "stdint.h"
#include "gpio.h"
/*
#define KEY3_Pin GPIO_PIN_5
#define KEY3_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_7
#define KEY2_GPIO_Port GPIOC
#define KEY1_Pin GPIO_PIN_5
#define KEY1_GPIO_Port GPIOA
#define KEY0_Pin GPIO_PIN_12
#define KEY0_GPIO_Port GPIOB
*/


extern void keyScan(void);
uint8_t getKeyValue(void);
void flushKeyBuf(void);


#endif