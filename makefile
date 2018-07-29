CC = clang
CCXX = clang++

OPTIONS_CPP = -std=c++11

INCLUDES_C = -I./third-party

INCLUDES_CPP = -I./third-party
INCLUDES_CPP += -I./third-party/socket.io-client-cpp/lib/websocketpp
INCLUDES_CPP += -I./third-party/socket.io-client-cpp/lib/rapidjson/include
INCLUDES_CPP += -I${BOOST_PATH}/include

LIBDIRS = -L${BOOST_PATH}/lib

SOURCEFILES_C = ./third-party/rpi-sht1x/RPi_SHT1x.c

SOURCEFILES_CPP = ./src/*.cpp
SOURCEFILES_CPP += ./third-party/socket.io-client-cpp/src/sio_client.cpp
SOURCEFILES_CPP += ./third-party/socket.io-client-cpp/src/sio_socket.cpp
SOURCEFILES_CPP += ./third-party/socket.io-client-cpp/src/internal/sio_client_impl.cpp 
SOURCEFILES_CPP += ./third-party/socket.io-client-cpp/src/internal/sio_packet.cpp

LIBS = -lboost_system -lpthread -lbcm2835

compile_c:
	@echo "Compiling c files..."
	${CC} ${INCLUDES_C} -c ${SOURCEFILES_C} 

compile_cpp:
	@echo "Compiling cpp files..."
	${CCXX} -DRAPIDJSON_HAS_CXX11_RVALUE_REFS=0 ${INCLUDES_CPP} -c ${SOURCEFILES_CPP} ${LIBDIRS} ${LIBS} ${OPTIONS}

all: compile_c compile_cpp
	@echo "Linking..."
	${CCXX}  *.o -o thermostat

clean:
	@echo "Cleaning up.."
	-rm -rf *.o # - prefix for ignoring errors and continue execution
	-rm thermostat
