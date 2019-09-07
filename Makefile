O_FILES=    socket_class.o \
			host.o \
			encryption.o \
			frame.o \
			binary_frame.o \
			protocol_exchange.o \
			key_exchange_init.o \
			encryption_aes128.o \
			frame_packer.o

			
TEST_FILES=	tests/test_host.o \
			tests/test_frames.o \
			tests/test_encryption.o \
			tests/test_frame_packer.o 
		


VPATH=	ssh_packets/ \
	  	socket_sources/ \
		tests/
	
CXXFLAGS=--std=c++11 -Wall -lcrypto


CXX=g++
OUT=main.o
LIBS=""

all: $(O_FILES) main.cpp
	$(CXX) main.cpp $(O_FILES) $(CXXFLAGS) -o $(OUT)

run: $(O_FILES) main.cpp
	$(CXX) main.cpp $(O_FILES) $(CXXFLAGS) -o $(OUT); ./$(OUT)

tests: $(O_FILES) $(TEST_FILES) tests/main.cpp
	$(CXX) tests/main.cpp $(O_FILES) $(TEST_FILES) -o tests/tests.o $(CXXFLAGS)

clean:
	rm *.o && rm tests/*.o

