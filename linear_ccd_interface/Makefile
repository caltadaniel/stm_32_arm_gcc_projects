
# Put your stlink folder here so make burn will work.
STLINK=/home/blacksmith/usr/local/bin

#per il portatile grande e solo /usr/local/bin

# Put your source files here (or *.c, etc)
SRCS=main.c system_stm32f4xx.c stm32f4xx_it.c

# Binaries will be generated with this name (.elf, .bin, .hex, etc)
PROJ_NAME=ccd_interface

# Library modules. Add here all the files you want to add
SRCS += stm32f4xx_gpio.c stm32f4xx_rcc.c stm32f4xx_exti.c stm32f4xx_usart.c misc.c stm32f4xx_tim.c stm32f4xx_syscfg.c

SRCS += stm32f4_discovery.c

# Library folder
STM_COMMON=../STM32F4xx_DSP_StdPeriph_Lib_V1.8.0

# Normally you shouldn't need to change anything below this line!
#######################################################################################

CC=arm-none-eabi-gcc
SIZE=arm-none-eabi-size
#OBJCOPY=arm-none-eabi-objcopy

#CFLAGS  = -g -O2 -Wall -Tstm32_flash.ld

#use this option for GDB
CFLAGS  = -ggdb -O2 -Wall -Tstm32_flash.ld 


CFLAGS += -DSTM32F411xE #define the microcontroller type. This is used in the system_stm32f4.c
CFLAGS += -DUSE_STDPERIPH_DRIVER #define to use the standard peripheral driver
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -I.

# Include files from STM libraries
CFLAGS += -I$(STM_COMMON)/Utilities/STM32F4-Discovery
CFLAGS += -I$(STM_COMMON)/Libraries/CMSIS/Include 
CFLAGS += -I$(STM_COMMON)/Libraries/CMSIS/Device/ST/STM32F4xx/Include
CFLAGS += -I$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/inc

# add startup file to build
SRCS += $(STM_COMMON)/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/TrueSTUDIO/startup_stm32f411xe.s
OBJS = $(SRCS:.c=.o)

vpath %.c $(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src $(STM_COMMON)/Utilities/STM32F4-Discovery

#.PHONY: proj

#all: proj

#proj: $(PROJ_NAME).elf

#$(PROJ_NAME).elf: $(SRCS)
#	$(CC) $(CFLAGS) $^ -o $@ 
#	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
#	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin

#clean:
#	rm -f *.o $(PROJ_NAME).elf $(PROJ_NAME).hex $(PROJ_NAME).bin

# Flash the STM32F4
#burn: proj
#	$(STLINK)/st-flash write $(PROJ_NAME).bin 0x8000000

SEMIHOSTING_FLAGS = --specs=rdimon.specs -lc -lrdimon 



.PHONY: all

all: $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(SEMIHOSTING_FLAGS) $(CFLAGS) $^ -o $@    
	$(SIZE) $@    

clean:
	rm -f $(PROJ_NAME).elf 


#######################################################
# Debugging targets
#######################################################
gdb: all
	arm-none-eabi-gdb $(PROJ_NAME).elf

# Start OpenOCD GDB server (supports semihosting)
openocd: 
	openocd -f board/stm32f4discovery.cfg 


