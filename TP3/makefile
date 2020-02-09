all : expansion_dynamique expansion_d3 extrema_histo egalisation

expansion_dynamique:
	g++ -Wall -I ../librairie -o bin/expansion_dynamique src/expansion_dynamique.cpp
expansion_d3:
	g++ -Wall -I ../librairie -o bin/expansion_d3 src/expansion_d3.cpp
extrema_histo:
	g++ -Wall -I ../librairie -o bin/extrema_histo src/extrema_histo.cpp
egalisation:
	g++ -Wall -I ../librairie -o bin/egalisation src/egalisation.cpp
clean :
	rm -rf obj/*.o
mrproper :
	rm -rf bin/*
