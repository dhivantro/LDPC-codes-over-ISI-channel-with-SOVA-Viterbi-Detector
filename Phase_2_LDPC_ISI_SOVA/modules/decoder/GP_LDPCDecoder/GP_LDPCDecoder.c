// Software Recording Channel (SWRC) platform in C.
// Name      : GP_LDPCDecoder
// Type      : module.
// Path      : modules/decoder/GP_LDPCDecoder
// Dependency: 
// Version   : 1.0
// Author(s) : Kheong Sann Chan.
// Date      : Mon Mar 28 17:14:35 2022
// Comment   : The first-trial (7,4) Hamming encoder for the group project 
//             team 

#include "GP_LDPCDecoder.h"
// Print the double **L struct
void printLGP_LDPCDecoderStruct (GP_LDPCDecoderStruct *GP_LDPCDecoder) {
}

// Free the memory allocated to double **L
void freeLGP_LDPCDecoderStruct (GP_LDPCDecoderStruct *GP_LDPCDecoder) {
}

// Allocate memory for double **L
void allocateLGP_LDPCDecoderStruct (GP_LDPCDecoderStruct *GP_LDPCDecoder) {
}

// Print the int **H struct
void printHGP_LDPCDecoderStruct (GP_LDPCDecoderStruct *GP_LDPCDecoder) {
}

// Free the memory allocated to int **H
void freeHGP_LDPCDecoderStruct (GP_LDPCDecoderStruct *GP_LDPCDecoder) {
}

// Allocate memory for int **H
void allocateHGP_LDPCDecoderStruct (GP_LDPCDecoderStruct *GP_LDPCDecoder) {
}

// Initialize the fields in the module structure
// Set pointers to NULL (so they can be called with realloc)
// Initialize the parameters to sane start-up values.
void initGP_LDPCDecoderStruct (GP_LDPCDecoderStruct *GP_LDPCDecoder) {
// Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
  GP_LDPCDecoder->H                   = NULL;
  GP_LDPCDecoder->L                   = NULL;
  GP_LDPCDecoder->N                   = 0;
  GP_LDPCDecoder->M                   = 0;
  GP_LDPCDecoder->K                   = 0;
  GP_LDPCDecoder->R                   = 0.0;
// Fields automatically included in every module that request $args{i}
  GP_LDPCDecoder->trainFlag           = 0;
  GP_LDPCDecoder->N_train             = 0;
  GP_LDPCDecoder->i_train             = 0;
  GP_LDPCDecoder->numberOfMult        = 0;
  GP_LDPCDecoder->aveNoOfMultPerFrame = 0.0;
  GP_LDPCDecoder->numberOfAdd         = 0;
  GP_LDPCDecoder->aveNoOfAddPerFrame  = 0.0;
  GP_LDPCDecoder->numberOfComp        = 0;
  GP_LDPCDecoder->aveNoOfCompPerFrame = 0.0;
  GP_LDPCDecoder->simTime             = 0.0;
  GP_LDPCDecoder->aveSimTimePerFrame  = 0.0;
  GP_LDPCDecoder->numberOfCalls       = 0;
}

// Frees up all the memory in the structure
void freeGP_LDPCDecoderStruct (GP_LDPCDecoderStruct *GP_LDPCDecoder) {
  if (GP_LDPCDecoder==NULL) {printf("GP_LDPCDecoder=NULL in function freeGP_LDPCDecoderStruct not free'ing\n");return;}
  int i;
  //Free int **H
  freeHGP_LDPCDecoderStruct(GP_LDPCDecoder);
  //Free double **L
  freeLGP_LDPCDecoderStruct(GP_LDPCDecoder);
  GP_LDPCDecoder->N             =0;
  GP_LDPCDecoder->M             =0;
  GP_LDPCDecoder->K             =0;
  GP_LDPCDecoder->R             =0.0;
  GP_LDPCDecoder->trainFlag     =0;
  GP_LDPCDecoder->N_train       =0;
  GP_LDPCDecoder->i_train       =0;
  GP_LDPCDecoder->numberOfMult  =0;
  GP_LDPCDecoder->aveNoOfMultPerFrame=0.0;
  GP_LDPCDecoder->numberOfAdd   =0;
  GP_LDPCDecoder->aveNoOfAddPerFrame=0.0;
  GP_LDPCDecoder->numberOfComp  =0;
  GP_LDPCDecoder->aveNoOfCompPerFrame=0.0;
  GP_LDPCDecoder->simTime       =0.0;
  GP_LDPCDecoder->aveSimTimePerFrame=0.0;
  GP_LDPCDecoder->numberOfCalls =0;
  //free(GP_LDPCDecoder);GP_LDPCDecoder=NULL;
}

// Prints the contents of the structure.
// Used for determining the status of the simulation
// as well as for debugging.
void printGP_LDPCDecoderStruct (GP_LDPCDecoderStruct *GP_LDPCDecoder, char *name, int index, int pre) {
  int i,j;
  char *preString,*name2;
  //if (GP_LDPCDecoder==NULL) {printf("%s%s=NULL\n",preString,name);return;}
  preString=(char*)calloc((pre+1),sizeof(char));
  for (i=0;i<pre;i++) preString[i]=' '; preString[i]='\0';
  //printf("%s[--%d:%s--------\n",preString,index,name);
// Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
    printHGP_LDPCDecoderStruct(GP_LDPCDecoder);                                                        // Print int **H
    printLGP_LDPCDecoderStruct(GP_LDPCDecoder);                                                        // Print double **L
    // printf("%s  int                  %s->N=%d\n",preString,name,GP_LDPCDecoder->N);                    // Print int N
    // printf("%s  int                  %s->M=%d\n",preString,name,GP_LDPCDecoder->M);                    // Print int M
    // printf("%s  int                  %s->K=%d\n",preString,name,GP_LDPCDecoder->K);                    // Print int K
    // printf("%s  double               %s->R=%lf\n",preString,name,GP_LDPCDecoder->R); 
    // Print double R
// Fields automatically included in every module that request $args{i}
    // printf("%s  uint8_t              %s->trainFlag=%"SCNu8"\n",preString,name,GP_LDPCDecoder->trainFlag); // Print uint8_t trainFlag
    // printf("%s  long int             %s->N_train=%ld\n",preString,name,GP_LDPCDecoder->N_train);       // Print long int N_train
    // printf("%s  long int             %s->i_train=%ld\n",preString,name,GP_LDPCDecoder->i_train);       // Print long int i_train
  //   printf("%s  long unsigned int    %s->numberOfMult=%lu\n",preString,name,GP_LDPCDecoder->numberOfMult); // Print long unsigned int numberOfMult
  //   printf("%s  double               %s->aveNoOfMultPerFrame=%lf\n",preString,name,GP_LDPCDecoder->aveNoOfMultPerFrame); // Print double aveNoOfMultPerFrame
  //   printf("%s  long unsigned int    %s->numberOfAdd=%lu\n",preString,name,GP_LDPCDecoder->numberOfAdd); // Print long unsigned int numberOfAdd
  //   printf("%s  double               %s->aveNoOfAddPerFrame=%lf\n",preString,name,GP_LDPCDecoder->aveNoOfAddPerFrame); // Print double aveNoOfAddPerFrame
  //   printf("%s  long unsigned int    %s->numberOfComp=%lu\n",preString,name,GP_LDPCDecoder->numberOfComp); // Print long unsigned int numberOfComp
  //   printf("%s  double               %s->aveNoOfCompPerFrame=%lf\n",preString,name,GP_LDPCDecoder->aveNoOfCompPerFrame); // Print double aveNoOfCompPerFrame
  //   printf("%s  double               %s->simTime=%lf\n",preString,name,GP_LDPCDecoder->simTime);       // Print double simTime
  //   printf("%s  double               %s->aveSimTimePerFrame=%lf\n",preString,name,GP_LDPCDecoder->aveSimTimePerFrame); // Print double aveSimTimePerFrame
  //   printf("%s  long unsigned int    %s->numberOfCalls=%lu\n",preString,name,GP_LDPCDecoder->numberOfCalls); // Print long unsigned int numberOfCalls
  // printf("%s---%d:%s-------]\n",preString,index,name);
  free(preString);
}

