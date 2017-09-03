CXX := arm-linux-g++

Sources = *.cpp
Sources += *.cc


main : 
	@echo "Compiling.."
	${CXX} -o main -I"/usr/local/arm/opt/FriendlyARM/toolschain/4.5.1/include" -L"/usr/local/arm/opt/FriendlyARM/toolschain/4.5.1/lib" -lpthread -lprotobuf ${Sources}
	@echo "Finish Building."
