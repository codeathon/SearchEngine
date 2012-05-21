################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TokenProcessor/CBasicEnglishTokenProcessor.cpp \
../TokenProcessor/CBasicTokenProcessor.cpp \
../TokenProcessor/CWikiTokenProcessor.cpp 

OBJS += \
./TokenProcessor/CBasicEnglishTokenProcessor.o \
./TokenProcessor/CBasicTokenProcessor.o \
./TokenProcessor/CWikiTokenProcessor.o 

CPP_DEPS += \
./TokenProcessor/CBasicEnglishTokenProcessor.d \
./TokenProcessor/CBasicTokenProcessor.d \
./TokenProcessor/CWikiTokenProcessor.d 


# Each subdirectory must supply rules for building sources it contributes
TokenProcessor/%.o: ../TokenProcessor/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


