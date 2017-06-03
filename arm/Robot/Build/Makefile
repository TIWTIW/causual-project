


CXX := arm-linux-g++
#CXX := g++

INCLUDE_DIR = $(shell pwd)/../Includes
INCLUDE_DIR_COM = ${INCLUDE_DIR}/COM_UART
INCLUDE_DIR_VisionLocation = ${INCLUDE_DIR}/VisionLocation

INCLUDE_DEPS = -I"${INCLUDE_DIR_COM}" -I"${INCLUDE_DIR}" -I"${INCLUDE_DIR_VisionLocation}"

CFLAGS := -O0 -g3 -Wall -g -c -fmessage-length=0 -std=c++0x -MMD -MP -MF

RM := rm -rf

include sources.mk
include objects.mk

# subdir makefile
include subdir.mk
include ./Sources/mapping/subdir.mk
include ./Sources/logmodule/subdir.mk
include ./Sources/generalfunction/subdir.mk
include ./Sources/subdir.mk
include ./Sources/COM_UART/subdir.mk
include ./Sources/VisionLocation/subdir.mk



ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

all: RobotV2

RobotV2: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	${CXX}  -o "RobotV2" $(OBJS) $(USER_OBJS) $(LIBS)
	#${CXX}  -o "RobotV1" $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

.PHONY: all clean dependents
# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(C_DEPS)$(CPP_DEPS) RobotV2
	-@echo ' '