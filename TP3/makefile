all : seuil seuil_ppm erosion

seuil:
	g++ -Wall -I ../librairie -o bin/seuil src/seuil.cpp
seuil_ppm :
	g++ -Wall -I ../librairie -o bin/seuil_ppm src/seuil_ppm.cpp
erosion :
	g++ -Wall -I ../librairie -o bin/erosion src/erosion.cpp
difference :
	g++ -Wall -I ../librairie -o bin/difference src/difference.cpp
clean :
	rm -rf obj/*.o
mrproper :
	rm -rf bin/*
