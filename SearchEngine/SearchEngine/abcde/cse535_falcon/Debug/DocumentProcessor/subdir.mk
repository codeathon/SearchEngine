################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DocumentProcessor/CDocumentProcessor.cpp 

OBJS += \
./DocumentProcessor/CDocumentProcessor.o 

CPP_DEPS += \
./DocumentProcessor/CDocumentProcessor.d 


# Each subdirectory must supply rules for building sources it contributes
DocumentProcessor/%.o: ../DocumentProcessor/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


