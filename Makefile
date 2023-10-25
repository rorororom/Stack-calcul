all: compiler cpu

compiler:
	cd compiler && make && cd ..

cpu:
	cd cpu && make && cd ..

.PHONY: compiler cpu

run:
	cd compiler/ && ./main.out
	cd cpu/ && ./main.out

clean:
	cd compiler && make clean && cd ..
	cd cpu && make clean && cd ..
	cd common && rm -rf *.o && cd ..


