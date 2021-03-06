CC = clang
CCXX = clang++

OPTIONS_CPP = -std=c++11
OPTIONS_ARCH = -march=armv6 -mfpu=vfp

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
	${CC} ${OPTIONS_ARCH} ${INCLUDES_C} -c ${SOURCEFILES_C} 

compile_cpp:
	@echo "Compiling cpp files..."
	${CCXX} ${OPTIONS_ARCH} -DRAPIDJSON_HAS_CXX11_RVALUE_REFS=0 -DSIO_TLS ${INCLUDES_CPP} -c ${SOURCEFILES_CPP} ${OPTIONS}

all: compile_c compile_cpp
	@echo "Linking..."
	${CCXX} *.o ${LIBDIRS} ${LIBS} -o thermostat
	
install_mail_notify:
	@echo "Installing mail notify service..."
	cp notify-by-email.sh /usr/local/bin
	chmod 755 /usr/local/bin/notify-by-email.sh
	sed -e "s/\$${FROM}/$(FROM)/" -e "s/\$${TO}/$(TO)/" notify-by-email_template@.service >> notify-by-email@.service
	mv notify-by-email@.service /lib/systemd/system
	systemctl link /lib/systemd/system/notify-by-email@.service
	
uninstall_mail_notify:
	@echo "Uninstalling  mail notify service..."
	systemctl disable notify-by-email@
	rm /lib/systemd/system/notify-by-email@.service
	rm /usr/local/bin/notify-by-email.sh
	
install: install_mail_notify
	@echo "Installing service..."
	cp thermostat /usr/local/bin
	sed -e "s/\$${URL}/$(subst /,\/,$(URL))/" -e "s/\$${TOKEN}/$(TOKEN)/" -e "s/\$${ROOMID}/$(ROOMID)/" thermostat_template.service >> thermostat.service
	mv thermostat.service /lib/systemd/system
	systemctl start thermostat
	systemctl enable thermostat
	
uninstall: uninstall_mail_notify
	@echo "Uninstalling service..."
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
