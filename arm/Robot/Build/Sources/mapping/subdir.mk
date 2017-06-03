CPP_SRCS += \
../Sources/mapping/grid_map_core.cpp \
../Sources/mapping/grid_map_coordinate.cpp \
../Sources/mapping/GlobalPlanning.cpp \

OBJS += \
./Sources/mapping/grid_map_core.o \
./Sources/mapping/grid_map_coordinate.o \
./Sources/mapping/GlobalPlanning.o \

CPP_DEPS += \
./Sources/mapping/grid_map_core.d \
./Sources/mapping/grid_map_coordinate.d \
./Sources/mapping/GlobalPlanning.d \

# Each subdirectory must supply rules for building sources it contributes
./Sources/mapping/%.o: ../Sources/mapping/%.cpp
	@echo 'Building file: $<'
	${CXX} ${INCLUDE_DEPS} ${CFLAGS}"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

