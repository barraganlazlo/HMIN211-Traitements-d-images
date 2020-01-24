all : test_grey seuil profilDat histogramme histogramme_couleur seuil_ppm

test_grey: 
	g++ -Wall -I ../librairie -o bin/test_grey src/test_grey.cpp
seuil:
	g++ -Wall -I ../librairie -o bin/seuil src/seuil.cpp
profilDat :
	g++ -Wall -I ../librairie -o bin/profilDat src/profilDat.cpp
histogramme :
	g++ -Wall -I ../librairie -o bin/histogramme src/histogramme.cpp
histogramme_couleur :
	g++ -Wall -I ../librairie -o bin/histogramme_couleur src/histogramme_couleur.cpp
seuil_ppm :
	g++ -Wall -I ../librairie -o bin/seuil_ppm src/seuil_ppm.cpp

clean : 
	rm -rf obj/*.o
mrproper :
	rm -rf bin/*
