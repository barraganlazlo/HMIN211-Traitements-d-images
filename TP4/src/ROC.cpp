#include <stdio.h>
#include <iostream>
#include "image_ppm.h"

using namespace std;
int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomVerite[250];
  int nH, nW, nTaille, seuil;

  if (argc < 4)
  {
    printf("Usage: ImageIn.pgm ImageVerite.pgm Seuil ... \n");
    exit (1) ;
  }

  sscanf (argv[1],"%s",cNomImgLue);
  sscanf (argv[2],"%s",cNomVerite);
  sscanf (argv[3],"%d",&seuil);

  OCTET *ImgIn, *ImgVerite;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  allocation_tableau(ImgIn, OCTET, nTaille);
  allocation_tableau(ImgVerite, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nTaille);
  lire_image_pgm(cNomVerite, ImgVerite, nTaille);

  int TP = 0;
  int FP = 0;
  int TN = 0;
  int FN = 0;

  for (int i=0; i < nH; i++) {
    for (int j=0; j < nW; j++) {
      int pos = i*nW+j;
      ImgIn[pos]= ImgIn[pos] > seuil ? 255 : 0;
      if(ImgVerite[pos] == ImgIn[pos]){
        if(ImgVerite[pos] == 255) TP++;
        else TN++;
      }else{
        if(ImgVerite[pos] == 255) FP++;
        else FN++;
      }

    }
  }

  cout << "TP = " << TP << endl;
  cout << "FP = " << FP << endl;
  cout << "TN = " << TN << endl;
  cout << "FN = " << FN << endl;

  cout << endl;
  cout << "Sensibilite : " << ((float)TP / (float)(TP + FN)) << endl;
  cout << "Specifite : " << 1.0 - ((float)TN / (float)(TN + FP)) << endl;

  // ecrire_image_pgm(cNomImgEcrite, ImgVerite,  nH, nW);
  free(ImgIn);
  return 1;
}
