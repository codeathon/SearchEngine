################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cse535_falcon/QueryProcessor/BatchQueryProcessor.cpp \
../cse535_falcon/QueryProcessor/OnlineQueryProcessor.cpp 

OBJS += \
./cse535_falcon/QueryProcessor/BatchQueryProcessor.o \
./cse535_falcon/QueryProcessor/OnlineQueryProcessor.o 

CPP_DEPS += \
./cse535_falcon/QueryProcessor/BatchQueryProcessor.d \
./cse535_falcon/QueryProcessor/OnlineQueryProcessor.d 


# Each subdirectory must supply rules for building sources it contributes
cse535_falcon/QueryProcessor/%.o: ../cse535_falcon/QueryProcessor/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


