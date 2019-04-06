#include "menu.h"
#include "sine.h"

void OS_Main(void) // Main Menu
{
	SSD1306_Fill (0);
	SSD1306_UpdateScreen(); //display
	while(1)
	{
		kv = getKeyValue();
		SSD1306_GotoXY (10,12);
		SSD1306_Puts ("Hello!", &Font_11x18, 1);
		SSD1306_GotoXY (10, 34);
		SSD1306_Puts ("Floyd", &Font_11x18, 1);
		SSD1306_UpdateScreen(); //display
		
		if (kv == KEY_ESC)
		{
			OS_Init();
			//flushKeyBuf();
			break;
		}
	}
}

void OS_Menu1(void) // Menu Level 1
{
	uint32_t freqValue = 100;
	char buf[10];
	uint32_t value;
	SSD1306_Fill (0);
	SSD1306_UpdateScreen(); //display
	//HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);
	HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, sineBuf, 256, DAC_ALIGN_12B_R);
	
	while(1)
	{
		kv = getKeyValue();
		SSD1306_GotoXY (10,12);
		SSD1306_Puts ("Sine GNT", &Font_11x18, 1);
		SSD1306_UpdateScreen(); //display
		value = freqValue;
		sprintf(buf, "%6.1d Hz   ", value);
		SSD1306_GotoXY (10, 34);
		SSD1306_Puts (buf, &Font_11x18, 1);
		SSD1306_UpdateScreen(); //display
		
		if (kv == KEY_UP)
		{
			if (freqValue < 10000)
				freqValue += 100;
			else if (freqValue == 10000)
				freqValue = 100;
		}
		
		else if (kv == KEY_DOWN)
		{
			if (freqValue > 100)
				freqValue -= 100;
			else if (freqValue == 100)
				freqValue = 10000;
		}
		
		else if (kv == KEY_ESC)
		{
			//HAL_DAC_Stop(&hdac1, DAC_CHANNEL_1);
			OS_Init();
			HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_1);
			break;
		}
		setSineFreq(freqValue);
	}
}

void OS_Menu2(void) // Menu Level 2
{
	
	char buf[10];
	uint32_t ad;
	SSD1306_Fill (0);
	SSD1306_UpdateScreen(); //display
	//HAL_ADC_Start(&hadc1);
	HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, sineBuf, 256, DAC_ALIGN_12B_R);
	setSineFreq(1000);
	
	while(1)
	{
		kv = getKeyValue();
		SSD1306_GotoXY (10,12);
		SSD1306_Puts ("Peak Volt.", &Font_11x18, 1);
		SSD1306_GotoXY (10, 34);
		
		SSD1306_Puts ("Volt:", &Font_7x10, 1);
		SSD1306_UpdateScreen(); //display
		
		for(uint8_t i = 0; i < 128; i++)
		{
			ad += ADC_Value[i];
		}
		sprintf(buf, "%4.3f V      ", (double)ad*3300/65536/128/1000);
		ad = 0;
		
		SSD1306_GotoXY (10, 48);
		SSD1306_Puts (buf, &Font_7x10, 1);
		SSD1306_UpdateScreen(); //display
		
		if (kv == KEY_ESC)
		{
			OS_Init();
			HAL_DAC_Stop_DMA(&hdac1, DAC_CHANNEL_1);
			break;
		}
	}
}

void OS_Menu3(void) // Menu Level 3
{
	HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, sineTable, 256, DAC_ALIGN_12B_R);
	SSD1306_Fill (0);
	SSD1306_UpdateScreen();
	
	
	SSD1306_GotoXY (10,12);
	SSD1306_Puts ("Hello!", &Font_11x18, 1);
	SSD1306_GotoXY (10, 34);
	SSD1306_Puts ("Press Up to Draw", &Font_7x10, 1);
	SSD1306_GotoXY (10, 48);
	SSD1306_Puts ("Down to Judge", &Font_7x10, 1);
	SSD1306_UpdateScreen();
	
	while(1)
	{
		kv = getKeyValue();

		SSD1306_GotoXY (10,12);
		SSD1306_Puts ("Hello!", &Font_11x18, 1);
		SSD1306_GotoXY (10, 34);
		SSD1306_Puts ("Press Up to Draw", &Font_7x10, 1);
		SSD1306_GotoXY (10, 48);
		SSD1306_Puts ("Down to Judge", &Font_7x10, 1);
		SSD1306_UpdateScreen();
		
		if (kv == KEY_UP)
		{
			OS_Menu3_1();
			
		}
		else if (kv == KEY_DOWN)
		{
			OS_Menu3_2();
			
		}
		
		else if (kv == KEY_ESC)
		{
			OS_Init();
			break;
		}
	}
}

void OS_Menu3_1(void) //Draw curve
{
	SSD1306_Fill (0);
	SSD1306_UpdateScreen();
	
	SSD1306_GotoXY (10,12);
	SSD1306_Puts ("Curve :D", &Font_11x18, 1);
	SSD1306_GotoXY (10, 34);
	SSD1306_Puts ("Press Enter", &Font_7x10, 1);
	SSD1306_UpdateScreen();
	
	while(1)
	{
		kv = getKeyValue();
		
		SSD1306_GotoXY (10,12);
		SSD1306_Puts ("Curve :D", &Font_11x18, 1);
		SSD1306_GotoXY (10, 34);
		SSD1306_Puts ("Press Enter", &Font_7x10, 1);
		SSD1306_GotoXY (10, 48);
		SSD1306_Puts ("to Draw", &Font_7x10, 1);
		SSD1306_UpdateScreen();
		
		if (kv == KEY_ENTER)
		{
			drawCurve();
			
		}
		else if (kv == KEY_ESC)
		{
			SSD1306_Fill(0);
			SSD1306_UpdateScreen();
			break;
		}
	}
}

