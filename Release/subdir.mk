################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
../weather_client.ino 

CPP_SRCS += \
../.ino.cpp \
../convert.cpp 

LINK_OBJ += \
./.ino.cpp.o \
./convert.cpp.o 

INO_DEPS += \
./weather_client.ino.d 

CPP_DEPS += \
./.ino.cpp.d \
./convert.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
.ino.cpp.o: ../.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10605 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR     -I"E:\Arduino\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\hardware\arduino\avr\variants\standard" -I"C:\Users\Brady\Documents\Arduino\libraries\DHTlib" -I"C:\Users\Brady\Documents\Arduino\libraries\RF24-master" -I"E:\Arduino\hardware\arduino\avr\libraries\SPI" -I"E:\Arduino\hardware\arduino\avr\libraries\Wire" -I"E:\Arduino\hardware\arduino\avr\libraries\Wire\utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

convert.cpp.o: ../convert.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10605 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR     -I"E:\Arduino\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\hardware\arduino\avr\variants\standard" -I"C:\Users\Brady\Documents\Arduino\libraries\DHTlib" -I"C:\Users\Brady\Documents\Arduino\libraries\RF24-master" -I"E:\Arduino\hardware\arduino\avr\libraries\SPI" -I"E:\Arduino\hardware\arduino\avr\libraries\Wire" -I"E:\Arduino\hardware\arduino\avr\libraries\Wire\utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

weather_client.o: ../weather_client.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"E:\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10605 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR     -I"E:\Arduino\hardware\arduino\avr\cores\arduino" -I"E:\Arduino\hardware\arduino\avr\variants\standard" -I"C:\Users\Brady\Documents\Arduino\libraries\DHTlib" -I"C:\Users\Brady\Documents\Arduino\libraries\RF24-master" -I"E:\Arduino\hardware\arduino\avr\libraries\SPI" -I"E:\Arduino\hardware\arduino\avr\libraries\Wire" -I"E:\Arduino\hardware\arduino\avr\libraries\Wire\utility" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


