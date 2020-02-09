#include "image_ppm.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

struct RGB{
  int* r;
  int* g;
  int* b;
};

void extrema(OCTET *ImgOut, int nH, int nW, int alpha_r, int beta_r, int alpha_g, int beta_g, int alpha_b, int beta_b);
struct RGB histogram(OCTET *ImgIn, int nH, int nW);
int linearTransform(int n, int alpha, int beta);

int main(int argc, char **argv){
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;

    if (argc < 3)
    {
      printf("Usage: ImageIn.ppm ImageOut.ppm \n");
      exit (1) ;
    }
    sscanf (argv[1],"%s",cNomImgLue);
    sscanf (argv[2],"%s",cNomImgEcrite);

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille *3);
    lire_image_ppm(cNomImgLue, ImgIn, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille *3);

    //Get histogram
    struct RGB histOriginal = histogram(ImgIn, nH, nW);

    int L = 256; //Layers
    float* ddp_r = (float*) malloc(L * sizeof(float));
    float* ddp_g = (float*) malloc(L * sizeof(float));
    float* ddp_b = (float*) malloc(L * sizeof(float));

    float* fa_r = (float*) malloc(L * sizeof(float));
    float* fa_g = (float*) malloc(L * sizeof(float));
    float* fa_b = (float*) malloc(L * sizeof(float));

    for(int i = 0; i < L; i++){
      ddp_r[i] = (float)histOriginal.r[i] / (float)nTaille;
      ddp_g[i] = (float)histOriginal.g[i] / (float)nTaille;
      ddp_b[i] = (float)histOriginal.b[i] / (float)nTaille;

      fa_r[i] = i == 0 ? ddp_r[i] : ddp_r[i] + fa_r[i - 1];
      fa_g[i] = i == 0 ? ddp_g[i] : ddp_g[i] + fa_g[i - 1];
      fa_b[i] = i == 0 ? ddp_b[i] : ddp_b[i] + fa_b[i - 1];
    }

    //struct RGB hist = histogram(ImgIn, nH, nW);

    //Get alpha & Beta
    int alpha_r = -1, alpha_g = -1, alpha_b = -1;
    int beta_r = -1, beta_g = -1, beta_b = -1;

    for (int i=0; i < 255; i++) {
      if(alpha_r == -1 && fa_r[i] >= 0.01) alpha_r = i;
      if(alpha_g == -1 && fa_g[i] >= 0.01) alpha_g = i;
      if(alpha_b == -1 && fa_b[i] >= 0.01) alpha_b = i;

      if(beta_r == -1 && fa_r[i] >= 0.99) beta_r = i;
      if(beta_g == -1 && fa_g[i] >= 0.99) beta_g = i;
      if(beta_b == -1 && fa_b[i] >= 0.99) beta_b = i;
    }

    cout << "r : " << alpha_r << " / " << beta_r << endl;
    cout << "g : " << alpha_g << " / " << beta_g << endl;
    cout << "b : " << alpha_b << " / " << beta_b << endl;
    extrema(ImgIn, nH, nW, alpha_r, beta_r, alpha_g, beta_g, alpha_b, beta_b); //SetExtrema

    //Apply Dynamic expension
    int position;
    for (int i=0; i < nH; i++) {
      for (int j=0; j < nW; j++) {
        position = i*nW*3+j*3;
        ImgOut[position] = linearTransform(ImgIn[position], alpha_r, beta_r);
        ImgOut[position + 1] = linearTransform(ImgIn[position + 1], alpha_g, beta_g);
        ImgOut[position + 2] = linearTransform(ImgIn[position + 2], alpha_b, beta_b);
      }
    }

    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);

    return 0;
}

void extrema(OCTET *ImgOut, int nH, int nW, int alpha_r, int beta_r, int alpha_g, int beta_g, int alpha_b, int beta_b){
  for (int i=0; i < nH; i++) {
      for (int j=0; j < nW; j++) {
          int pos = i*nW*3+j*3;
          ImgOut[pos] = ImgOut[pos] > beta_r ? beta_r : ImgOut[pos] < alpha_r ? alpha_r : ImgOut[pos];
          ImgOut[pos +1] = ImgOut[pos +1] > beta_g ? beta_g : ImgOut[pos +1] < alpha_g ? alpha_g : ImgOut[pos +1];
          ImgOut[pos +2] = ImgOut[pos +2] > beta_b ? beta_b : ImgOut[pos +2] < alpha_b ? alpha_b : ImgOut[pos +2];
      }
  }
}

struct RGB histogram(OCTET *ImgIn, int nH, int nW){
  struct RGB occ;
  occ.r = (int*) malloc(256 * sizeof(int));
  occ.g = (int*) malloc(256 * sizeof(int));
  occ.b = (int*) malloc(256 * sizeof(int));
  for(int i=0; i<256; i++){
      occ.r[i]=0;
      occ.g[i]=0;
      occ.b[i]=0;
  }
  for (int i=0; i < nH; i++) {
      for (int j=0; j < nW; j++) {
          occ.r[ImgIn[i*nW*3+j*3]]+=1;
          occ.g[ImgIn[i*nW*3+j*3 +1]]+=1;
          occ.b[ImgIn[i*nW*3+j*3 +2]]+=1;
      }
  }

  return occ;
}

int linearTransform(int n, int alpha, int beta){
  return 255 * ((float)(n - alpha) / (float)(beta - alpha));
}
