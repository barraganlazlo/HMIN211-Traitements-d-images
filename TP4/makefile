all : convert_gray blur blur_pointed ROC

convert_gray :
	g++ -Wall -I ../librairie -o bin/convert_gray src/convert_gray.cpp
blur :
	g++ -Wall -I ../librairie -o bin/blur src/blur.cpp
blur_pointed :
	g++ -Wall -I ../librairie -o bin/blur_pointed src/blur_pointed.cpp
ROC :
	g++ -Wall -I ../librairie -o bin/ROC src/ROC.cpp

clean :
	rm -rf obj/*.o
mrproper :
	rm -rf bin/*
