all : expansion_dynamique expansion_d3 extrema

expansion_dynamique:
	g++ -Wall -I ../librairie -o bin/expansion_dynamique src/expansion_dynamique.cpp
expansion_d3:
	g++ -Wall -I ../librairie -o bin/expansion_d3 src/expansion_d3.cpp
extrema:
	g++ -Wall -I ../librairie -o bin/extrema src/extrema.cpp
clean :
	rm -rf obj/*.o
mrproper :
	rm -rf bin/*
