# EETrain-MCU-system-Comprehensive-ability
using STM32H743ZI-Nucleo Board and extension board(soidered by myself) to complete a series of tasks.

I use CubeMX to initialize the peripherals of MCU and generate the code for all the configurations.
Then I use a ssd1306 Driver Library with Fonts based on stm32's hardware IIC
Sorry i forgot where i found it :(

I use a key scanning method from here: 
>https://blog.51cto.com/13719208/

Then i wrote my own menu interfaces and functional blocks.
I use DAC with DMA to generate a sine waveform based on 256-points sinetable.
if you want to control it's amplitude, you can plus the table with a variable < 1.

And, as for the ADC, i also use it with DMA, store the data in a 128-nums array, and for each read-out, add all the nums up,
and take the average. to convert the raw 16bit data into voltage, plus it with 3300/65535/1000(if you want the accurate value, you can measure the 3.3v reference on the board and change the value of 3300)

I wrote several functions to draw the Voltage-Frequency Characteristic curve on the 132*64 OLED.
Due to its low resolution, the display is not so ideal...
I may use a SPI-TFT with higher resolution to make projects in the future......

I almost forgot that, a Frequency sweep is an interesting function, i may use it to make a simple test instrument like a Sweeer.
As for the circuit, i didn't make a diagram. If you want to get some information, pls QQ me on 912283532.(Twitter as well(@summer_200816), but i won't use it frequently.)

Unfortunately, i didn't complete all the Indicators mentioned in the PDF file, because i'm still too weak :(
I take 2 weeks to complete this project. Upload its main codes as a record :D
Floydfish-2019-4-6.
