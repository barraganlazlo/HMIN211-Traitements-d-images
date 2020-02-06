#include <stdio.h>
#include <iostream>
#include "image_ppm.h"
#define M 255

using namespace std;
int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, a,b;

  if (argc != 5)
  {
    printf("Usage: ImageIn.pgm ImageOut.pgm a b \n");
    exit (1) ;
  }

  sscanf (argv[1],"%s",cNomImgLue);
  sscanf (argv[2],"%s",cNomImgEcrite);
  sscanf (argv[3],"%d",&a);
  sscanf (argv[4],"%d",&b);

  OCTET *ImgIn, *ImgOut;

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
  for (int i=0; i < nH; i++)
  {
    for (int j=0; j < nW; j++)
    {
      int p=i*nW +j;
      ImgOut[p] = M *((ImgIn[p] - a )/(b - a));
    }
  }
  ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
  free(ImgIn);
  return 1;
}
