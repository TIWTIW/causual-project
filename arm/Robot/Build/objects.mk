USER_OBJS :=

OPENCV_LIBS :=  \
-lopencv_highgui -lopencv_core \
-lopencv_features2d -lopencv_imgproc \
-lopencv_objdetect -lopencv_video \
-lopencv_photo -lopencv_calib3d


LIBS := -lpthread -lrt -ldl ${OPENCV_LIBS}