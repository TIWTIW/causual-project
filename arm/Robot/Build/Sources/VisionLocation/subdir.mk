CPP_SRCS += \
../Sources/VisionLocation/cornerextraction.cpp \
../Sources/VisionLocation/cornermatching.cpp \
../Sources/VisionLocation/poseestimate.cpp \
../Sources/VisionLocation/location.cpp \
../Sources/VisionLocation/camera.cpp \
../Sources/VisionLocation/frame.cpp \
../Sources/VisionLocation/pose.cpp \


OBJS += \
./Sources/VisionLocation/cornerextraction.o \
./Sources/VisionLocation/cornermatching.o \
./Sources/VisionLocation/poseestimate.o \
./Sources/VisionLocation/location.o \
./Sources/VisionLocation/camera.o \
./Sources/VisionLocation/frame.o \
./Sources/VisionLocation/pose.o \


CPP_DEPS += \
./Sources/VisionLocation/cornerextraction.d \
./Sources/VisionLocation/cornermatching.d \
./Sources/VisionLocation/poseestimate.d \
./Sources/VisionLocation/location.d \
./Sources/VisionLocation/camera.d \
./Sources/VisionLocation/frame.d \
./Sources/VisionLocation/pose.d \


# Each subdirectory must supply rules for building sources it contributes
./Sources/COM_UART/%.o: ../Sources/VisionLocation/%.cpp # Please change the related path!
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	${CXX} ${INCLUDE_DEPS} ${CFLAGS}"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

./Sources/COM_UART/%.o: ../Sources/VisionLocation/%.cc # Please change the related path!
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	${CXX} ${INCLUDE_DEPS} ${CFLAGS}"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '