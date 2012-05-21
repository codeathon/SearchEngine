################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cse535_falcon/Indexer/Config.cpp \
../cse535_falcon/Indexer/FileHelper.cpp \
../cse535_falcon/Indexer/InvertedIndexer.cpp \
../cse535_falcon/Indexer/StringHelper.cpp \
../cse535_falcon/Indexer/forwardIndexer.cpp 

OBJS += \
./cse535_falcon/Indexer/Config.o \
./cse535_falcon/Indexer/FileHelper.o \
./cse535_falcon/Indexer/InvertedIndexer.o \
./cse535_falcon/Indexer/StringHelper.o \
./cse535_falcon/Indexer/forwardIndexer.o 

CPP_DEPS += \
./cse535_falcon/Indexer/Config.d \
./cse535_falcon/Indexer/FileHelper.d \
./cse535_falcon/Indexer/InvertedIndexer.d \
./cse535_falcon/Indexer/StringHelper.d \
./cse535_falcon/Indexer/forwardIndexer.d 


# Each subdirectory must supply rules for building sources it contributes
cse535_falcon/Indexer/%.o: ../cse535_falcon/Indexer/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