void OS_Menu3_2(void) //Judge the types of filters
{
	SSD1306_Fill (0);
	SSD1306_UpdateScreen();
	
	while(1)
	{
		kv = getKeyValue();
		
		SSD1306_GotoXY (10,12);
		SSD1306_Puts ("Types :D", &Font_11x18, 1);
		SSD1306_GotoXY (10, 34);
		SSD1306_Puts ("Press Enter", &Font_7x10, 1);
		SSD1306_GotoXY (10, 48);
		SSD1306_Puts ("to Judge", &Font_7x10, 1);
		SSD1306_UpdateScreen();
		
		if (kv == KEY_ESC)
		{
			SSD1306_Fill(0);
			SSD1306_UpdateScreen();
			break;
		}
	}
	
}
void drawCurve(void) // Function of Drawing curves
{
	uint32_t ad;
	uint16_t disBuffer[100];
	SSD1306_Fill(0);
	SSD1306_UpdateScreen();
	
	for (uint8_t i = 0; i < Curve_X; i++)
	{
		setSineFreq(100+(i+1)*100);
		HAL_Delay(25);
		for(uint8_t j = 0; j < 128; j++)
		{
			ad += ADC_Value[j];
		}
		ad /= 128;
		curveBuffer[i] = ad;
		ad = 0;
	}
	
	SSD1306_DrawLine(18, 0, 18, 63, 1);
	SSD1306_DrawLine(0, Curve_Y, 127, Curve_Y, 1);
	SSD1306_GotoXY(55, 52);
	SSD1306_Puts("Freq/100HZ", &Font_7x10, 1);
	SSD1306_UpdateScreen();
	
	for (uint8_t k = 0; k < 100; k++)
		disBuffer[k] = mmap(50, 0, (double)curveBuffer[k]*3370/65536/1000);
	
	for (uint8_t i = 0; i < Curve_X; i++)
	{
		if (i != Curve_X - 1)
			SSD1306_DrawLine(i+18, Curve_Y-disBuffer[i], i+1+18, Curve_Y-disBuffer[i+1], 1);
		else if (i == Curve_X - 1)
			SSD1306_DrawLine(i-1+18, Curve_Y-disBuffer[i-1], i+18, Curve_Y-disBuffer[i], 1);
	}
	SSD1306_UpdateScreen();
	
	while(1)
	{
		kv = getKeyValue();
		if (kv == KEY_ESC)
		{
			SSD1306_Fill(0);
			SSD1306_UpdateScreen();
			break;
		}
	}
}

void OS_CopyRight(void) //Copyright Menu
{
	SSD1306_Fill (0);
	SSD1306_UpdateScreen(); //display
	
	
	SSD1306_GotoXY (10,12);
	SSD1306_Puts ("By", &Font_11x18, 1);
	SSD1306_GotoXY (10, 34);
	SSD1306_Puts ("Floydfish.", &Font_11x18, 1);
	SSD1306_UpdateScreen(); //display
	while (1)
	{
		kv = getKeyValue();
		if (kv == KEY_ESC)
		{
			OS_Init();
			break;
		}
	}
}

void OS_Init(void) // Initializing the Operating System
{
	SSD1306_Fill (0);
	SSD1306_UpdateScreen(); //display
	
	uint8_t color_index[4] = {0, 0, 0,	0};
	color_index[menu_index] = 1;
	
	SSD1306_DrawFilledRectangle(9, menu_index*15+3, 114, 13, 1);
	SSD1306_GotoXY(90, menu_index*15+5);
	SSD1306_Puts("<<<", &Font_7x10, 0);
	
	SSD1306_GotoXY(10, 5);
	SSD1306_Puts("Sine GNT", &Font_7x10, color_index[0]);
	SSD1306_GotoXY(10, 20);
	SSD1306_Puts("Peak Detect", &Font_7x10, color_index[1]);
	SSD1306_GotoXY(10, 35);
	SSD1306_Puts("Draw Curve", &Font_7x10, color_index[2]);
	SSD1306_GotoXY(10, 50);
	SSD1306_Puts("CopyRight", &Font_7x10, color_index[3]);
	
	SSD1306_UpdateScreen();
	
}

void OS_Trans(void) // Trasnport Tasks between Menu_1-Menu_n
{
	kv = getKeyValue();
		if (kv == KEY_UP)
		{
			if (menu_index > 0)
				menu_index--;
			else if (menu_index == 0)
				menu_index = 3;
			OS_Init();
			flushKeyBuf();
		}
		
		else if (kv == KEY_DOWN)
		{
			if (menu_index == 3)
				menu_index = 0;
			else if (menu_index < 3)
				menu_index++;
			OS_Init();
			flushKeyBuf();
		}
		
		else if (kv == KEY_ENTER)
		{
			switch (menu_index)
			{
				case 0 :	OS_Menu1();
									flushKeyBuf();
					break;
				case 1 :	OS_Menu2();
									flushKeyBuf();
					break;
				case 2 :	OS_Menu3();
									flushKeyBuf();
					break;
				case 3 :	OS_CopyRight();
									flushKeyBuf();
					break;
				default : break;
			}
		}
		
		else if (kv == KEY_ESC)
		{
			OS_Init();
			flushKeyBuf();
			HAL_Delay(5);
		}
}

uint16_t mmap(uint32_t max, uint32_t min, double num) // "mmap" function for dividing curve points.
{
	if (num > 2.50)
		return max;
	else
	{
		for (uint8_t i = 1; i <= 50; i++)
		{
			if (num >= (i-1)*0.05 && num <= i*0.05)
			{
				return i;
				break;
			}
		}
		return max;
	}
}













