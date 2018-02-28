

<br>
Contents:

1. LED blinker sample code (buildable)
2. USB virtual serial port code (buildable)
2. Semihosting Hello World sample code (buildable)
3. Template file with gdb settings (buildable)
4. Playground1 with example of multiple periphrial use in the same program
3. STM sample code (buildable)
4. STM libraries and headers


<br>
STM libraries, headers, and samples have been modified to work with GNU Tools for ARM Embedded Processors toolchain and STM32F4 Discovery EVB.   Generally this just involved adding Makefiles and a slightly modified version of the TrueStudio linker file.   In the Project directory, everything under Demonstration, FW\_upgrade, and Peripheral\_Examples is buildable from the command line by running 'make'

STM's approach toward 'library code' is somewhat non-traditional.  Rather than building libraries up front and linking them with your source, STM appears to intend for you to include their individual source files in your code's build.   Some of their source files include local headers and modules (i.e. stm32f4xx\_conf.h, stm32f4xx\_it.c/h, system\_stm32f4xx.c, etc) that you modify/store in your source tree.  Because of this, building the library up front wouldn't work properly, as the configuration for some library modules could vary from project to project.

<br>

In order to have the projects working with make, you have to add two folders to the PATH variables.
I made it with the script myenvvars.sh stored in /etc/profile.d. 
The content is:
export PATH=$PATH:/home/blacksmith/openocd-0.10.0/bin:/home/blacksmith/opt/gcc-arm-none-eabi-7-2017-q4-major/bin



