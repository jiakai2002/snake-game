all: snake

snake: snake.cpp
	g++ snake.cpp -lncurses -o snake
