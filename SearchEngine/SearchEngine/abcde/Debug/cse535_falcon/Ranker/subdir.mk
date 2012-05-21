################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cse535_falcon/Ranker/BM25.cpp \
../cse535_falcon/Ranker/QueryResult.cpp \
../cse535_falcon/Ranker/VectorSpaceModel.cpp \
../cse535_falcon/Ranker/booleanModel.cpp 

OBJS += \
./cse535_falcon/Ranker/BM25.o \
./cse535_falcon/Ranker/QueryResult.o \
./cse535_falcon/Ranker/VectorSpaceModel.o \
./cse535_falcon/Ranker/booleanModel.o 

CPP_DEPS += \
./cse535_falcon/Ranker/BM25.d \
./cse535_falcon/Ranker/QueryResult.d \
./cse535_falcon/Ranker/VectorSpaceModel.d \
./cse535_falcon/Ranker/booleanModel.d 


# Each subdirectory must supply rules for building sources it contributes
cse535_falcon/Ranker/%.o: ../cse535_falcon/Ranker/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