// Store random values into the fields of GP_LDPCDecoderStruct.
// For testing that saving to .cfg file works.
// User should help to write appropriate random-generating values
// to be stored in the appropriate fields.
void randomizeGP_LDPCDecoderStruct (GP_LDPCDecoderStruct *GP_LDPCDecoder) {
  int idum=1;SWRC_randomize(&idum);
  //GP_LDPCDecoder->H=rand();
  //GP_LDPCDecoder->L=ran2(&idum);
  //GP_LDPCDecoder->N=rand();
  //GP_LDPCDecoder->M=rand();
  //GP_LDPCDecoder->K=rand();
  //GP_LDPCDecoder->R=ran2(&idum);
}

// Initialize an array of GP_LDPCDecoderStruct's to sane starting values
void initArrayGP_LDPCDecoderStruct (arrayGP_LDPCDecoderStruct *GP_LDPCDecoder) {
  GP_LDPCDecoder->N_x=0;
  GP_LDPCDecoder->x=NULL;
}

// Allocate memory for an array of N GP_LDPCDecoderStruct's
void allocateArrayGP_LDPCDecoderStruct (arrayGP_LDPCDecoderStruct *GP_LDPCDecoder,int N) {
  int i;
  GP_LDPCDecoder->N_x=N;
  GP_LDPCDecoder->x = (GP_LDPCDecoderStruct*)realloc(GP_LDPCDecoder->x,N*sizeof(GP_LDPCDecoderStruct));
  for (i=0;i<GP_LDPCDecoder->N_x;i++) {
    initGP_LDPCDecoderStruct(&GP_LDPCDecoder->x[i]);
  }
}

// Free an array of GP_LDPCDecoderStruct's
void freeArrayGP_LDPCDecoderStruct (arrayGP_LDPCDecoderStruct *GP_LDPCDecoder) {
  // if (GP_LDPCDecoder==NULL) {printf("GP_LDPCDecoder=NULL in function freeArrayGP_LDPCDecoderStruct not free'ing\n");return;}
  int i;
  for (i=0;i<GP_LDPCDecoder->N_x;i++) {
    freeGP_LDPCDecoderStruct(&GP_LDPCDecoder->x[i]);
  } free(GP_LDPCDecoder->x);GP_LDPCDecoder->x=NULL;
}

// Fill the arrayGP_LDPCDecoderStruct with random values.
// The GP_LDPCDecoder->N_GP_LDPCDecoder parameter 
// must be set to the number of elements in the array.
// Array must be allocated before calling this function.
void randomizeArrayGP_LDPCDecoderStruct (arrayGP_LDPCDecoderStruct *GP_LDPCDecoder) {
  int i;
  for (i=0;i<GP_LDPCDecoder->N_x;i++) randomizeGP_LDPCDecoderStruct(&GP_LDPCDecoder->x[i]);
}

// Print arrayGP_LDPCDecoderStruct
void printArrayGP_LDPCDecoderStruct (arrayGP_LDPCDecoderStruct *GP_LDPCDecoder) {
  int i;
  for (i=0;i<GP_LDPCDecoder->N_x;i++) {
    printGP_LDPCDecoderStruct(&GP_LDPCDecoder->x[i],"GP_LDPCDecoder",i,0);
  }
}

// Initialize a double array of GP_LDPCDecoderStruct to sane startup values
void initDoubleArrayGP_LDPCDecoderStruct (doubleArrayGP_LDPCDecoderStruct *GP_LDPCDecoder) {
  GP_LDPCDecoder->N_N_x=0;
  GP_LDPCDecoder->N_x=NULL;
  GP_LDPCDecoder->x=NULL;
}

// Allocate memory for a rectangular double array of GP_LDPCDecoderStruct
void allocateDoubleArrayGP_LDPCDecoderStruct (doubleArrayGP_LDPCDecoderStruct *GP_LDPCDecoder, int N, int M) {
  int i,j;
  GP_LDPCDecoder->N_N_x=N;
  GP_LDPCDecoder->N_x=(long unsigned int*)realloc(GP_LDPCDecoder->N_x,N*sizeof(long unsigned int));
  for (i=0;i<GP_LDPCDecoder->N_N_x;i++) GP_LDPCDecoder->N_x[i]=M;
  GP_LDPCDecoder->x=(GP_LDPCDecoderStruct**)realloc(GP_LDPCDecoder->x,N*sizeof(GP_LDPCDecoderStruct*));
  for (i=0;i<GP_LDPCDecoder->N_N_x;i++) {
    GP_LDPCDecoder->x[i]=(GP_LDPCDecoderStruct*)calloc(M,sizeof(GP_LDPCDecoderStruct));
  for(j=0;j<GP_LDPCDecoder->N_x[i];j++) initGP_LDPCDecoderStruct(&GP_LDPCDecoder->x[i][j]);
  }
}

