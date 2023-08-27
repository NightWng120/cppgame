game: main.cpp
	g++ -std=c++17 main.cpp Game.cpp -o prog -lSDL2 `sdl2-config --cflags --libs` -lSDL2_image -g

run: prog
	./prog

prog: main.cpp
	rm prog
	g++ -std=c++17 main.cpp Game.cpp -o prog -lSDL2 `sdl2-config --cflags --libs` -lSDL2_image -g

debug:
	gdb prog

clean:
	rm prog


