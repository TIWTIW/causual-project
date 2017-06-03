CPP_SRCS += \
../main.cpp

OBJS += \
./main.o

CPP_DEPS += \
./main.d


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	${CXX} ${INCLUDE_DEPS} ${CFLAGS}"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
