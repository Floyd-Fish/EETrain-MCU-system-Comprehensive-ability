#include "key.h"

#define KEY_100MS       2
#define KEY_200MS       20
#define KEY_500MS       50
#define KEY_1S          100
#define KEY_2S          200


#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_ENTER 3
#define KEY_ESC 4
#define KEY_MENU 5
#define KEY_ONOFF 6
#define KEY_NONE 0


#define PORT_KENTER   HAL_GPIO_ReadPin(	GPIOC, GPIO_PIN_7)
#define PORT_KUP   HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)
#define PORT_KDOWN   HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)
#define PORT_KESC   HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)


uint32_t gucKeyEnterTimer, gucKeyUpTimer,gucKeyDownTimer, gucKeyEscTimer, gucKeyMenuTimer;  //按键消抖需要的扫描计时器
uint8_t gfEnterPressing, gfEnterNeedAck;        //ENTER按键的按下标志、需要响应的标志
uint8_t gfUpPressing, gfUpNeedAck;    //UP按键的按下标志、需要响应的标志；  
uint8_t gfDownPressing, gfDownNeedAck;    //DOWN按键的按下标志、需要响应的标志；
uint8_t gfEscPressing, gfEscNeedAck;  //ESC按键的按下标志、需要响应的标志；
uint8_t gfMenuPressing, gfMenuNeedAck;      //MENU按键(同时按下UP、DOWN）的按下标志、需要响应的标志；
uint8_t gfONOFFPressing, gfONOFFNeedAck;    //ONOFF按键（按下OK超过3秒）的按下标志、需要响应的标志；


void keyScan()
{
	
//*********************OK key*********************//
  if(PORT_KENTER == 0)
    {
      gucKeyEnterTimer++;
      if(gucKeyEnterTimer > KEY_100MS)
        {
          if(gfEnterPressing == 0)
            gfEnterNeedAck = 1;
					
          gfEnterPressing=1;
        }
      if(gucKeyEnterTimer > KEY_1S)
        {
          gfONOFFPressing = 1;
          if(gfONOFFPressing == 0)
            gfONOFFNeedAck = 1;
        }
    }
  else
    {
      gucKeyEnterTimer = 0;
      gfEnterPressing = 0;
    } 

//*********************Up key*********************//
		if(PORT_KUP == 0)
    {
      gucKeyUpTimer++;
      if(gucKeyUpTimer > KEY_100MS)
      {
          if(gfUpPressing == 0)
            gfUpNeedAck = 1;
					gfUpPressing = 1;
      }
    }
  else
    {
      gucKeyUpTimer = 0;
      gfUpPressing = 0;
    }	
//*********************Down key*********************//
		if(PORT_KDOWN == 0)
    {
      gucKeyDownTimer++;
      if(gucKeyDownTimer > KEY_100MS)
      {
          if(gfDownPressing == 0)
            gfDownNeedAck = 1;
					gfDownPressing = 1;
      }
    }
  else
    {
      gucKeyDownTimer = 0;
      gfDownPressing = 0;
    }			
//*********************Esc key*********************//
		if(PORT_KESC == 0)
    {
      gucKeyEscTimer++;
      if(gucKeyEscTimer > KEY_100MS)
      {
          if(gfEscPressing == 0)
            gfEscNeedAck = 1;
					gfEscPressing = 1;
      }
    }
  else
    {
      gucKeyEscTimer = 0;
      gfEscPressing = 0;
    }		
//*********************Menu key*********************//
  if(gfUpPressing && gfDownPressing)
    {
      gucKeyMenuTimer++;
      if(gucKeyMenuTimer > KEY_1S)
        {
          if(gfMenuPressing == 0)
            gfMenuNeedAck = 1;
					gfMenuPressing = 1;
        }
    }
  else
    {
      gucKeyMenuTimer = 0;
      gfMenuPressing = 0;
    } 
}

//*********************ENDING*********************//
//*********************ENDING*********************//
//*********************ENDING*********************//
//*********************ENDING*********************//
//*********************ENDING*********************//



uint8_t getKeyValue(void)
{
  if(gfUpNeedAck) 
    {
      gfUpNeedAck = 0;
      return KEY_UP;
    }
		
	if(gfDownNeedAck)
		{
			gfDownNeedAck = 0;
			return KEY_DOWN;
		}
		
	if(gfEnterNeedAck)
		{
			gfEnterNeedAck = 0;
			return KEY_ENTER;
		}
		
  if(gfMenuNeedAck)
    {
      gfMenuNeedAck = 0;
      return KEY_MENU;
    }
	if (gfEscNeedAck)
		{
			gfEscNeedAck = 0;
			return KEY_ESC;
		}

  if(gfONOFFNeedAck)
    {
      gfONOFFNeedAck = 0;
      return KEY_ONOFF;
    }

  return KEY_NONE;
}


void flushKeyBuf(void)
{
  gfUpNeedAck=0;
  gfDownNeedAck=0;
  gfEnterNeedAck=0;
  gfEscNeedAck=0;
  gfMenuNeedAck=0;
  gfONOFFNeedAck=0;
}

