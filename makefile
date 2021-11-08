platformer_compile:
	g++ -c main.cpp game.cpp player.cpp level.cpp particles.cpp gem.cpp doughnut_bar.cpp -g
	g++ main.o game.o player.o level.o particles.o gem.o doughnut_bar.o -o main -lsfml-graphics -lsfml-window -lsfml-system -g