CPP_SRCS += \
../Sources/videodevice.cpp \
../Sources/RobotTypes.cpp \
../Sources/location_imu.cpp \
../Sources/CommandGenerator.cpp \
../Sources/Robot_COM_NodeX.cpp \
../Sources/Robot_VisionNavV2_L1.cpp \
../Sources/Robot_VisionNavV2_L2.cpp \
../Sources/Robot_VisionNavV2_L3.cpp \
../Sources/pictureType.cpp \
../Sources/centerline.cpp \
../Sources/dete.cpp \
../Sources/distance_decoder.cpp \
../Sources/distance_measure.cpp \
../Sources/mark.cpp \
../Sources/test_function.cpp \

#../Sources/RobotV2_VisionNav_L1_V1.cpp \
../Sources/RobotV2_VisionNav_L2.cpp \
../Sources/RobotV2_VisionNav_L3.cpp \
../Sources/Robot_COM_NodeX.cpp \

#../Sources/RobotV2_VisionNav_L1.cpp \

OBJS += \
./Sources/videodevice.o \
./Sources/RobotTypes.o \
./Sources/location_imu.o \
./Sources/CommandGenerator.o \
./Sources/Robot_COM_NodeX.o \
./Sources/Robot_VisionNavV2_L1.o \
./Sources/Robot_VisionNavV2_L2.o \
./Sources/Robot_VisionNavV2_L3.o \
./Sources/pictureType.o \
./Sources/centerline.o \
./Sources/dete.o \
./Sources/distance_decoder.o \
./Sources/distance_measure.o \
./Sources/mark.o \
./Sources/test_function.o \

#./Sources/RobotV2_VisionNav_L1.o \
./Sources/RobotV2_VisionNav_L1_V1.o \
./Sources/RobotV2_VisionNav_L2.o \
./Sources/RobotV2_VisionNav_L3.o \

CPP_DEPS += \
./Sources/videodevice.d \
./Sources/RobotTypes.d \
./Sources/location_imu.d \
./Sources/CommandGenerator.d \
./Sources/Robot_COM_NodeX.d \
./Sources/Robot_VisionNavV2_L1.d \
./Sources/Robot_VisionNavV2_L2.d \
./Sources/Robot_VisionNavV2_L3.d \
./Sources/pictureTypes.d \
./Sources/centerline.d \
./Sources/dete.d \
./Sources/distance_decoder.d \
./Sources/distance_measure.d \
./Sources/mark.d \
./Sources/test_function.d \

#./Sources/RobotV2_VisionNav_L1.d \
./Sources/RobotV2_VisionNav_L1_V1.d \
./Sources/RobotV2_VisionNav_L2.d \
./Sources/RobotV2_VisionNav_L3.d \


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.cpp
	@echo 'Building file: $<'
	${CXX} ${INCLUDE_DEPS} ${CFLAGS}"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '