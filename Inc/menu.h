#ifndef __MENU_H
#define __MENU_H
#include "ssd1306.h"
#include "key.h"

#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_ENTER 3
#define KEY_ESC 4
#define KEY_MENU 5
#define KEY_ONOFF 6
#define KEY_NONE 0

#define Curve_X 100
#define Curve_Y 50

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

extern DAC_HandleTypeDef hdac1;
extern DMA_HandleTypeDef hdma_dac1_ch1;

extern uint8_t kv;
extern uint8_t menu_index;
extern uint32_t ADC_Value[128];
extern uint32_t curveBuffer[Curve_X];
extern TIM_HandleTypeDef htim6;

void OS_Main(void);
void OS_Menu1(void);
void OS_Menu2(void);
void OS_Menu3(void);
void OS_Menu3_1(void);
void OS_Menu3_2(void);
void OS_Init(void);
void OS_Trans(void);
void OS_CopyRight(void);
void drawCurve(void);
uint16_t mmap(uint32_t max, uint32_t min, double num);
extern void setSineFreq(uint32_t frequency);
extern void sweepFreq(uint32_t min, uint32_t max, uint16_t step, uint16_t interval);

#endif