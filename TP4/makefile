all : convert_gray flou flou_fond blur blur_pointed ROC ROC2

convert_gray :
	g++ -Wall -I ../librairie -o bin/convert_gray src/convert_gray.cpp
flou :
	g++ -Wall -I ../librairie -o bin/flou src/flou.cpp
flou_fond :
	g++ -Wall -I ../librairie -o bin/flou_fond src/flou_fond.cpp
blur :
	g++ -Wall -I ../librairie -o bin/blur src/blur.cpp
blur_pointed :
	g++ -Wall -I ../librairie -o bin/blur_pointed src/blur_pointed.cpp
ROC :
	g++ -Wall -I ../librairie -o bin/ROC src/ROC.cpp
ROC2 :
	g++ -Wall -I ../librairie -o bin/ROC2 src/ROC2.cpp
clean :
	rm -rf obj/*.o
mrproper :
	rm -rf bin/*
