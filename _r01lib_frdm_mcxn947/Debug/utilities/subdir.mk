################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_assert.c \
../utilities/fsl_debug_console.c \
../utilities/fsl_str.c 

C_DEPS += \
./utilities/fsl_assert.d \
./utilities/fsl_debug_console.d \
./utilities/fsl_str.d 

OBJS += \
./utilities/fsl_assert.o \
./utilities/fsl_debug_console.o \
./utilities/fsl_str.o 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MCXN947VDF -DCPU_MCXN947VDF_cm33 -DCPU_MCXN947VDF_cm33_core0 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/board" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/source" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/drivers" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/device" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/utilities" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/component/uart" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/component/serial_manager" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/component/lists" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/CMSIS" -I"/Users/tedd/dev/mcuxpresso/r01projects/_r01lib_frdm_mcxn947/startup" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-utilities

clean-utilities:
	-$(RM) ./utilities/fsl_assert.d ./utilities/fsl_assert.o ./utilities/fsl_debug_console.d ./utilities/fsl_debug_console.o ./utilities/fsl_str.d ./utilities/fsl_str.o

.PHONY: clean-utilities

