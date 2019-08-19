CXX=g++
FLAGS=--std=c++11

tests:
	$(CXX) main.cpp test_host.cpp test_frames.cpp -o tests.out $(FLAGS)

run: tests
	./tests.out

