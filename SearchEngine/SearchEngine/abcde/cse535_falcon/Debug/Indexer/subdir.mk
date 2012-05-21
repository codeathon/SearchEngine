################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Indexer/Config.cpp \
../Indexer/FileHelper.cpp \
../Indexer/InvertedIndexer.cpp \
../Indexer/StringHelper.cpp 

OBJS += \
./Indexer/Config.o \
./Indexer/FileHelper.o \
./Indexer/InvertedIndexer.o \
./Indexer/StringHelper.o 

CPP_DEPS += \
./Indexer/Config.d \
./Indexer/FileHelper.d \
./Indexer/InvertedIndexer.d \
./Indexer/StringHelper.d 


# Each subdirectory must supply rules for building sources it contributes
Indexer/%.o: ../Indexer/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


