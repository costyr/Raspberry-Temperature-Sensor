CC = clang++

OPTIONS = -std=c++11

INCLUDES = -I./third-party
INCLUDES += -I./third-party/socket.io-client-cpp/lib/websocketpp
INCLUDES += -I./third-party/socket.io-client-cpp/lib/rapidjson/include
INCLUDES += -I${BOOST_PATH}/include

LIBDIRS = -L${BOOST_PATH}/lib

SOURCEFILES_C = ./third-party/rpi-sht1x/RPi_SHT1x.c

SOURCEFILES_CPP = ./src/*.cpp
SOURCEFILES_CPP += ./third-party/socket.io-client-cpp/src/sio_client.cpp
SOURCEFILES_CPP += ./third-party/socket.io-client-cpp/src/sio_socket.cpp
SOURCEFILES_CPP += ./third-party/socket.io-client-cpp/src/internal/sio_client_impl.cpp 
SOURCEFILES_CPP += ./third-party/socket.io-client-cpp/src/internal/sio_packet.cpp

LIBS = -lboost_system -lpthread -lbcm2835

all:
	@echo "Building..."
	${CC} -DRAPIDJSON_HAS_CXX11_RVALUE_REFS=0 ${INCLUDES} ${LIBDIRS} ${OPTIONS} -x c ${SOURCEFILES_C} -x c++ ${SOURCEFILES_CPP} ${LIBS} -o thermostat

clean:
	@echo "Cleaning up.."
	-rm -rf *.o # - prefix for ignoring errors and continue execution
	-rm thermostat
