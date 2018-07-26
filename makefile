CC = g++

OPTIONS = -std=c++11

INCLUDES = -I./third-party
INCLUDES += -I./third-party/socket.io-client-cpp/lib/websocketpp
INCLUDES += -I./third-party/socket.io-client-cpp/lib/rapidjson/include
INCLUDES += -I./third-party/boost_1_67_0/include

LIBDIRS = -L./third-party/boost_1_67_0/lib

SOURCEFILES = ./src/thermostat.cpp
SOURCEFILES += ./third-party/socket.io-client-cpp/src/sio_client.cpp
SOURCEFILES += ./third-party/socket.io-client-cpp/src/sio_socket.cpp
SOURCEFILES += ./third-party/socket.io-client-cpp/src/internal/sio_client_impl.cpp 
SOURCEFILES += ./third-party/socket.io-client-cpp/src/internal/sio_packet.cpp

LIBS = -lboost_system -lpthread

all:
	@echo "Building..."
	${CC} ${INCLUDES} ${LIBDIRS} ${OPTIONS} ${SOURCEFILES} ${LIBS} -o thermostat

clean:
	@echo "Cleaning up.."
	-rm -rf *.o # - prefix for ignoring errors and continue execution
	-rm thermostat
