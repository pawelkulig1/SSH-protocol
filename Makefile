O_FILES=    socket_class.o \
			host.o \
			frame.o \
			binary_frame.o \
			protocol_exchange.o \
			key_exchange_init.o 



CXX=g++
OUT=main.o
LIBS=""
FLAGS=--std=c++17 

all: $(O_FILES)
	$(CXX) main.cpp $(O_FILES) $(FLAGS) -o $(OUT)

run: 
	$(CXX) $(O_FILES) $(FLAGS) -o $(OUT); ./$(OUT)

test:
	make -C tests/

socket_class.o: socket_sources/socket_class.cpp socket_sources/socket_class.h
	$(CXX) -c socket_sources/socket_class.cpp -o socket_class.o $(FLAGS)

host.o: host.cpp host.h
	$(CXX) -c host.cpp -o host.o $(FLAGS)

frame.o: ssh_packets/frame.cpp ssh_packets/frame.h
	$(CXX) -c ssh_packets/frame.cpp -o frame.o $(FLAGS)

protocol_exchange.o: frame.o ssh_packets/protocol_exchange.cpp ssh_packets/protocol_exchange.h 
	$(CXX) -c ssh_packets/protocol_exchange.cpp -o protocol_exchange.o $(FLAGS)

binary_frame.o: frame.o ssh_packets/binary_frame.cpp ssh_packets/binary_frame.h 
	$(CXX) -c ssh_packets/binary_frame.cpp -o binary_frame.o $(FLAGS)

key_exchange_init.o: frame.o ssh_packets/key_exchange_init.cpp ssh_packets/key_exchange_init.h 
	$(CXX) -c ssh_packets/key_exchange_init.cpp -o key_exchange_init.o $(FLAGS)

clean:
	rm *.o

