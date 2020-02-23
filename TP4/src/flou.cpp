#include "image_ppm.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

int flou(int y, int x, OCTET *ImgIn,OCTET *ImgOut, int nH, int nW, int niveauDeFloutage);

int main(int argc, char **argv){
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, nivDeFloutage = 1;

    if (argc < 4)
    {
      printf("Usage: ImageIn.ppm ImageOut.ppm niveauDeFloutage\n");
      exit (1) ;
    }
    sscanf (argv[1],"%s",cNomImgLue);
    sscanf (argv[2],"%s",cNomImgEcrite);
    sscanf (argv[3],"%d",&nivDeFloutage);

    cout << nivDeFloutage << endl;

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille *3);
    lire_image_ppm(cNomImgLue, ImgIn, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille * 3);
    
    for (int i=0; i < nH; i++) {
      for (int j=0; j < nW; j++) {
        flou(i,j, ImgIn, ImgOut, nH, nW, nivDeFloutage);
      }
    }

    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    free(ImgOut);

    return 0;
}

int flou(int y, int x, OCTET *ImgIn,OCTET *ImgOut, int nH, int nW, int niveauDeFloutage){
    int pixelIndex=3*y*nW + 3*x;
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
    ImgOut[pixelIndex]=cumulR/nbVoisins;
    ImgOut[pixelIndex+1]=cumulV/nbVoisins;
    ImgOut[pixelIndex+2]=cumulB/nbVoisins;
    return 0;
}