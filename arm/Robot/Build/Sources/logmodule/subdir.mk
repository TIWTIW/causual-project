CPP_SRCS += \
../Sources/logmodule/logmodule.cpp \

OBJS += \
./Sources/logmodule/logmodule.o \

CPP_DEPS += \
./Sources/logmodule/logmodule.d \

# Each subdirectory must supply rules for building sources it contributes
./Sources/logmodule/%.o: ../Sources/logmodule/%.cpp
	@echo 'Building file: $<'
	${CXX} ${INCLUDE_DEPS} ${CFLAGS}"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

