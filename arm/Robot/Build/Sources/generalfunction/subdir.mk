CPP_SRCS += \
../Sources/generalfunction/Myfunctions.cpp \

OBJS += \
./Sources/generalfunction/Myfunctions.o \

CPP_DEPS += \
./Sources/generalfunction/Myfunctions.d \

# Each subdirectory must supply rules for building sources it contributes
./Sources/generalfunction/%.o: ../Sources/generalfunction/%.cpp
	@echo 'Building file: $<'
	${CXX} ${INCLUDE_DEPS} ${CFLAGS}"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

