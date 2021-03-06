#include <stdio.h>
#include <iostream>
#include <fstream>
#include "image_ppm.h"

using namespace std;

int* diagram(OCTET *ImgIn,int nH,int nW);

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;

  if (argc < 5)
  {
    printf("Usage: ImageIn.pgm ImageOut.pgm ddp fa ... \n");
    exit (1) ;
  }

  char BufferOutDdp[250];
  char BufferOutFa[250];

  sscanf (argv[1],"%s",cNomImgLue);
  sscanf (argv[2],"%s",cNomImgEcrite);
  sscanf (argv[3],"%s",BufferOutDdp);
  sscanf (argv[4],"%s",BufferOutFa);

  OCTET *ImgIn, *ImgOut;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nTaille);
  allocation_tableau(ImgOut, OCTET, nTaille);

  //Get the datagram of the image
  int L = 256; //Layers
  int* diag = diagram(ImgIn, nH, nW);
  float* ddp = (float*) malloc(L * sizeof(float));
  float* fa = (float*) malloc(L * sizeof(float));

  ofstream fileOutDdp(BufferOutDdp);
  ofstream fileOutFa(BufferOutFa);

  for(int i = 0; i < L; i++){
    ddp[i] = (float)diag[i] / (float)nTaille;
      fileOutDdp<<i <<" "<< ddp[i] <<endl;
    fa[i] = i == 0 ? ddp[i] : ddp[i] + fa[i - 1];
      fileOutFa<<i <<" "<< fa[i] <<endl;
  }

  //Apply Dynamic expension
  int position;
  for (int i=0; i < nH; i++) {
    for (int j=0; j < nW; j++) {
      position = i*nW + j;
      ImgOut[position] = (L - 1) * fa[ImgIn[position]];
    }
  }

  ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
  free(ImgIn);
  free(ImgOut);
  free(diag);
  return 0;
}

int* diagram(OCTET *ImgIn,int nH,int nW){
  int* occ = (int*) malloc(256 * sizeof(int));
  //Init with 0
  for(int i=0; i<256; i++){ occ[i]=0; }
  for (int i=0; i < nH; i++) {
      for (int j=0; j < nW; j++) {
          occ[ImgIn[i*nW+j]]+=1;
      }
  }
  return occ;
}
