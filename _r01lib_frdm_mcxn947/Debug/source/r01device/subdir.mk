################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/r01device/I2C_device.cpp \
../source/r01device/test_LM75B.cpp 

CPP_DEPS += \
./source/r01device/I2C_device.d \
./source/r01device/test_LM75B.d 

OBJS += \
./source/r01device/I2C_device.o \
./source/r01device/test_LM75B.o 


# Each subdirectory must supply rules for building sources it contributes
source/r01device/%.o: ../source/r01device/%.cpp source/r01device/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DCPU_MCXN947VDF -DCPU_MCXN947VDF_cm33 -DCPU_MCXN947VDF_cm33_core0 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/source" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/source/r01lib" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/source/r01device" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/board" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/drivers" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/device" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/utilities" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/component/uart" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/component/serial_manager" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/component/lists" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/CMSIS" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/startup" -O2 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fno-rtti -fno-exceptions -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-r01device

clean-source-2f-r01device:
	-$(RM) ./source/r01device/I2C_device.d ./source/r01device/I2C_device.o ./source/r01device/test_LM75B.d ./source/r01device/test_LM75B.o

.PHONY: clean-source-2f-r01device

