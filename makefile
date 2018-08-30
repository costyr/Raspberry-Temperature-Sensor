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

LIBS = -lboost_system -lpthread -lbcm2835 -lcrypto -lssl

compile_c:
	@echo "Compiling c files..."
	${CC} ${INCLUDES_C} -c ${SOURCEFILES_C} 

compile_cpp:
	@echo "Compiling cpp files..."
	${CCXX} -DRAPIDJSON_HAS_CXX11_RVALUE_REFS=0 -DSIO_TLS ${INCLUDES_CPP} -c ${SOURCEFILES_CPP} ${OPTIONS}

all: compile_c compile_cpp
	@echo "Linking..."
	${CCXX} *.o ${LIBDIRS} ${LIBS} -o thermostat
	
install:
	@echo "Installing service..."
	cp thermostat /usr/local/bin
	rm thermostat.service
	@echo "[Unit]" >> thermostat.service
	@echo "Description=Thermostat service" >> thermostat.service
	@echo "After=network.target" >> thermostat.service
	@echo "StartLimitIntervalSec=0" >> thermostat.service
	@echo "[Service]" >> thermostat.service
	@echo "Type=simple" >> thermostat.service
	@echo "Restart=always" >> thermostat.service
	@echo "RestartSec=1+" >> thermostat.service
	@echo "User=pi" >> thermostat.service
	@echo "ExecStart=/usr/local/bin/thermostat --server_url "$(URL)" --server_token "$(TOKEN)" --room_id "$(ROOMID)" --log_sensor_data" >> thermostat.service
	@echo "StandardOutput=/var/log/thermostat.log"
	@echo "StandardError=/var/log/thermostat.log"
	@echo "[Install]" >> thermostat.service
	@echo "WantedBy=multi-user.target" >> thermostat.service
	cp thermostat.service /lib/systemd/system
	systemctl start thermostat
	systemctl enable thermostat
	
uninstall:
	@echo "Uinstalling service..."
	systemctl stop thermostat
	systemctl disable thermostat
	rm /lib/systemd/system/thermostat.service
	systemctl daemon-reload
	systemctl reset-failed
	rm /usr/local/bin/thermostat
	
clean:
	@echo "Cleaning up.."
	-rm -rf *.o # - prefix for ignoring errors and continue execution
	-rm thermostat