// Free a double array of GP_LDPCDecoderStruct's
void freeDoubleArrayGP_LDPCDecoderStruct (doubleArrayGP_LDPCDecoderStruct *GP_LDPCDecoder) {
  int i;
  for (i=0;i<GP_LDPCDecoder->N_N_x;i++) {
    if (GP_LDPCDecoder->x[i]!=NULL) free(GP_LDPCDecoder->x[i]);
  }
  free(GP_LDPCDecoder->N_x);GP_LDPCDecoder->N_x=NULL;
  free(GP_LDPCDecoder->x);GP_LDPCDecoder->x=NULL;
}

// Print arrayGP_LDPCDecoderStruct
void printDoubleArrayGP_LDPCDecoderStruct (doubleArrayGP_LDPCDecoderStruct *GP_LDPCDecoder, char *name, int index, int pre) {
}

// Plot function generates any plots associated with the 
// structure
void plotGP_LDPCDecoderStruct (GP_LDPCDecoderStruct *GP_LDPCDecoder, const char *filename) {
}

// All the data from all the modules is packed into an
// array of uint8_vectors for saving. One uint8_vector per module. 
// Each uint8_vector contains a stringified version of the
// data in the struct. uint8_vectors are then written to and 
// read from disk by the SWRC_saveuint8_vector and SWRC_loaduint8_vector 
// functions. This function packs struct data into a uint_8_vector
void packGP_LDPCDecoderStruct (GP_LDPCDecoderStruct *GP_LDPCDecoder, uint8_vector *cfgFile) {
  int i;
 //Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
  // Pack int **H
  for (i=0;i<(GP_LDPCDecoder->N_row_H);i++) 
    SWRC_packToUint8((uint8_t*)GP_LDPCDecoder->H[i],GP_LDPCDecoder->N_col_H,sizeof(int),cfgFile);
  // Pack double **L
  for (i=0;i<(GP_LDPCDecoder->N_row_L);i++) 
    SWRC_packToUint8((uint8_t*)GP_LDPCDecoder->L[i],GP_LDPCDecoder->N_col_L,sizeof(double),cfgFile);
  // Pack int N
  SWRC_packToUint8((uint8_t*)&GP_LDPCDecoder->N,1,sizeof(int),cfgFile);
  // Pack int M
  SWRC_packToUint8((uint8_t*)&GP_LDPCDecoder->M,1,sizeof(int),cfgFile);
  // Pack int K
  SWRC_packToUint8((uint8_t*)&GP_LDPCDecoder->K,1,sizeof(int),cfgFile);
  // Pack double R
  SWRC_packToUint8((uint8_t*)&GP_LDPCDecoder->R,1,sizeof(double),cfgFile);
 //Fields automatically included in every module that request $args{i}
  // Pack uint8_t trainFlag
  SWRC_packToUint8((uint8_t*)&GP_LDPCDecoder->trainFlag,1,sizeof(uint8_t),cfgFile);
  // Pack long int N_train
  SWRC_packToUint8((uint8_t*)&GP_LDPCDecoder->N_train,1,sizeof(long int),cfgFile);
  // Pack long int i_train
  SWRC_packToUint8((uint8_t*)&GP_LDPCDecoder->i_train,1,sizeof(long int),cfgFile);
  // Pack long unsigned int numberOfMult
  SWRC_packToUint8((uint8_t*)&GP_LDPCDecoder->numberOfMult,1,sizeof(long unsigned int),cfgFile);
  // Pack double aveNoOfMultPerFrame
  SWRC_packToUint8((uint8_t*)&GP_LDPCDecoder->aveNoOfMultPerFrame,1,sizeof(double),cfgFile);
  // Pack long unsigned int numberOfAdd
  SWRC_packToUint8((uint8_t*)&GP_LDPCDecoder->numberOfAdd,1,sizeof(long unsigned int),cfgFile);
  // Pack double aveNoOfAddPerFrame
  SWRC_packToUint8((uint8_t*)&GP_LDPCDecoder->aveNoOfAddPerFrame,1,sizeof(double),cfgFile);
  // Pack long unsigned int numberOfComp
  SWRC_packToUint8((uint8_t*)&GP_LDPCDecoder->numberOfComp,1,sizeof(long unsigned int),cfgFile);
  // Pack double aveNoOfCompPerFrame
  SWRC_packToUint8((uint8_t*)&GP_LDPCDecoder->aveNoOfCompPerFrame,1,sizeof(double),cfgFile);
  // Pack double simTime
  SWRC_packToUint8((uint8_t*)&GP_LDPCDecoder->simTime,1,sizeof(double),cfgFile);
  // Pack double aveSimTimePerFrame
  SWRC_packToUint8((uint8_t*)&GP_LDPCDecoder->aveSimTimePerFrame,1,sizeof(double),cfgFile);
  // Pack long unsigned int numberOfCalls
  SWRC_packToUint8((uint8_t*)&GP_LDPCDecoder->numberOfCalls,1,sizeof(long unsigned int),cfgFile);
}

