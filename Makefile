all:
	g++-13 main.cpp stack.cpp error_func.cpp log_funcs.cpp calculator.cpp -o main.out

.PHONY: clean
clean:
	rm *.o

