################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cse535_falcon/DocumentParsers/CBaseParser.cpp \
../cse535_falcon/DocumentParsers/CWhiteSpaceParser.cpp \
../cse535_falcon/DocumentParsers/CWikiMarkupParser.cpp 

OBJS += \
./cse535_falcon/DocumentParsers/CBaseParser.o \
./cse535_falcon/DocumentParsers/CWhiteSpaceParser.o \
./cse535_falcon/DocumentParsers/CWikiMarkupParser.o 

CPP_DEPS += \
./cse535_falcon/DocumentParsers/CBaseParser.d \
./cse535_falcon/DocumentParsers/CWhiteSpaceParser.d \
./cse535_falcon/DocumentParsers/CWikiMarkupParser.d 


# Each subdirectory must supply rules for building sources it contributes
cse535_falcon/DocumentParsers/%.o: ../cse535_falcon/DocumentParsers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


