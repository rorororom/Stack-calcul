all:
	g++ -DWITH_CANARY -DWITH_HASH main.cpp stack.cpp creator_cpu.cpp error_func.cpp log_funcs.cpp compiler.cpp cpu.cpp -o main.out

.PHONY: clean
clean:
	rm *.o

