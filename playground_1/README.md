This is a reminder on the issues encountered during the development:
1) GDB was not working due to the fact that teh program was failing.
I used the RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);function but it seems that the GPIOA was not proprely set up
2)in order to setup the semihosting i had to add "PROVIDE (__end__=.);" to the stm32_flash.ld
If you want to include semihosting on other projects, just use the provided file
3)The timing of the output was wrong. Then I discovered that this was caused by a wrong setup of the board oscillator on the file system_stm32f4xx.c
For the stm32f411ve the nominal frequency is 100MHz, PLL_N is 400, PLL_M is 8 and PLL_P is 4
