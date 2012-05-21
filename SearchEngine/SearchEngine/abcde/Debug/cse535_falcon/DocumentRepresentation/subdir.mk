################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cse535_falcon/DocumentRepresentation/CDocument.cpp 

OBJS += \
./cse535_falcon/DocumentRepresentation/CDocument.o 

CPP_DEPS += \
./cse535_falcon/DocumentRepresentation/CDocument.d 


# Each subdirectory must supply rules for building sources it contributes
cse535_falcon/DocumentRepresentation/%.o: ../cse535_falcon/DocumentRepresentation/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


