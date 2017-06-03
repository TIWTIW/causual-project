# This is Sources/COM_UART Module makefile

CPP_SRCS += \
../Sources/COM_UART/COMUART.cpp \
../Sources/COM_UART/COM_UserTypes.cpp \
../Sources/COM_UART/CRC.cc \

OBJS += \
./Sources/COM_UART/COMUART.o \
./Sources/COM_UART/COM_UserTypes.o \
./Sources/COM_UART/CRC.o \

CPP_DEPS += \
./Sources/COM_UART/COMUART.d \
./Sources/COM_UART/COM_UserTypes.d \
./Sources/COM_UART/CRC.d \




# Each subdirectory must supply rules for building sources it contributes
./Sources/COM_UART/%.o: ../Sources/COM_UART/%.cpp # Please change the related path!
	@echo 'Building file: $<'
	${CXX} ${INCLUDE_DEPS} ${CFLAGS}"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

./Sources/COM_UART/%.o: ../Sources/COM_UART/%.cc # Please change the related path!
	@echo 'Building file: $<'
	${CXX} ${INCLUDE_DEPS} ${CFLAGS}"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '