all: brainfuck

debug: brainfuck-debug

brainfuck: Cell.o Executor.o Parser.o Brainfuck.o
	g++ Cell.o Executor.o Parser.o Brainfuck.o -o Brainfuck -std=c++17

Brainfuck.o: Brainfuck.cpp
	g++ Brainfuck.cpp -c -o Brainfuck.o -std=c++17

Executor.o: Executor.cpp Executor.h
	g++ Executor.cpp -c -o Executor.o -std=c++17

Parser.o: Parser.cpp Parser.h
	g++ Parser.cpp -c -o Parser.o -std=c++17

Cell.o: Cell.cpp Cell.h
	g++ Cell.cpp -c -o Cell.o -std=c++17

brainfuck-debug: Cell-d.o Executor-d.o Parser-d.o Brainfuck-d.o
	g++ Cell-d.o Executor-d.o Parser-d.o Brainfuck-d.o -O0 -o DBrainfuck -std=c++17

Brainfuck-d.o: Brainfuck.cpp
	g++ Brainfuck.cpp -c -ggdb3 -O0 -o Brainfuck-d.o -std=c++17

Executor-d.o: Executor.cpp Executor.h
	g++ Executor.cpp -c -ggdb3 -O0 -o Executor-d.o -std=c++17

Parser-d.o: Parser.cpp Parser.h
	g++ Parser.cpp -c -ggdb3 -O0 -o Parser-d.o -std=c++17

Cell-d.o: Cell.cpp Cell.h
	g++ Cell.cpp -c -ggdb3 -O0 -o Cell-d.o -std=c++17

clean:
	rm *.o
