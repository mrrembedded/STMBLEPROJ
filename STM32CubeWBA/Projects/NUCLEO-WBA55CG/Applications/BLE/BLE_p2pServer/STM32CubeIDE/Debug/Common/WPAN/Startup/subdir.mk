################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
D:/Companies/Migration/STMBLEEVK/STMBLEPROJ/STM32CubeWBA/Projects/Common/WPAN/Startup/stm32wbaxx_ResetHandler_GCC.s 

OBJS += \
./Common/WPAN/Startup/stm32wbaxx_ResetHandler_GCC.o 

S_DEPS += \
./Common/WPAN/Startup/stm32wbaxx_ResetHandler_GCC.d 


# Each subdirectory must supply rules for building sources it contributes
Common/WPAN/Startup/stm32wbaxx_ResetHandler_GCC.o: D:/Companies/Migration/STMBLEEVK/STMBLEPROJ/STM32CubeWBA/Projects/Common/WPAN/Startup/stm32wbaxx_ResetHandler_GCC.s Common/WPAN/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m33 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Common-2f-WPAN-2f-Startup

clean-Common-2f-WPAN-2f-Startup:
	-$(RM) ./Common/WPAN/Startup/stm32wbaxx_ResetHandler_GCC.d ./Common/WPAN/Startup/stm32wbaxx_ResetHandler_GCC.o

.PHONY: clean-Common-2f-WPAN-2f-Startup

