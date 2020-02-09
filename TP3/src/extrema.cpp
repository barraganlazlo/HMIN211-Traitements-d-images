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

struct RGB histogram(OCTET *ImgIn, int nH, int nW);
int linearTransform(int n, int alpha, int beta);

int main(int argc, char **argv){
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;
    float tempP;
    float P;
    if (argc < 4)
    {
      printf("Usage: ImageIn.ppm ImageOut.ppm P\n");
      exit (1) ;
    }
    sscanf (argv[1],"%s",cNomImgLue);
    sscanf (argv[2],"%s",cNomImgEcrite);
    sscanf (argv[3],"%f",&tempP);

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille *3);
    lire_image_ppm(cNomImgLue, ImgIn, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille *3);

    //Get histogram
    struct RGB hist = histogram(ImgIn, nH, nW);
    P=tempP/100.0f;
    cout << " P : "<<P <<endl;
    //Get alpha & Beta
    int alpha_r = -1, alpha_g = -1, alpha_b = -1;
    int beta_r = -1, beta_g = -1, beta_b = -1;
    float rp,gp,bp;
    rp=0;
    gp=0;
    bp=0;
    for (int i=0; i < 255; i++) {
      if(alpha_r<0 && rp>=P){
        alpha_r=i;
      }
      if(alpha_g<0 && gp>=P){
        alpha_g=i;
      }
      if(alpha_b<0 && bp>=P){
        alpha_b=i;
      }
      rp+=hist.r[i] / (float)nTaille;
      gp+=hist.g[i] / (float)nTaille;
      bp+=hist.b[i] / (float)nTaille;
      if(beta_r<0 && rp>=1-P){
        if(i==0){
          beta_r=0;
        }else{
          beta_r=i-1;
        }
      }
      if(beta_g<0 && gp>=1-P){
        if(i==0){
          beta_g=0;
        }else{
          beta_g=i-1;
        }
      }
      if(beta_b<0 && bp>=1-P){
        if(i==0){
          beta_b=0;
        }else{
          beta_b=i-1;
        }
      }
    }

    cout << "r : " << alpha_r << " / " << beta_r << endl;
    cout << "g : " << alpha_g << " / " << beta_g << endl;
    cout << "b : " << alpha_b << " / " << beta_b << endl;

    //Apply Dynamic expension
    int position;
    for (int i=0; i < nH; i++) {
      for (int j=0; j < nW; j++) {
        position = i*nW*3+j*3;
        if(ImgIn[]){

        }
        ImgOut[position] = linearTransform(ImgIn[position], alpha_r, beta_r);
        ImgOut[position + 1] = linearTransform(ImgIn[position + 1], alpha_g, beta_g);
        ImgOut[position + 2] = linearTransform(ImgIn[position + 2], alpha_b, beta_b);
      }
    }

    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);

    return 0;
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
