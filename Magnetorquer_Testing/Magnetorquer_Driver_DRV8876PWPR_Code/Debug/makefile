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


BUILD_ARTIFACT_NAME := Magnetorquer_Driver_DRV8876PWPR_Code
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Magnetorquer_Driver_DRV8876PWPR_Code.elf \

MAP_FILES += \
Magnetorquer_Driver_DRV8876PWPR_Code.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Magnetorquer_Driver_DRV8876PWPR_Code.list \


# All Target
all: main-build

# Main-build Target
main-build: Magnetorquer_Driver_DRV8876PWPR_Code.elf secondary-outputs

# Tool invocations
Magnetorquer_Driver_DRV8876PWPR_Code.elf Magnetorquer_Driver_DRV8876PWPR_Code.map: $(OBJS) $(USER_OBJS) /Users/madcloud123/Documents/GitHub/Rapid-ADCS-Magnetorquer/Magnetorquer_Testing/Magnetorquer_Driver_DRV8876PWPR_Code/STM32G431KBTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Magnetorquer_Driver_DRV8876PWPR_Code.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/Users/madcloud123/Documents/GitHub/Rapid-ADCS-Magnetorquer/Magnetorquer_Testing/Magnetorquer_Driver_DRV8876PWPR_Code/STM32G431KBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Magnetorquer_Driver_DRV8876PWPR_Code.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Magnetorquer_Driver_DRV8876PWPR_Code.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Magnetorquer_Driver_DRV8876PWPR_Code.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Magnetorquer_Driver_DRV8876PWPR_Code.elf Magnetorquer_Driver_DRV8876PWPR_Code.list Magnetorquer_Driver_DRV8876PWPR_Code.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
