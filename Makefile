O_FILES=    socket_class.o \
			host.o \
			encryption.o \
			frame.o \
			binary_frame.o \
			protocol_exchange.o \
			key_exchange_init.o \
			encryption_aes128.o \
			payload.o \
			byte.o \
			big_num.o \
			dh.o

			
TEST_FILES=	tests/test_host.o \
			tests/test_frames.o \
			tests/test_encryption.o \
			tests/test_frame_packer.o \
			tests/test_byte.o \
			tests/test_big_num.o

		


VPATH=	ssh_packets/ \
	  	socket_sources/ \
		tests/ \
		encryption/
	
CXXFLAGS=--std=c++11 -Wall -L/usr/local/opt/openssl/lib -I/usr/local/opt/openssl/include -lcrypto -g


CXX=g++
OUT=main.o
LIBS=""

all: $(O_FILES) main.cpp
	$(CXX) main.cpp $(O_FILES) $(CXXFLAGS) -o $(OUT)

run: $(O_FILES) main.cpp
	$(CXX) main.cpp $(O_FILES) $(CXXFLAGS) -o $(OUT); ./$(OUT)

tests: $(O_FILES) $(TEST_FILES) tests/main.cpp
	$(CXX) tests/main.cpp $(O_FILES) $(TEST_FILES) -o tests/tests.o $(CXXFLAGS)

poc: $(O_FILES) experiments/poc.cpp
	$(CXX) experiments/poc.cpp $(O_FILES) $(CXXFLAGS) -o experiments/poc.o

sym_enc: $(O_FILES) experiments/poc.cpp
	$(CXX) experiments/sym_enc.cpp $(O_FILES) $(CXXFLAGS) -o experiments/sym_enc.o


clean:
	rm *.o && rm tests/*.o