// After loading the data back from a .cfg file, the data is unpacked
// back into the struct with this function.
void unpackGP_LDPCDecoderStruct (GP_LDPCDecoderStruct *GP_LDPCDecoder, uint8_vector *cfgFile) {
  int i;
  freeGP_LDPCDecoderStruct(GP_LDPCDecoder);
// Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
  // Unpack int **H
  if ((GP_LDPCDecoder->N_row_H)!=0) {
    GP_LDPCDecoder->H=(int**) calloc(GP_LDPCDecoder->N_row_H,sizeof(int*));
    for (i=0;i<(GP_LDPCDecoder->N_row_H);i++) {
      GP_LDPCDecoder->H[i]=(int*) calloc(GP_LDPCDecoder->N_col_H,sizeof(int));
      SWRC_unpackFromUint8((uint8_t*)GP_LDPCDecoder->H[i],GP_LDPCDecoder->N_col_H,sizeof(int),cfgFile);
    }
  }
  // Unpack double **L
  if ((GP_LDPCDecoder->N_row_L)!=0) {
    GP_LDPCDecoder->L=(double**) calloc(GP_LDPCDecoder->N_row_L,sizeof(double*));
    for (i=0;i<(GP_LDPCDecoder->N_row_L);i++) {
      GP_LDPCDecoder->L[i]=(double*) calloc(GP_LDPCDecoder->N_col_L,sizeof(double));
      SWRC_unpackFromUint8((uint8_t*)GP_LDPCDecoder->L[i],GP_LDPCDecoder->N_col_L,sizeof(double),cfgFile);
    }
  }
  // Unpack int N
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCDecoder->N,1,sizeof(int),cfgFile);
  // Unpack int M
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCDecoder->M,1,sizeof(int),cfgFile);
  // Unpack int K
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCDecoder->K,1,sizeof(int),cfgFile);
  // Unpack double R
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCDecoder->R,1,sizeof(double),cfgFile);
// Fields automatically included in every module that request $args{i}
  // Unpack uint8_t trainFlag
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCDecoder->trainFlag,1,sizeof(uint8_t),cfgFile);
  // Unpack long int N_train
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCDecoder->N_train,1,sizeof(long int),cfgFile);
  // Unpack long int i_train
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCDecoder->i_train,1,sizeof(long int),cfgFile);
  // Unpack long unsigned int numberOfMult
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCDecoder->numberOfMult,1,sizeof(long unsigned int),cfgFile);
  // Unpack double aveNoOfMultPerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCDecoder->aveNoOfMultPerFrame,1,sizeof(double),cfgFile);
  // Unpack long unsigned int numberOfAdd
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCDecoder->numberOfAdd,1,sizeof(long unsigned int),cfgFile);
  // Unpack double aveNoOfAddPerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCDecoder->aveNoOfAddPerFrame,1,sizeof(double),cfgFile);
  // Unpack long unsigned int numberOfComp
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCDecoder->numberOfComp,1,sizeof(long unsigned int),cfgFile);
  // Unpack double aveNoOfCompPerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCDecoder->aveNoOfCompPerFrame,1,sizeof(double),cfgFile);
  // Unpack double simTime
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCDecoder->simTime,1,sizeof(double),cfgFile);
  // Unpack double aveSimTimePerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCDecoder->aveSimTimePerFrame,1,sizeof(double),cfgFile);
  // Unpack long unsigned int numberOfCalls
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCDecoder->numberOfCalls,1,sizeof(long unsigned int),cfgFile);
}

// Pack the contents of arrayGP_LDPCDecoderStruct to a uint8_vector
void packArrayGP_LDPCDecoderStruct (arrayGP_LDPCDecoderStruct *GP_LDPCDecoder, uint8_vector *cfgFile) {
  SWRC_packToUint8((uint8_t*)&GP_LDPCDecoder->N_x,1,sizeof(long unsigned int),cfgFile);
  SWRC_packToUint8((uint8_t*)GP_LDPCDecoder->x,GP_LDPCDecoder->N_x,sizeof(GP_LDPCDecoderStruct),cfgFile);
}

// Unpack the contents of arrayGP_LDPCDecoderStruct from a uint8_vector.
void unpackArrayGP_LDPCDecoderStruct (arrayGP_LDPCDecoderStruct *GP_LDPCDecoder, uint8_vector *cfgFile) {
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCDecoder->N_x,1,sizeof(long unsigned int),cfgFile);
  GP_LDPCDecoder->x = (GP_LDPCDecoderStruct*)realloc(GP_LDPCDecoder->x,GP_LDPCDecoder->N_x*sizeof(GP_LDPCDecoderStruct));
  SWRC_unpackFromUint8((uint8_t*)GP_LDPCDecoder->x,GP_LDPCDecoder->N_x,sizeof(GP_LDPCDecoderStruct),cfgFile);
}

// Pack the contents of doubleArrayGP_LDPCDecoderStruct to a uint8_vector
void packDoubleArrayGP_LDPCDecoderStruct (doubleArrayGP_LDPCDecoderStruct *GP_LDPCDecoder, uint8_vector *cfgFile) {
  int i;
  SWRC_packToUint8((uint8_t*)&GP_LDPCDecoder->N_N_x,1,sizeof(long unsigned int),cfgFile);
  SWRC_packToUint8((uint8_t*)GP_LDPCDecoder->N_x,GP_LDPCDecoder->N_N_x,sizeof(long unsigned int),cfgFile);
  for (i=0;i<GP_LDPCDecoder->N_N_x;i++) 
    SWRC_packToUint8((uint8_t*)GP_LDPCDecoder->x[i],GP_LDPCDecoder->N_x[i],sizeof(GP_LDPCDecoderStruct),cfgFile);
}

// Unpack the contents of doubleArrayGP_LDPCDecoderStruct from a uint8_vector
void unpackDoubleArrayGP_LDPCDecoderStruct (doubleArrayGP_LDPCDecoderStruct *GP_LDPCDecoder, uint8_vector *cfgFile) {
  int i;
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCDecoder->N_N_x,1,sizeof(long unsigned int),cfgFile);
  // allocate memory for and unpack GP_LDPCDecoder->N_GP_LDPCDecoder
  GP_LDPCDecoder->N_x=(long unsigned int*) realloc(GP_LDPCDecoder->N_x,GP_LDPCDecoder->N_N_x*sizeof(long unsigned int));
  SWRC_unpackFromUint8((uint8_t*)GP_LDPCDecoder->N_x,GP_LDPCDecoder->N_N_x,sizeof(long unsigned int),cfgFile);
  // allocate memory for GP_LDPCDecoder->GP_LDPCDecoder
  GP_LDPCDecoder->x=(GP_LDPCDecoderStruct**)realloc(GP_LDPCDecoder->x,GP_LDPCDecoder->N_N_x*sizeof(GP_LDPCDecoderStruct*));
  for (i=0;i<GP_LDPCDecoder->N_N_x;i++) {
    SWRC_unpackFromUint8((uint8_t*)GP_LDPCDecoder->x[i],GP_LDPCDecoder->N_x[i],sizeof(GP_LDPCDecoderStruct),cfgFile);
  }
}

// Function for loading the struct
int loadGP_LDPCDecoderStruct (GP_LDPCDecoderStruct *GP_LDPCDecoder, char *filename) {
}

// Function for saving the struct
void saveGP_LDPCDecoderStruct (GP_LDPCDecoderStruct *GP_LDPCDecoder, char *filename) {
}

