CXX_FLAGS = -D _DEBUG -std=c++17 -fsanitize=address -fsanitize=undefined
TARGET = main.out

all: main.out

main.out: main.o stack.o creator_cpu.o error_func.o compiler.o log_funcs.o
	g++ $(CXX_FLAGS) main.o stack.o creator_cpu.o error_func.o compiler.o log_funcs.o -o main.out
main.o: main.cpp Makefile
	g++ $(CXX_FLAGS) -c main.cpp -o main.o
stack.o: stack.cpp
	g++ $(CXX_FLAGS) -c stack.cpp -o stack.o
creator_cpu.o: creator_cpu.cpp
	g++ $(CXX_FLAGS) -c creator_cpu.cpp -o creator_cpu.o
error_func.o: error_func.cpp
	g++ $(CXX_FLAGS) -c error_func.cpp -o error_func.o
compiler.o: compiler.cpp
	g++ $(CXX_FLAGS) -c compiler.cpp -o compiler.o
log_funcs.o: log_funcs.cpp
	g++ $(CXX_FLAGS) -c log_funcs.cpp -o log_funcs.o

.PHONY: clean
clean:
	rm *.o
	rm main.out

.PHONY: subdirs
subdirs:
	$(MAKE) -C cpu -f cpu/makefile

