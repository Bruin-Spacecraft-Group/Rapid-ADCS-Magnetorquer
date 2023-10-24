################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32G4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Magnetometer_IIS2MDCTR_Code
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Magnetometer_IIS2MDCTR_Code.elf \

MAP_FILES += \
Magnetometer_IIS2MDCTR_Code.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Magnetometer_IIS2MDCTR_Code.list \


# All Target
all: main-build

# Main-build Target
main-build: Magnetometer_IIS2MDCTR_Code.elf secondary-outputs

# Tool invocations
Magnetometer_IIS2MDCTR_Code.elf Magnetometer_IIS2MDCTR_Code.map: $(OBJS) $(USER_OBJS) C:\Users\munng\OneDrive\Documents\GitHub\Rapid-ADCS-Magnetorquer\Magnetorquer_Testing\Magnetometer_IIS2MDCTR_Code\STM32G431KBTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Magnetometer_IIS2MDCTR_Code.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\munng\OneDrive\Documents\GitHub\Rapid-ADCS-Magnetorquer\Magnetorquer_Testing\Magnetometer_IIS2MDCTR_Code\STM32G431KBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Magnetometer_IIS2MDCTR_Code.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Magnetometer_IIS2MDCTR_Code.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Magnetometer_IIS2MDCTR_Code.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Magnetometer_IIS2MDCTR_Code.elf Magnetometer_IIS2MDCTR_Code.list Magnetometer_IIS2MDCTR_Code.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