// Set parameters (fields) in the structure
// Change the values of fields in the structure
void setParmGP_LDPCDecoderStruct (GP_LDPCDecoderStruct *GP_LDPCDecoder, char *arg) {
  int i;
  SWRC_removeSpaces(arg);
   if (SWRC_readSingleArgumentFromString(arg,"N",&GP_LDPCDecoder->N,"%d")==1) {
     printf("N=%d\n",GP_LDPCDecoder->N);
   }
  // if (SWRC_readSingleArgumentFromString(arg,"M",&GP_LDPCDecoder->M,"%d")==1) {
  //   printf("M=%d\n",GP_LDPCDecoder->M);
  // }
   if (SWRC_readSingleArgumentFromString(arg,"K",&GP_LDPCDecoder->K,"%d")==1) {
     printf("K=%d\n",GP_LDPCDecoder->K);
   }

   if (SWRC_readSingleArgumentFromString(arg,"N_row_H",&GP_LDPCDecoder->N_row_H,"%d")==1) {
     printf("N_row_H=%d\n",GP_LDPCDecoder->N_row_H);
   }
     if (SWRC_readSingleArgumentFromString(arg,"N_col_H",&GP_LDPCDecoder->N_col_H,"%d")==1) {
     printf("N_col_H=%d\n",GP_LDPCDecoder->N_col_H);
     }
   
  // if (SWRC_readSingleArgumentFromString(arg,"R",&GP_LDPCDecoder->R,"%lf")==1) {
  //   printf("R=%lf\n",GP_LDPCDecoder->R);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"trainFlag",&GP_LDPCDecoder->trainFlag,"%"SCNu8"")==1) {
  //   printf("trainFlag=%"SCNu8"\n",GP_LDPCDecoder->trainFlag);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"N_train",&GP_LDPCDecoder->N_train,"%ld")==1) {
  //   printf("N_train=%ld\n",GP_LDPCDecoder->N_train);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"i_train",&GP_LDPCDecoder->i_train,"%ld")==1) {
  //   printf("i_train=%ld\n",GP_LDPCDecoder->i_train);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfMult",&GP_LDPCDecoder->numberOfMult,"%lu")==1) {
  //   printf("numberOfMult=%lu\n",GP_LDPCDecoder->numberOfMult);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveNoOfMultPerFrame",&GP_LDPCDecoder->aveNoOfMultPerFrame,"%lf")==1) {
  //   printf("aveNoOfMultPerFrame=%lf\n",GP_LDPCDecoder->aveNoOfMultPerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfAdd",&GP_LDPCDecoder->numberOfAdd,"%lu")==1) {
  //   printf("numberOfAdd=%lu\n",GP_LDPCDecoder->numberOfAdd);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveNoOfAddPerFrame",&GP_LDPCDecoder->aveNoOfAddPerFrame,"%lf")==1) {
  //   printf("aveNoOfAddPerFrame=%lf\n",GP_LDPCDecoder->aveNoOfAddPerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfComp",&GP_LDPCDecoder->numberOfComp,"%lu")==1) {
  //   printf("numberOfComp=%lu\n",GP_LDPCDecoder->numberOfComp);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveNoOfCompPerFrame",&GP_LDPCDecoder->aveNoOfCompPerFrame,"%lf")==1) {
  //   printf("aveNoOfCompPerFrame=%lf\n",GP_LDPCDecoder->aveNoOfCompPerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"simTime",&GP_LDPCDecoder->simTime,"%lf")==1) {
  //   printf("simTime=%lf\n",GP_LDPCDecoder->simTime);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveSimTimePerFrame",&GP_LDPCDecoder->aveSimTimePerFrame,"%lf")==1) {
  //   printf("aveSimTimePerFrame=%lf\n",GP_LDPCDecoder->aveSimTimePerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfCalls",&GP_LDPCDecoder->numberOfCalls,"%lu")==1) {
  //   printf("numberOfCalls=%lu\n",GP_LDPCDecoder->numberOfCalls);
  // }
  if (*arg!='\0') {
    printf("GP_LDPCDecoder module: Remaining unknown parms in arg list:%s\n Please correct and run again.\n",arg);exit(-1);
  }
}

// A command comes from the user
// This function processes and executes the command
// some commands need a signal to operate on, which is
// passed via the signalStruct. 
void processCommandGP_LDPCDecoder (GP_LDPCDecoderStruct *GP_LDPCDecoder, signalStruct *signal, const char *command) {
  char commandParameter[400];
  int i;
  printf("processCommandGP_LDPCDecoder:%s\n",command);
  for(i=0;i<400 && i<strlen(command);) {
    if (SWRC_matchCommand(command,"load",&i,commandParameter,400)==1) {
	loadGP_LDPCDecoderStruct(GP_LDPCDecoder,commandParameter);
	continue;
    }

    if (SWRC_matchCommand(command,"print",&i,commandParameter,400)==1) {
	printGP_LDPCDecoderStruct(GP_LDPCDecoder,"GP_LDPCDecoder",0,0);
	continue;
    }

    if (SWRC_matchCommand(command,"setParm",&i,commandParameter,400)==1) {
	setParmGP_LDPCDecoderStruct(GP_LDPCDecoder,commandParameter);
	continue;
    }

    if (SWRC_matchCommand(command,"checkParm",&i,commandParameter,400)==1) {
	checkParametersGP_LDPCDecoder(GP_LDPCDecoder);
	continue;
    }

    if (SWRC_matchCommand(command,"precomp",&i,commandParameter,400)==1) {
	precompGP_LDPCDecoder(GP_LDPCDecoder);
	continue;
    }

    if (SWRC_matchCommand(command,"postcomp",&i,commandParameter,400)==1) {
	postcompGP_LDPCDecoder(GP_LDPCDecoder,0);
	continue;
    }

    if (SWRC_matchCommand(command,"help",&i,commandParameter,400)==1) {
	helpCommandGP_LDPCDecoder(0);
	continue;
    }

    if (SWRC_matchCommand(command,"run",&i,commandParameter,400)==1) {
	runGP_LDPCDecoder(GP_LDPCDecoder, signal);
	continue;
    }

    printf("processCommandGP_LDPCDecoder: Unknown command:%s\n",&command[i]);
    break;
  }
}

// Provides instructions on the commands that this module is able to process.
void helpCommandGP_LDPCDecoder (int index) {
  printf("Commands recognized by %d:GP_LDPCDecoderStruct:\n",index);
  printf("  \"print();\"        : print the GP_LDPCDecoderStruct fields\n");
  printf("  \"setParm(arg);\"   : set the GP_LDPCDecoderStruct fields\n");
  printf("  \"help();\"         : display this help screen\n");
}

