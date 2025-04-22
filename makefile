run:
	g++ src/main.cpp src/instructions.cpp src/functions.cpp -o main -std=c++17 \
    -I/usr/local/systemc/include \
    -Iinclude \
    -L/usr/local/systemc/lib-linux64 -lsystemc -lm
	./main

clean:
	rm -f main
