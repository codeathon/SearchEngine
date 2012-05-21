################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DocumentParsers/CBaseParser.cpp \
../DocumentParsers/CWhiteSpaceParser.cpp \
../DocumentParsers/CWikiMarkupParser.cpp 

OBJS += \
./DocumentParsers/CBaseParser.o \
./DocumentParsers/CWhiteSpaceParser.o \
./DocumentParsers/CWikiMarkupParser.o 

CPP_DEPS += \
./DocumentParsers/CBaseParser.d \
./DocumentParsers/CWhiteSpaceParser.d \
./DocumentParsers/CWikiMarkupParser.d 


# Each subdirectory must supply rules for building sources it contributes
DocumentParsers/%.o: ../DocumentParsers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


