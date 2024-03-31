################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/r01lib/InterruptIn.cpp \
../source/r01lib/Ticker.cpp \
../source/r01lib/cpp_config.cpp \
../source/r01lib/i2c.cpp \
../source/r01lib/i3c.cpp \
../source/r01lib/io.cpp \
../source/r01lib/mcu.cpp \
../source/r01lib/obj.cpp \
../source/r01lib/spi.cpp 

C_SRCS += \
../source/r01lib/irq.c \
../source/r01lib/semihost_hardfault.c 

CPP_DEPS += \
./source/r01lib/InterruptIn.d \
./source/r01lib/Ticker.d \
./source/r01lib/cpp_config.d \
./source/r01lib/i2c.d \
./source/r01lib/i3c.d \
./source/r01lib/io.d \
./source/r01lib/mcu.d \
./source/r01lib/obj.d \
./source/r01lib/spi.d 

C_DEPS += \
./source/r01lib/irq.d \
./source/r01lib/semihost_hardfault.d 

OBJS += \
./source/r01lib/InterruptIn.o \
./source/r01lib/Ticker.o \
./source/r01lib/cpp_config.o \
./source/r01lib/i2c.o \
./source/r01lib/i3c.o \
./source/r01lib/io.o \
./source/r01lib/irq.o \
./source/r01lib/mcu.o \
./source/r01lib/obj.o \
./source/r01lib/semihost_hardfault.o \
./source/r01lib/spi.o 


# Each subdirectory must supply rules for building sources it contributes
source/r01lib/%.o: ../source/r01lib/%.cpp source/r01lib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DCPU_MCXN947VDF -DCPU_MCXN947VDF_cm33 -DCPU_MCXN947VDF_cm33_core0 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/source" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/source/r01lib" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/source/r01device" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/board" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/drivers" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/device" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/utilities" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/component/uart" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/component/serial_manager" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/component/lists" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/CMSIS" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/startup" -O2 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fno-rtti -fno-exceptions -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/r01lib/%.o: ../source/r01lib/%.c source/r01lib/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MCXN947VDF -DCPU_MCXN947VDF_cm33 -DCPU_MCXN947VDF_cm33_core0 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/board" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/source" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/drivers" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/device" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/utilities" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/component/uart" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/component/serial_manager" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/component/lists" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/CMSIS" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/startup" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-r01lib

clean-source-2f-r01lib:
	-$(RM) ./source/r01lib/InterruptIn.d ./source/r01lib/InterruptIn.o ./source/r01lib/Ticker.d ./source/r01lib/Ticker.o ./source/r01lib/cpp_config.d ./source/r01lib/cpp_config.o ./source/r01lib/i2c.d ./source/r01lib/i2c.o ./source/r01lib/i3c.d ./source/r01lib/i3c.o ./source/r01lib/io.d ./source/r01lib/io.o ./source/r01lib/irq.d ./source/r01lib/irq.o ./source/r01lib/mcu.d ./source/r01lib/mcu.o ./source/r01lib/obj.d ./source/r01lib/obj.o ./source/r01lib/semihost_hardfault.d ./source/r01lib/semihost_hardfault.o ./source/r01lib/spi.d ./source/r01lib/spi.o

.PHONY: clean-source-2f-r01lib