// Check that all the parameters needed to run the simulation are present.
// Uncomment any/all variables that _need_ to be present for the simulation to run.
int checkParametersGP_LDPCDecoder (GP_LDPCDecoderStruct *GP_LDPCDecoder) {
  int output=0;
  //if (GP_LDPCDecoder->H==NULL) {output++;printf("GP_LDPCDecoder->H needed, but not set\n");}
  //if (GP_LDPCDecoder->L==NULL) {output++;printf("GP_LDPCDecoder->L needed, but not set\n");}
  //if (GP_LDPCDecoder->N==0) {output++;printf("GP_LDPCDecoder->N needed, but not set\n");}
  //if (GP_LDPCDecoder->M==0) {output++;printf("GP_LDPCDecoder->M needed, but not set\n");}
  //if (GP_LDPCDecoder->K==0) {output++;printf("GP_LDPCDecoder->K needed, but not set\n");}
  //if (GP_LDPCDecoder->R==0.0) {output++;printf("GP_LDPCDecoder->R needed, but not set\n");}
  //if (GP_LDPCDecoder->trainFlag==0) {output++;printf("GP_LDPCDecoder->trainFlag needed, but not set\n");}
  //if (GP_LDPCDecoder->N_train==0) {output++;printf("GP_LDPCDecoder->N_train needed, but not set\n");}
  //if (GP_LDPCDecoder->i_train==0) {output++;printf("GP_LDPCDecoder->i_train needed, but not set\n");}
  //if (GP_LDPCDecoder->numberOfMult==0) {output++;printf("GP_LDPCDecoder->numberOfMult needed, but not set\n");}
  //if (GP_LDPCDecoder->aveNoOfMultPerFrame==0.0) {output++;printf("GP_LDPCDecoder->aveNoOfMultPerFrame needed, but not set\n");}
  //if (GP_LDPCDecoder->numberOfAdd==0) {output++;printf("GP_LDPCDecoder->numberOfAdd needed, but not set\n");}
  //if (GP_LDPCDecoder->aveNoOfAddPerFrame==0.0) {output++;printf("GP_LDPCDecoder->aveNoOfAddPerFrame needed, but not set\n");}
  //if (GP_LDPCDecoder->numberOfComp==0) {output++;printf("GP_LDPCDecoder->numberOfComp needed, but not set\n");}
  //if (GP_LDPCDecoder->aveNoOfCompPerFrame==0.0) {output++;printf("GP_LDPCDecoder->aveNoOfCompPerFrame needed, but not set\n");}
  //if (GP_LDPCDecoder->simTime==0.0) {output++;printf("GP_LDPCDecoder->simTime needed, but not set\n");}
  //if (GP_LDPCDecoder->aveSimTimePerFrame==0.0) {output++;printf("GP_LDPCDecoder->aveSimTimePerFrame needed, but not set\n");}
  //if (GP_LDPCDecoder->numberOfCalls==0) {output++;printf("GP_LDPCDecoder->numberOfCalls needed, but not set\n");}
  return(output);
}

// Precomputation done just prior to the main for loop
// iterating the BER/FER are put into this subroutine
void precompGP_LDPCDecoder (GP_LDPCDecoderStruct *GP_LDPCDecoder) {
  GP_LDPCDecoder->i_train=0;
  GP_LDPCDecoder->numberOfMult=0;
  GP_LDPCDecoder->aveNoOfMultPerFrame=0.0;
  GP_LDPCDecoder->numberOfAdd=0;
  GP_LDPCDecoder->aveNoOfAddPerFrame=0.0;
  GP_LDPCDecoder->numberOfComp=0;
  GP_LDPCDecoder->aveNoOfCompPerFrame=0.0;
  GP_LDPCDecoder->simTime=0.0;
  GP_LDPCDecoder->aveSimTimePerFrame=0.0;
  GP_LDPCDecoder->numberOfCalls=0;
}

// postComputation, such as freeing up any memory, done after
// the iteration of the BER/FER are put into this subroutine
void postcompGP_LDPCDecoder (GP_LDPCDecoderStruct *GP_LDPCDecoder, char finishedFlag) {
  GP_LDPCDecoder->aveNoOfMultPerFrame=(double)GP_LDPCDecoder->numberOfMult/GP_LDPCDecoder->numberOfCalls;
  GP_LDPCDecoder->aveNoOfAddPerFrame=(double)GP_LDPCDecoder->numberOfAdd/GP_LDPCDecoder->numberOfCalls;
  GP_LDPCDecoder->aveNoOfCompPerFrame=(double)GP_LDPCDecoder->numberOfComp/GP_LDPCDecoder->numberOfCalls;
  GP_LDPCDecoder->aveSimTimePerFrame=(double)GP_LDPCDecoder->simTime/GP_LDPCDecoder->numberOfCalls;
}

// Function called prior to training. Zero out statistics matrices,
// set the i_train index to zero etc...
void pretrainGP_LDPCDecoder (GP_LDPCDecoderStruct *GP_LDPCDecoder) {
  GP_LDPCDecoder->i_train=0;
}

// Function called after training. Free allocated memory etc...
void posttrainGP_LDPCDecoder (GP_LDPCDecoderStruct *GP_LDPCDecoder) {
}

// Some modules have a training phase where modules before them are run
// and statistics collected so the module can run properly.
// This function performs the training for the module then 
// saved back to the .cfg file.
// Returns 1 if training is complete
// Returns 0 otherwise
int trainGP_LDPCDecoder (GP_LDPCDecoderStruct *GP_LDPCDecoder, signalStruct *signal) {
  if ((GP_LDPCDecoder->trainFlag&1)==1) { // Training complete, call the run function
    printf("Running GP_LDPCDecoder\n");
    runGP_LDPCDecoder(GP_LDPCDecoder,signal);
    return(1);
  } else {                 // Do the training
    printf("Training GP_LDPCDecoder %ld/%ld\n",GP_LDPCDecoder->i_train,GP_LDPCDecoder->N_train);
    // Accumulate the statistics
    GP_LDPCDecoder->i_train++;
    if (GP_LDPCDecoder->i_train>=GP_LDPCDecoder->N_train) { // Statistics accumulated, post-training computation
      GP_LDPCDecoder->trainFlag=1;
    }
    return(0);
  }
}

