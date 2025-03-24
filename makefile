

run:
	g++ src/main.cpp src/instructions.cpp src/functions.cpp -o main -std=c++17 -I/usr/local/systemc/include -L/usr/local/systemc/lib -lsystemc -lm
	./main
clean:
	rm -f main 
