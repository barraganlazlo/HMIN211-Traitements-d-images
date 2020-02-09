#include <stdio.h>
#include <iostream>
#include <fstream>
#include "image_ppm.h"

using namespace std;

int* diagram(OCTET *ImgIn,int nH,int nW);
OCTET Ta(int L, int position, float *fa, OCTET *ImgRef);
OCTET InverseTa(int L, int position, int *fa, OCTET *ImgRef);

int main(int argc, char* argv[])
{
    //cNomImgLue -> Reference
    //cNomCompare -> Compare
    char cNomImgLue[250], cNomCompare[250] , cNomImgEcrite[250];
    int nH, nW, nTaille;

    if (argc < 4) {
        printf("Usage: ImageSource.pgm ImageCompare.pgm ImageOut.pgm ... \n");
        exit (1) ;
    }

    //char BufferOutDdp[250];
    //char BufferOutFa[250];

    sscanf (argv[1],"%s",cNomImgLue);
    sscanf (argv[2],"%s",cNomCompare);
    sscanf (argv[3],"%s",cNomImgEcrite);

    OCTET *ImgRef, *ImgTest, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    lire_nb_lignes_colonnes_image_pgm(cNomCompare, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgRef, OCTET, nTaille);
    allocation_tableau(ImgTest, OCTET, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);

    lire_image_pgm(cNomImgLue, ImgRef, nTaille);
    lire_image_pgm(cNomCompare, ImgTest, nTaille);

    // Soit N le nbre de pixels ;
    // Soit f[256] la fonction de transform. des luminances ;
    // Soit l’histogramme de référence: histoCumuleRef[256] ;
    // évaluer l’histogramme cumulé : histoCumule[256] ;
    int L = 256; //Layers

    //Get the datagram of the image
    int* diagRef = diagram(ImgRef, nH, nW);
    int* diagTest = diagram(ImgTest, nH, nW);
    //Ref functions
    float* ddp_ref = (float*) malloc(L * sizeof(float));
    float* histoCumuleRef = (float*) malloc(L * sizeof(float));
    //Test functions
    float* ddp_test = (float*) malloc(L * sizeof(float));
    float* histoCumule = (float*) malloc(L * sizeof(float));

    for(int i = 0; i < L; i++){
        ddp_ref[i] = (float)diagRef[i] / (float)nTaille;
        histoCumuleRef[i] = i == 0 ? ddp_ref[i] : ddp_ref[i] + histoCumuleRef[i - 1];

        ddp_test[i] = (float)diagTest[i] / (float)nTaille;
        histoCumule[i] = i == 0 ? ddp_test[i] : ddp_test[i] + histoCumule[i - 1];
    }

    int f[L];
    int y = 0 ;
    for(int x = 0; x < L; x++){
        f[x] = y;
        //Protection While
        while(histoCumule[x] > histoCumuleRef[y] && y < 256 && x < 256){
            y++;
        }
    }

    //Apply Dynamic expension
    int position;
    for (int i=0; i < nH; i++) {
        for (int j=0; j < nW; j++) {
            position = i*nW + j;
            ImgOut[position] = Ta(L, position, histoCumule, ImgTest);
            ImgOut[position] = InverseTa(L, position, f, ImgOut);
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgRef);
    free(ImgTest);
    free(ImgOut);
    
    free(diagRef);
    free(diagTest);
    free(ddp_ref);
    free(histoCumuleRef);
    free(ddp_test);
    free(histoCumule);
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

OCTET Ta(int L, int position, float *fa, OCTET *ImgRef){
    return (L - 1) * fa[ImgRef[position]];
}

OCTET InverseTa(int L, int position, int *fa, OCTET *ImgRef){
    return (L - 1) * fa[ImgRef[position]];
}