// Contribute the fields to the berResultStruct that will be 
// printed in the berResult file. Every module contributes
// its own fields. User has to choose the fields to be saved
// using pushBerResultField() once per field to be added
void initBerResultStructGP_LDPCDecoder (GP_LDPCDecoderStruct *GP_LDPCDecoder,berResultStruct *berResult) {
  //pushBerResultField(berResult,"N","int","%1d",&GP_LDPCDecoder->N);
  //pushBerResultField(berResult,"M","int","%1d",&GP_LDPCDecoder->M);
  //pushBerResultField(berResult,"K","int","%1d",&GP_LDPCDecoder->K);
  //pushBerResultField(berResult,"R","double","%1lf",&GP_LDPCDecoder->R);
  //pushBerResultField(berResult,"trainFlag","uint8_t","%9"SCNu8"",&GP_LDPCDecoder->trainFlag);
  //pushBerResultField(berResult,"N_train","long int","%7ld",&GP_LDPCDecoder->N_train);
  //pushBerResultField(berResult,"i_train","long int","%7ld",&GP_LDPCDecoder->i_train);
  //pushBerResultField(berResult,"numberOfMult","long unsigned int","%12lu",&GP_LDPCDecoder->numberOfMult);
  //pushBerResultField(berResult,"aveNoOfMultPerFrame","double","%19lf",&GP_LDPCDecoder->aveNoOfMultPerFrame);
  //pushBerResultField(berResult,"numberOfAdd","long unsigned int","%11lu",&GP_LDPCDecoder->numberOfAdd);
  //pushBerResultField(berResult,"aveNoOfAddPerFrame","double","%18lf",&GP_LDPCDecoder->aveNoOfAddPerFrame);
  //pushBerResultField(berResult,"numberOfComp","long unsigned int","%12lu",&GP_LDPCDecoder->numberOfComp);
  //pushBerResultField(berResult,"aveNoOfCompPerFrame","double","%19lf",&GP_LDPCDecoder->aveNoOfCompPerFrame);
  //pushBerResultField(berResult,"simTime","double","%7lf",&GP_LDPCDecoder->simTime);
  //pushBerResultField(berResult,"aveSimTimePerFrame","double","%18lf",&GP_LDPCDecoder->aveSimTimePerFrame);
  //pushBerResultField(berResult,"numberOfCalls","long unsigned int","%13lu",&GP_LDPCDecoder->numberOfCalls);
}

#include <stdlib.h>
#include <stdint.h> //for uint8_t
#include <limits.h> // For INT_MAX in row operation

#define row_H 230
#define column_H 340
#define row_L row_H
#define column_L column_H
#define r_size 340

//dhiva's part
int H[row_H][column_H];
double new_Input[r_size];
double L[row_L][column_L];
double temp[row_L][column_L];
double Lnew[row_L][column_L];
double sign[row_L][column_L];
//jw's part
double sum[r_size];
double sum_L[r_size];
double new_L[row_L][r_size];
int newSum[r_size];
int Output[r_size];

int i, j, k;

//declare functions
void L_initial();//Initialisation
void L_row_operation();//Row operation
void row_operation();//find min1 and min2
void Adjust_Row_Element(double first, double second, int index);
void get_parity_L();//count and see parity of each row
void update_parity_L(float n, int i);//update the signs of numbers in each row 
void update_L_matrix();//update final output
void print_L_matrix();//print final output
void L_column_operation();//Column operation
void L_final();//Final Decision
int syndrome();//Syndrome Check

void L_initial(){
  int i, j ,k;

  //This part gets H 
  //Dynamically allocate L, make L size=H size
  //input col[1] = L 1st col(wherever non zero)
  //if(L[i][1]==1): L[i][j]=input[j]

  for(i=0; i<column_L; i++)
    {
      for(j=0; j<row_L; j++)
	{
	  if (H[j][i] == 0)
	    {
	      L[j][i] = 0;//remain position of 0s on H
	    }
	  else
	    {
	      L[j][i] = new_Input[i];
	    }
	   
	}
    }
  //print output of initialisation
  // printf("\n-------Initialisation-------\n\n");
   for (i=0; i<row_L; i++)
     {
       for (j=0; j<column_L; j++)
   	{
	  // printf("%f ", L[i][j]);
   	}
       // printf("\n");
     }
}

void L_row_operation(){

  row_operation(); //Get magnitude
  get_parity_L(); //Get the sign first
  update_L_matrix(); //Updating magnitude with sign
}

void row_operation()
{

  int i, j, k;
  double first, second;

  first = second = INT_MAX;

  // reset negative sign
  for(i=0; i<row_L; i++)
    {
      for(j=0; j<column_L; j++)
  	{
	  if (L[i][j] < 0)
  	    {
  	      temp[i][j] = L[i][j]*(-1);
  	    }

	  else
	    {
	      temp[i][j] = L[i][j];
	    }
  	}
    }

  // printf("\n-------L after resetting the signs-------\n\n");
   for(i=0; i<row_L; i++)
     {
       for(j=0; j<column_L; j++)
   	{
	   
	  //  printf("%f ",temp[i][j]);
	    
   	}
       // printf("\n");
     }
    
  //Row Operation Starts
  //printf("\n-------Row Operation-------");
  for(i=0; i<row_L; i++)
    {
      for(j=0; j<column_L; j++)
	{
	  //if (H[i][j] == 0.0){
	     //first=0.0;
	     // second=0.0;
	  // }
	  //printf("\n H[%d][%d]: %d",i,j, H[i][j]);
	    if (H[i][j] != 0.0){
	     
	     
	   if (temp[i][j] < first )
	    {
	      //If current element smaller than first, update first and second
	      second = first;
	      //printf("\n sec: %f ",second);
	      first = temp[i][j]; //update first to current element
	      //printf("\n hfiueruifecond");
	      //printf("\nj:%d first: %f",j,first);
	      //printf("\nj:%d sec: %f",j,second);
	      
	    }//1
	  
	  else if (temp[i][j] < second && temp[i][j] != first )
	    {	     
	      //if current element in between first and second
	    
		second = temp[i][j];

	      //printf("\n col [%d][%d]   %f     %f",i,j,first,second);
	      //printf("\nsec: %f",second);
		//printf("\nj:%d sec: %f fir:%f",j,second,first);
		  
	    }//2

	  else if (temp[i][j] == first && second == INT_MAX )
	    {
	      second = first;
	      //printf("\nj:%d first: %f",j,first);
	      //printf("\nj:%d sec: %f",j,second);
	      //first = temp[i][j];
	    }//3

	  else if (temp[i][j] < first && L[i][j]!=0.0 )
	    {
	      second = temp[i][j];
	      //printf("\nj:%d sec: %f",j,second);
	    }//4

	  else if (temp[i][j] < second && L[i][j]!= 0.0)
	    {
	      second = temp[i][j];
	      //printf("\nj:%d sec: %f",j,second);
	    }
	   
	  }//if H!=0	 
	  
	}
      // if(first == INT_MAX && second == INT_MAX)
      // 	{
      // 	  first = 0.0;
      // 	  second= 0.0;
      // 	}
       // printf("\n\nRow %d: smallest: %f \t2nd smallest: %f ",i,first,second);
      Adjust_Row_Element(first, second, i);
      first = second = INT_MAX; //reset values
      //printf("\n col [%d][%d]   %f     %f",i,j,first,second);
    }
}

