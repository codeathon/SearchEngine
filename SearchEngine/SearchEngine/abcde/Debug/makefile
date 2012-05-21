################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include cse535_falcon/src/subdir.mk
-include cse535_falcon/TokenProcessor/subdir.mk
-include cse535_falcon/Ranker/subdir.mk
-include cse535_falcon/QueryRepresentation/subdir.mk
-include cse535_falcon/QueryProcessor/subdir.mk
-include cse535_falcon/QueryParser/subdir.mk
-include cse535_falcon/Indexer/subdir.mk
-include cse535_falcon/DocumentRepresentation/subdir.mk
-include cse535_falcon/DocumentProcessor/subdir.mk
-include cse535_falcon/DocumentParsers/subdir.mk
-include cse535_falcon/Debug/src/subdir.mk
-include cse535_falcon/Debug/TokenProcessor/subdir.mk
-include cse535_falcon/Debug/Indexer/subdir.mk
-include cse535_falcon/Debug/DocumentRepresentation/subdir.mk
-include cse535_falcon/Debug/DocumentProcessor/subdir.mk
-include cse535_falcon/Debug/DocumentParsers/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: abcde

# Tool invocations
abcde: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++  -o "abcde" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) abcde
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
