#include <stdio.h>
#include <iostream>
#include "image_ppm.h"

int get4voisins(OCTET * ImgIn , int nH, int nW, int i, int j, int *voisin);
void copyValues(OCTET * array1, OCTET * array2, int taille);

using namespace std;
int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nbErosion;

  if (argc < 4)
  {
    printf("Usage: ImageIn.pgm ImageDil.pgm nbErosion ... \n");
    exit (1) ;
  }

  sscanf (argv[1],"%s",cNomImgLue);
  sscanf (argv[2],"%s",cNomImgEcrite);
  sscanf (argv[3],"%d",&nbErosion);
  nbErosion = nbErosion <= 0 ? 1 : nbErosion;

  OCTET *ImgIn, *ImgOut, *ImgFinal;

  //Lecture taille image
  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  //Calcul total taille image
  nTaille = nH * nW;

  //Allocation image sur ImgIn
  allocation_tableau(ImgIn, OCTET, nTaille);
  //Ecriture sur ImgIn avec cNomImgLue
  lire_image_pgm(cNomImgLue, ImgIn, nTaille);
  //Allocation image sur ImgOut
  allocation_tableau(ImgOut, OCTET, nTaille);
  allocation_tableau(ImgFinal, OCTET, nTaille);

  int voisin[4];
  int nbv = 0;

  for (int erosion = 0; erosion < nbErosion; erosion++) {
    if(erosion > 0){
      copyValues(ImgOut, ImgIn, nTaille);
    }

    //Erosion
    for (int i=0; i < nH; i++) {
      for (int j=0; j < nW; j++) {
        int pixelPos = i*nW+j;
        nbv = get4voisins(ImgIn, nH, nW, i, j, voisin);
        bool found = false;
        for (int v = 0; v < nbv; v++) {
          if(voisin[v] == 0){
            found = true;
            break;
          }
        }
        ImgOut[pixelPos] = found ? 0 : ImgIn[pixelPos];
      }
    }

  }

  //Difference
  for (int i=0; i < nH; i++) {
    for (int j=0; j < nW; j++) {
      int pixelPos = i*nW+j;
      /*
      Si les deux pixels (de l’image seuillée et de l’image dilatée) appartiennent au fond, alors le pixel correspondant de l’image de sortie appartiendra au fond (255).
      Si les deux pixels (de l’image seuillée et de l’image dilatée) appartiennent à l’objet, alors le pixel correspondant de l’image de sortie appartiendra au fond (255).
      Si le pixel de l’image dilatée appartient à l’objet et que le pixel de l’image seuillée appartient au fond, alors le pixel correspondant de l’image de sortie appartiendra au contour (0)
      */
      if( ImgOut[pixelPos] == ImgIn[pixelPos]) ImgFinal[pixelPos] = 255;
      else  ImgFinal[pixelPos] = 0;
    }
  }

  ecrire_image_pgm(cNomImgEcrite, ImgFinal,  nH, nW);
  free(ImgIn);
  return 1;
}

int get4voisins(OCTET * ImgIn , int nH, int nW, int i, int j, int *voisin){
    int nbv = 0;
    if(i>0){
      voisin[0]=ImgIn[(i-1)*nW +j];
      nbv+=1;
    }
    if(j>0){
      voisin[1]=ImgIn[i * nW +(j-1)];
      nbv+=1;
    }
    if(j<nW-1){
      voisin[2]=ImgIn[i * nW +(j+1)];
      nbv+=1;
    }
    if(i<nH-1){
      voisin[3]=ImgIn[(i+1)*nW +j];
      nbv+=1;
    }
    return nbv;
}

void copyValues(OCTET * array1, OCTET * array2, int taille){
  for (int i = 0; i < taille; i++) {
    array2[i] = array1[i];
  }
}
