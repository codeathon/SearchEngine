################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cse535_falcon/TokenProcessor/CBasicEnglishTokenProcessor.cpp \
../cse535_falcon/TokenProcessor/CBasicTokenProcessor.cpp \
../cse535_falcon/TokenProcessor/CWikiTokenProcessor.cpp 

OBJS += \
./cse535_falcon/TokenProcessor/CBasicEnglishTokenProcessor.o \
./cse535_falcon/TokenProcessor/CBasicTokenProcessor.o \
./cse535_falcon/TokenProcessor/CWikiTokenProcessor.o 

CPP_DEPS += \
./cse535_falcon/TokenProcessor/CBasicEnglishTokenProcessor.d \
./cse535_falcon/TokenProcessor/CBasicTokenProcessor.d \
./cse535_falcon/TokenProcessor/CWikiTokenProcessor.d 


# Each subdirectory must supply rules for building sources it contributes
cse535_falcon/TokenProcessor/%.o: ../cse535_falcon/TokenProcessor/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


