#include "image_ppm.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

int flou_fond(int y, int x, OCTET *ImgIn,OCTET *ImgBinary,OCTET *ImgOut, int nH, int nW, int niveauDeFloutage, int fond);

int main(int argc, char **argv){
    char cNomImgLue[250], cNomImgEcrite[250], cNomImgBinary[250];
    int nH, nW, nTaille, nivDeFloutage = 1;
    int fond=0;
    if (argc < 5)
    {
      printf("Usage: ImageIn.ppm ImageBinary.pgm ImageOut.ppm niveauDeFloutage invert(optional)\n");
      exit (1) ;
    }
    sscanf (argv[1],"%s",cNomImgLue);
    sscanf (argv[2],"%s",cNomImgBinary);
    sscanf (argv[3],"%s",cNomImgEcrite);
    sscanf (argv[4],"%d",&nivDeFloutage);
    if(argc>5){
        fond=255;
    }
    cout << "niveau De Floutage : "<< nivDeFloutage << endl;
    cout << "fond : "<< fond << endl;

    OCTET *ImgIn, *ImgOut, *ImgBinary;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille *3);
    allocation_tableau(ImgBinary, OCTET, nTaille);
    lire_image_ppm(cNomImgLue, ImgIn, nTaille);
    lire_image_pgm(cNomImgBinary, ImgBinary, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille * 3);
    
    for (int i=0; i < nH; i++) {
      for (int j=0; j < nW; j++) {
        flou_fond(i,j, ImgIn, ImgBinary, ImgOut, nH, nW, nivDeFloutage, fond);
      }
    }
    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    free(ImgOut);

    return 0;
}

int flou_fond(int y, int x, OCTET *ImgIn,OCTET *ImgBinary,OCTET *ImgOut, int nH, int nW, int niveauDeFloutage, int fond){
    int pixelIndex_ppm=3*y*nW + 3*x;
    int pixelIndex_pgm=y*nW + x;
    if(ImgBinary[pixelIndex_pgm]!=fond){
        ImgOut[pixelIndex_ppm]=ImgIn[pixelIndex_ppm];
        ImgOut[pixelIndex_ppm+1]=ImgIn[pixelIndex_ppm+1];
        ImgOut[pixelIndex_ppm+2]=ImgIn[pixelIndex_ppm+2];
        return 0;
    }
    int currentX, currentY;
    int cumulR=0,cumulV=0, cumulB=0;
    int nbVoisins =0;
    for(int i=0; i <= niveauDeFloutage*2 ; i++)
    {
        currentY= -niveauDeFloutage + i +y;
        if(currentY<0 || currentY>=nH){
            continue;
        }
        for(int j = 0; j <= niveauDeFloutage*2; j++)
        {  
            currentX= -niveauDeFloutage + j +x;
            if(currentX<0 || currentX>=nW){
                continue;
            }
            int currentPixelIndex =3*currentY*nW +3*currentX;
            nbVoisins+=1;
            cumulR+=ImgIn[currentPixelIndex];
            cumulV+=ImgIn[currentPixelIndex+1];
            cumulB+=ImgIn[currentPixelIndex+2];
        }
    }    
    ImgOut[pixelIndex_ppm]=cumulR/nbVoisins;
    ImgOut[pixelIndex_ppm+1]=cumulV/nbVoisins;
    ImgOut[pixelIndex_ppm+2]=cumulB/nbVoisins;
    return 0;
}