void Adjust_Row_Element(double first, double second, int index){

  int start = 0; //1st non zero position in L
  
  // printf("\n f: %f  s: %f ",first, second);
   
  for(j=0; j<column_L; j++)
    {
      if (L[index][j] == 0)
	{
	  //j++;
	}

      else if (start == 0)
	{
	  Lnew[index][j] = second;
	  start = 1; //update
	}
      else if (start != 0)
	{
	  Lnew[index][j] = first;
	  start = 1; //update
	}
    }
}

void get_parity_L(){

  float n = 1;
  int x = 1;

  for(i=0; i<row_L; i++)
    {
      for(j=0; j<column_L; j++)
	{
	  if(L[i][j] != 0.0)
	    {	      	      
	      n = n * L[i][j];
	    }
	}     
      
      update_parity_L(n, i);
      n = 1; //reset n
    }

}
  
void update_parity_L(float n, int i){

  for(j=0; j<column_L; j++)
    {
      if(L[i][j]<0 && n>0) //if element of L is negative, 
	{
	  Lnew[i][j] = Lnew[i][j] * -1;
	}
      else if (L[i][j]>0 && n<0)
	{
	  Lnew[i][j] = Lnew[i][j] * -1;
	}
      //printf("L[%d][%d]: %f ",i,j,L[i][j]);
    }
  // printf("\n");
  // printf("\n n: %f",n);
}

void update_L_matrix(){

  //printf("\n\n\n------Updating L Matrix ----------- \n \n");

  for(i=0; i<row_L; i++)
    {
      for(j=0; j<column_L; j++)
	{	   
	  L[i][j] = Lnew[i][j];
	}
    }
}
  
void print_L_matrix(){

  //printf("\n\n-------Printing Updated L Matrix------- \n \n");

  for(i=0; i<row_L; i++)
    {
      for(j=0; j<column_L; j++)
	{
	  // if (j==339)
	  //   {
	  //     printf("L[%d][%d]=%lf\n", i, j, L[i][j]);
	  //   }
	  // printf("%f ",L[i][j]);
	}
      // printf("\n");
    }
}

void L_column_operation()
{
  //printf("\n-------Sum L of each column-------\n\n");
  //sum up all the elements of same column in L
  for(j=0;j<r_size;j++)
    {
      for(i=0;i<row_L;i++)
      	{
	  sum_L[j]+=L[i][j];
	}
      // if (j==339)
      // 	{
      // 	  printf("sum_L[%d]: %lf\n", j, sum_L[j]);
      // 	}
    }
  //sum up the elements of same column of r and L
  //printf("\n-------Sum of each column-------\n\n");
  for (j=0;j<r_size;j++)
    {
      sum[j]=new_Input[j]+sum_L[j];
      sum_L[j]=0.0;
      // printf("sum[%d]: %lf\n",j, sum[j]);
    }
  //create new L
  //printf("\n-------New L-------\n\n");
  // j=0;

  for (i=0;i<row_L;i++)
    {
      for(j=0;j<r_size;j++)
	{
	  if (L[i][j]!=0)
	    {
	      new_L[i][j]=sum[j]-L[i][j];
	    }
	  // printf("%lf", new_L[i][j]);
	}
      // printf("\n");
    }
}
void L_final()
{
  //final decision
  //printf("\n-------Final Decision-------\n\n");
  for (j=0;j<r_size;j++)
    {
      if (sum[j]>0)
	{
	  sum[j]=0;
	}
      else if (sum[j]<0)
	{
	  sum[j]=1;
	}
      printf("%f\n", sum[j]);
    }
}

// Finally when everything is in place, the module must be
// run during the actual simulation. The code for running
// the module is in this function.
void runGP_LDPCDecoder (GP_LDPCDecoderStruct *GP_LDPCDecoder, signalStruct *signal) {
  clock_t beginTime, endTime;
  int N_input,N_output;

  double *input;
  uint8_t *output;
  beginTime=clock();
  printf("In function runGP_LDPCDecoder\n");
  // Allocate memory for 1 more signal. The output of this function should go there.
  // USER NEEDS TO EDIT: the LENGTH of the output vector and the TYPE of
  // the output vector 0=uint8_t, 1=char, 2=int, 3=unsigned int, 4=long unsigned int, 5=float, 6=double
  // The type of the input vector should also be set correctly by the USER.
  N_input  = signal->N[signal->N_N-1];        // Length of the input vector
  input    = (double*) signal->x[signal->N_N-1]; // Assign pointer to the input memory
  N_output = 110; //length of output vector
  output   = (uint8_t*) incrementByOneSignal(signal,N_output,0,"GP_LDPCDecoder");    // Create a new output vector on end of signal list

  //Function for decoding process
 
  // Computation engine :
  // printf("Input: \n");
  // for (j=0;j<N_input;j++)
  //   {
  //     printf("%f\n", input[j]);

  //   }
  
  // printf("%d\n",r_size);
  for (j=0;j<r_size;j++)
    {
      new_Input[j]=  input[j];
      printf("%f\n", new_Input[j]);

    }
  
  FILE* f;
  f=fopen("H_matrix.txt", "r");
  if (!feof(f))
    {
      for (k=0;k<row_H;k++)
        {
	  for (j=0;j<column_H;j++)
            {
	      fscanf(f, "%d",&H[k][j]);
	      // printf("H[%d][%d]: %d\n", k, j, H[k][j]);
            }
	  // printf("\n");
        }
    }
  fclose(f);
  
  int i, j, k;

  int size;

  //Initialise L as sparse matrix (all zeros)
  for (i=0; i<row_L; i++)
    {
      for (j=0; j<column_L; j++)
	{
	  L[i][j]=0;
	}
    }
  //Print L
  for (i=0; i<row_L; i++)
    {
      for (j=0; j<column_L; j++)
	{
	  //printf("%f ", L[i][j]);
	}
      //printf("\n");
    }
   
  L_initial(); //initialisation
  L_row_operation();//row operation
  //print_L_matrix();
  //print output from row operation (which is also old L in column operation)
  L_column_operation();//column operation  
  L_final();//final decision
  //output=final decision
  for (j=0;j<110;j++)
    {
      if (sum[j]==1)
      	{
      	  output[j]=1;
      	}
      else
      	{
      	  output[j]=0;
      	}
      // output[j]= (uint8_t) sum[j];
    }
  
  // Save the time for the computation engine
  endTime = clock();
  GP_LDPCDecoder->simTime+=(double)(endTime-beginTime)/CLOCKS_PER_SEC;
  GP_LDPCDecoder->numberOfCalls++;
}


