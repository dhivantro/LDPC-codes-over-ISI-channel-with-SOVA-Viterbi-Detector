// Software Recording Channel (SWRC) platform in C.
// Name      : GP_LDPCEncoder
// Type      : module.
// Path      : modules/encoder/GP_LDPCEncoder
// Dependency: 
// Version   : 1.0
// Author(s) : Kheong Sann Chan.
// Date      : Mon Mar 28 17:13:28 2022
// Comment   : LDPC encoder parameters 

#include "GP_LDPCEncoder.h"
// Print the int **H struct
void printHGP_LDPCEncoderStruct (GP_LDPCEncoderStruct *GP_LDPCEncoder) {
}

// Free the memory allocated to int **H
void freeHGP_LDPCEncoderStruct (GP_LDPCEncoderStruct *GP_LDPCEncoder) {
}

// Allocate memory for int **H
void allocateHGP_LDPCEncoderStruct (GP_LDPCEncoderStruct *GP_LDPCEncoder) {
}

// Initialize the fields in the module structure
// Set pointers to NULL (so they can be called with realloc)
// Initialize the parameters to sane start-up values.
void initGP_LDPCEncoderStruct (GP_LDPCEncoderStruct *GP_LDPCEncoder) {
  // Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
  GP_LDPCEncoder->H                   = NULL;
  GP_LDPCEncoder->N                   = 0;
  GP_LDPCEncoder->M                   = 0;
  GP_LDPCEncoder->K                   = 0;
  GP_LDPCEncoder->R                   = 0.0;
  // Fields automatically included in every module that request $args{i}
  GP_LDPCEncoder->trainFlag           = 0;
  GP_LDPCEncoder->N_train             = 0;
  GP_LDPCEncoder->i_train             = 0;
  GP_LDPCEncoder->numberOfMult        = 0;
  GP_LDPCEncoder->aveNoOfMultPerFrame = 0.0;
  GP_LDPCEncoder->numberOfAdd         = 0;
  GP_LDPCEncoder->aveNoOfAddPerFrame  = 0.0;
  GP_LDPCEncoder->numberOfComp        = 0;
  GP_LDPCEncoder->aveNoOfCompPerFrame = 0.0;
  GP_LDPCEncoder->simTime             = 0.0;
  GP_LDPCEncoder->aveSimTimePerFrame  = 0.0;
  GP_LDPCEncoder->numberOfCalls       = 0;
}

// Frees up all the memory in the structure
void freeGP_LDPCEncoderStruct (GP_LDPCEncoderStruct *GP_LDPCEncoder) {
  if (GP_LDPCEncoder==NULL) {printf("GP_LDPCEncoder=NULL in function freeGP_LDPCEncoderStruct not free'ing\n");return;}
  int i;
  //Free int **H
  freeHGP_LDPCEncoderStruct(GP_LDPCEncoder);
  GP_LDPCEncoder->N             =0;
  GP_LDPCEncoder->M             =0;
  GP_LDPCEncoder->K             =0;
  GP_LDPCEncoder->R             =0.0;
  GP_LDPCEncoder->trainFlag     =0;
  GP_LDPCEncoder->N_train       =0;
  GP_LDPCEncoder->i_train       =0;
  GP_LDPCEncoder->numberOfMult  =0;
  GP_LDPCEncoder->aveNoOfMultPerFrame=0.0;
  GP_LDPCEncoder->numberOfAdd   =0;
  GP_LDPCEncoder->aveNoOfAddPerFrame=0.0;
  GP_LDPCEncoder->numberOfComp  =0;
  GP_LDPCEncoder->aveNoOfCompPerFrame=0.0;
  GP_LDPCEncoder->simTime       =0.0;
  GP_LDPCEncoder->aveSimTimePerFrame=0.0;
  GP_LDPCEncoder->numberOfCalls =0;
  //free(GP_LDPCEncoder);GP_LDPCEncoder=NULL;
}

// Prints the contents of the structure.
// Used for determining the status of the simulation
// as well as for debugging.
void printGP_LDPCEncoderStruct (GP_LDPCEncoderStruct *GP_LDPCEncoder, char *name, int index, int pre) {
  int i,j;
  char *preString,*name2;
  if (GP_LDPCEncoder==NULL) {printf("%s%s=NULL\n",preString,name);return;}
  preString=(char*)calloc((pre+1),sizeof(char));
  for (i=0;i<pre;i++) preString[i]=' '; preString[i]='\0';
  printf("%s[--%d:%s--------\n",preString,index,name);
  // Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
  printHGP_LDPCEncoderStruct(GP_LDPCEncoder);                                                        // Print int **H
  printf("%s  int                  %s->N=%d\n",preString,name,GP_LDPCEncoder->N);                    // Print int N
  printf("%s  int                  %s->M=%d\n",preString,name,GP_LDPCEncoder->M);                    // Print int M
  printf("%s  int                  %s->K=%d\n",preString,name,GP_LDPCEncoder->K);                    // Print int K
  printf("%s  double               %s->R=%lf\n",preString,name,GP_LDPCEncoder->R);                   // Print double R
  // Fields automatically included in every module that request $args{i}
  printf("%s  uint8_t              %s->trainFlag=%"SCNu8"\n",preString,name,GP_LDPCEncoder->trainFlag); // Print uint8_t trainFlag
  printf("%s  long int             %s->N_train=%ld\n",preString,name,GP_LDPCEncoder->N_train);       // Print long int N_train
  printf("%s  long int             %s->i_train=%ld\n",preString,name,GP_LDPCEncoder->i_train);       // Print long int i_train
  printf("%s  long unsigned int    %s->numberOfMult=%lu\n",preString,name,GP_LDPCEncoder->numberOfMult); // Print long unsigned int numberOfMult
  printf("%s  double               %s->aveNoOfMultPerFrame=%lf\n",preString,name,GP_LDPCEncoder->aveNoOfMultPerFrame); // Print double aveNoOfMultPerFrame
  printf("%s  long unsigned int    %s->numberOfAdd=%lu\n",preString,name,GP_LDPCEncoder->numberOfAdd); // Print long unsigned int numberOfAdd
  printf("%s  double               %s->aveNoOfAddPerFrame=%lf\n",preString,name,GP_LDPCEncoder->aveNoOfAddPerFrame); // Print double aveNoOfAddPerFrame
  printf("%s  long unsigned int    %s->numberOfComp=%lu\n",preString,name,GP_LDPCEncoder->numberOfComp); // Print long unsigned int numberOfComp
  printf("%s  double               %s->aveNoOfCompPerFrame=%lf\n",preString,name,GP_LDPCEncoder->aveNoOfCompPerFrame); // Print double aveNoOfCompPerFrame
  printf("%s  double               %s->simTime=%lf\n",preString,name,GP_LDPCEncoder->simTime);       // Print double simTime
  printf("%s  double               %s->aveSimTimePerFrame=%lf\n",preString,name,GP_LDPCEncoder->aveSimTimePerFrame); // Print double aveSimTimePerFrame
  printf("%s  long unsigned int    %s->numberOfCalls=%lu\n",preString,name,GP_LDPCEncoder->numberOfCalls); // Print long unsigned int numberOfCalls
  printf("%s---%d:%s-------]\n",preString,index,name);
  free(preString);
}

// Store random values into the fields of GP_LDPCEncoderStruct.
// For testing that saving to .cfg file works.
// User should help to write appropriate random-generating values
// to be stored in the appropriate fields.
void randomizeGP_LDPCEncoderStruct (GP_LDPCEncoderStruct *GP_LDPCEncoder) {
  int idum=1;SWRC_randomize(&idum);
  //GP_LDPCEncoder->H=rand();
  //GP_LDPCEncoder->N=rand();
  //GP_LDPCEncoder->M=rand();
  //GP_LDPCEncoder->K=rand();
  //GP_LDPCEncoder->R=ran2(&idum);
}

// Initialize an array of GP_LDPCEncoderStruct's to sane starting values
void initArrayGP_LDPCEncoderStruct (arrayGP_LDPCEncoderStruct *GP_LDPCEncoder) {
  GP_LDPCEncoder->N_x=0;
  GP_LDPCEncoder->x=NULL;
}

// Allocate memory for an array of N GP_LDPCEncoderStruct's
void allocateArrayGP_LDPCEncoderStruct (arrayGP_LDPCEncoderStruct *GP_LDPCEncoder,int N) {
  int i;
  GP_LDPCEncoder->N_x=N;
  GP_LDPCEncoder->x = (GP_LDPCEncoderStruct*)realloc(GP_LDPCEncoder->x,N*sizeof(GP_LDPCEncoderStruct));
  for (i=0;i<GP_LDPCEncoder->N_x;i++) {
    initGP_LDPCEncoderStruct(&GP_LDPCEncoder->x[i]);
  }
}

// Free an array of GP_LDPCEncoderStruct's
void freeArrayGP_LDPCEncoderStruct (arrayGP_LDPCEncoderStruct *GP_LDPCEncoder) {
  if (GP_LDPCEncoder==NULL) {printf("GP_LDPCEncoder=NULL in function freeArrayGP_LDPCEncoderStruct not free'ing\n");return;}
  int i;
  for (i=0;i<GP_LDPCEncoder->N_x;i++) {
    freeGP_LDPCEncoderStruct(&GP_LDPCEncoder->x[i]);
  } free(GP_LDPCEncoder->x);GP_LDPCEncoder->x=NULL;
}

// Fill the arrayGP_LDPCEncoderStruct with random values.
// The GP_LDPCEncoder->N_GP_LDPCEncoder parameter 
// must be set to the number of elements in the array.
// Array must be allocated before calling this function.
void randomizeArrayGP_LDPCEncoderStruct (arrayGP_LDPCEncoderStruct *GP_LDPCEncoder) {
  int i;
  for (i=0;i<GP_LDPCEncoder->N_x;i++) randomizeGP_LDPCEncoderStruct(&GP_LDPCEncoder->x[i]);
}

// Print arrayGP_LDPCEncoderStruct
void printArrayGP_LDPCEncoderStruct (arrayGP_LDPCEncoderStruct *GP_LDPCEncoder) {
  int i;
  for (i=0;i<GP_LDPCEncoder->N_x;i++) {
    printGP_LDPCEncoderStruct(&GP_LDPCEncoder->x[i],"GP_LDPCEncoder",i,0);
  }
}

// Initialize a double array of GP_LDPCEncoderStruct to sane startup values
void initDoubleArrayGP_LDPCEncoderStruct (doubleArrayGP_LDPCEncoderStruct *GP_LDPCEncoder) {
  GP_LDPCEncoder->N_N_x=0;
  GP_LDPCEncoder->N_x=NULL;
  GP_LDPCEncoder->x=NULL;
}

// Allocate memory for a rectangular double array of GP_LDPCEncoderStruct
void allocateDoubleArrayGP_LDPCEncoderStruct (doubleArrayGP_LDPCEncoderStruct *GP_LDPCEncoder, int N, int M) {
  int i,j;
  GP_LDPCEncoder->N_N_x=N;
  GP_LDPCEncoder->N_x=(long unsigned int*)realloc(GP_LDPCEncoder->N_x,N*sizeof(long unsigned int));
  for (i=0;i<GP_LDPCEncoder->N_N_x;i++) GP_LDPCEncoder->N_x[i]=M;
  GP_LDPCEncoder->x=(GP_LDPCEncoderStruct**)realloc(GP_LDPCEncoder->x,N*sizeof(GP_LDPCEncoderStruct*));
  for (i=0;i<GP_LDPCEncoder->N_N_x;i++) {
    GP_LDPCEncoder->x[i]=(GP_LDPCEncoderStruct*)calloc(M,sizeof(GP_LDPCEncoderStruct));
    for(j=0;j<GP_LDPCEncoder->N_x[i];j++) initGP_LDPCEncoderStruct(&GP_LDPCEncoder->x[i][j]);
  }
}

// Free a double array of GP_LDPCEncoderStruct's
void freeDoubleArrayGP_LDPCEncoderStruct (doubleArrayGP_LDPCEncoderStruct *GP_LDPCEncoder) {
  int i;
  for (i=0;i<GP_LDPCEncoder->N_N_x;i++) {
    if (GP_LDPCEncoder->x[i]!=NULL) free(GP_LDPCEncoder->x[i]);
  }
  free(GP_LDPCEncoder->N_x);GP_LDPCEncoder->N_x=NULL;
  free(GP_LDPCEncoder->x);GP_LDPCEncoder->x=NULL;
}

// Print arrayGP_LDPCEncoderStruct
void printDoubleArrayGP_LDPCEncoderStruct (doubleArrayGP_LDPCEncoderStruct *GP_LDPCEncoder, char *name, int index, int pre) {
}

// Plot function generates any plots associated with the 
// structure
void plotGP_LDPCEncoderStruct (GP_LDPCEncoderStruct *GP_LDPCEncoder, const char *filename) {
}

// All the data from all the modules is packed into an
// array of uint8_vectors for saving. One uint8_vector per module. 
// Each uint8_vector contains a stringified version of the
// data in the struct. uint8_vectors are then written to and 
// read from disk by the SWRC_saveuint8_vector and SWRC_loaduint8_vector 
// functions. This function packs struct data into a uint_8_vector
void packGP_LDPCEncoderStruct (GP_LDPCEncoderStruct *GP_LDPCEncoder, uint8_vector *cfgFile) {
  int i, j;
  //Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
  // Pack int **H
  for (i=0;i<(GP_LDPCEncoder->N_row_H);i++) {
    SWRC_packToUint8((uint8_t*)GP_LDPCEncoder->H[i],(GP_LDPCEncoder->N_col_H),sizeof(int),cfgFile);
  }
  // Pack int N
  SWRC_packToUint8((uint8_t*)&GP_LDPCEncoder->N,1,sizeof(int),cfgFile);
  // Pack int M
  SWRC_packToUint8((uint8_t*)&GP_LDPCEncoder->M,1,sizeof(int),cfgFile);
  // Pack int K
  SWRC_packToUint8((uint8_t*)&GP_LDPCEncoder->K,1,sizeof(int),cfgFile);
  // Pack double R
  SWRC_packToUint8((uint8_t*)&GP_LDPCEncoder->R,1,sizeof(double),cfgFile);
  //Fields automatically included in every module that request $args{i}
  // Pack uint8_t trainFlag
  SWRC_packToUint8((uint8_t*)&GP_LDPCEncoder->trainFlag,1,sizeof(uint8_t),cfgFile);
  // Pack long int N_train
  SWRC_packToUint8((uint8_t*)&GP_LDPCEncoder->N_train,1,sizeof(long int),cfgFile);
  // Pack long int i_train
  SWRC_packToUint8((uint8_t*)&GP_LDPCEncoder->i_train,1,sizeof(long int),cfgFile);
  // Pack long unsigned int numberOfMult
  SWRC_packToUint8((uint8_t*)&GP_LDPCEncoder->numberOfMult,1,sizeof(long unsigned int),cfgFile);
  // Pack double aveNoOfMultPerFrame
  SWRC_packToUint8((uint8_t*)&GP_LDPCEncoder->aveNoOfMultPerFrame,1,sizeof(double),cfgFile);
  // Pack long unsigned int numberOfAdd
  SWRC_packToUint8((uint8_t*)&GP_LDPCEncoder->numberOfAdd,1,sizeof(long unsigned int),cfgFile);
  // Pack double aveNoOfAddPerFrame
  SWRC_packToUint8((uint8_t*)&GP_LDPCEncoder->aveNoOfAddPerFrame,1,sizeof(double),cfgFile);
  // Pack long unsigned int numberOfComp
  SWRC_packToUint8((uint8_t*)&GP_LDPCEncoder->numberOfComp,1,sizeof(long unsigned int),cfgFile);
  // Pack double aveNoOfCompPerFrame
  SWRC_packToUint8((uint8_t*)&GP_LDPCEncoder->aveNoOfCompPerFrame,1,sizeof(double),cfgFile);
  // Pack double simTime
  SWRC_packToUint8((uint8_t*)&GP_LDPCEncoder->simTime,1,sizeof(double),cfgFile);
  // Pack double aveSimTimePerFrame
  SWRC_packToUint8((uint8_t*)&GP_LDPCEncoder->aveSimTimePerFrame,1,sizeof(double),cfgFile);
  // Pack long unsigned int numberOfCalls
  SWRC_packToUint8((uint8_t*)&GP_LDPCEncoder->numberOfCalls,1,sizeof(long unsigned int),cfgFile);
}

// After loading the data back from a .cfg file, the data is unpacked
// back into the struct with this function.
void unpackGP_LDPCEncoderStruct (GP_LDPCEncoderStruct *GP_LDPCEncoder, uint8_vector *cfgFile) {
  int i;
  freeGP_LDPCEncoderStruct(GP_LDPCEncoder);
  // Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
  // Unpack int **H
  if ((GP_LDPCEncoder->N_row_H)!=0) {
    GP_LDPCEncoder->H=(int**) calloc((GP_LDPCEncoder->N_row_H),sizeof(int*));
    for (i=0;i<(GP_LDPCEncoder->N_row_H);i++) {
      GP_LDPCEncoder->H[i]=(int*) calloc((GP_LDPCEncoder->N_col_H),sizeof(int));
      SWRC_unpackFromUint8((uint8_t*)GP_LDPCEncoder->H[i],(GP_LDPCEncoder->N_col_H),sizeof(int),cfgFile);
    }
  }
  // Unpack int N
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCEncoder->N,1,sizeof(int),cfgFile);
  // Unpack int M
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCEncoder->M,1,sizeof(int),cfgFile);
  // Unpack int K
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCEncoder->K,1,sizeof(int),cfgFile);
  // Unpack double R
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCEncoder->R,1,sizeof(double),cfgFile);
  // Fields automatically included in every module that request $args{i}
  // Unpack uint8_t trainFlag
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCEncoder->trainFlag,1,sizeof(uint8_t),cfgFile);
  // Unpack long int N_train
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCEncoder->N_train,1,sizeof(long int),cfgFile);
  // Unpack long int i_train
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCEncoder->i_train,1,sizeof(long int),cfgFile);
  // Unpack long unsigned int numberOfMult
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCEncoder->numberOfMult,1,sizeof(long unsigned int),cfgFile);
  // Unpack double aveNoOfMultPerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCEncoder->aveNoOfMultPerFrame,1,sizeof(double),cfgFile);
  // Unpack long unsigned int numberOfAdd
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCEncoder->numberOfAdd,1,sizeof(long unsigned int),cfgFile);
  // Unpack double aveNoOfAddPerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCEncoder->aveNoOfAddPerFrame,1,sizeof(double),cfgFile);
  // Unpack long unsigned int numberOfComp
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCEncoder->numberOfComp,1,sizeof(long unsigned int),cfgFile);
  // Unpack double aveNoOfCompPerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCEncoder->aveNoOfCompPerFrame,1,sizeof(double),cfgFile);
  // Unpack double simTime
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCEncoder->simTime,1,sizeof(double),cfgFile);
  // Unpack double aveSimTimePerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCEncoder->aveSimTimePerFrame,1,sizeof(double),cfgFile);
  // Unpack long unsigned int numberOfCalls
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCEncoder->numberOfCalls,1,sizeof(long unsigned int),cfgFile);
}

// Pack the contents of arrayGP_LDPCEncoderStruct to a uint8_vector
void packArrayGP_LDPCEncoderStruct (arrayGP_LDPCEncoderStruct *GP_LDPCEncoder, uint8_vector *cfgFile) {
  SWRC_packToUint8((uint8_t*)&GP_LDPCEncoder->N_x,1,sizeof(long unsigned int),cfgFile);
  SWRC_packToUint8((uint8_t*)GP_LDPCEncoder->x,GP_LDPCEncoder->N_x,sizeof(GP_LDPCEncoderStruct),cfgFile);
}

// Unpack the contents of arrayGP_LDPCEncoderStruct from a uint8_vector.
void unpackArrayGP_LDPCEncoderStruct (arrayGP_LDPCEncoderStruct *GP_LDPCEncoder, uint8_vector *cfgFile) {
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCEncoder->N_x,1,sizeof(long unsigned int),cfgFile);
  GP_LDPCEncoder->x = (GP_LDPCEncoderStruct*)realloc(GP_LDPCEncoder->x,GP_LDPCEncoder->N_x*sizeof(GP_LDPCEncoderStruct));
  SWRC_unpackFromUint8((uint8_t*)GP_LDPCEncoder->x,GP_LDPCEncoder->N_x,sizeof(GP_LDPCEncoderStruct),cfgFile);
}

// Pack the contents of doubleArrayGP_LDPCEncoderStruct to a uint8_vector
void packDoubleArrayGP_LDPCEncoderStruct (doubleArrayGP_LDPCEncoderStruct *GP_LDPCEncoder, uint8_vector *cfgFile) {
  int i;
  SWRC_packToUint8((uint8_t*)&GP_LDPCEncoder->N_N_x,1,sizeof(long unsigned int),cfgFile);
  SWRC_packToUint8((uint8_t*)GP_LDPCEncoder->N_x,GP_LDPCEncoder->N_N_x,sizeof(long unsigned int),cfgFile);
  for (i=0;i<GP_LDPCEncoder->N_N_x;i++) 
    SWRC_packToUint8((uint8_t*)GP_LDPCEncoder->x[i],GP_LDPCEncoder->N_x[i],sizeof(GP_LDPCEncoderStruct),cfgFile);
}

// Unpack the contents of doubleArrayGP_LDPCEncoderStruct from a uint8_vector
void unpackDoubleArrayGP_LDPCEncoderStruct (doubleArrayGP_LDPCEncoderStruct *GP_LDPCEncoder, uint8_vector *cfgFile) {
  int i;
  SWRC_unpackFromUint8((uint8_t*)&GP_LDPCEncoder->N_N_x,1,sizeof(long unsigned int),cfgFile);
  // allocate memory for and unpack GP_LDPCEncoder->N_GP_LDPCEncoder
  GP_LDPCEncoder->N_x=(long unsigned int*) realloc(GP_LDPCEncoder->N_x,GP_LDPCEncoder->N_N_x*sizeof(long unsigned int));
  SWRC_unpackFromUint8((uint8_t*)GP_LDPCEncoder->N_x,GP_LDPCEncoder->N_N_x,sizeof(long unsigned int),cfgFile);
  // allocate memory for GP_LDPCEncoder->GP_LDPCEncoder
  GP_LDPCEncoder->x=(GP_LDPCEncoderStruct**)realloc(GP_LDPCEncoder->x,GP_LDPCEncoder->N_N_x*sizeof(GP_LDPCEncoderStruct*));
  for (i=0;i<GP_LDPCEncoder->N_N_x;i++) {
    SWRC_unpackFromUint8((uint8_t*)GP_LDPCEncoder->x[i],GP_LDPCEncoder->N_x[i],sizeof(GP_LDPCEncoderStruct),cfgFile);
  }
}

// Function for loading the struct
int loadGP_LDPCEncoderStruct (GP_LDPCEncoderStruct *GP_LDPCEncoder, char *filename) {
}

// Function for saving the struct
void saveGP_LDPCEncoderStruct (GP_LDPCEncoderStruct *GP_LDPCEncoder, char *filename) {
}

// Set parameters (fields) in the structure
// Change the values of fields in the structure
void setParmGP_LDPCEncoderStruct (GP_LDPCEncoderStruct *GP_LDPCEncoder, char *arg) {
  int i;
  SWRC_removeSpaces(arg);
  if (SWRC_readSingleArgumentFromString(arg,"N",&GP_LDPCEncoder->N,"%d")==1) {
    printf("N=%d\n",GP_LDPCEncoder->N);
  }
  // if (SWRC_readSingleArgumentFromString(arg,"M",&GP_LDPCEncoder->M,"%d")==1) {
  //   printf("M=%d\n",GP_LDPCEncoder->M);
  // }
  if (SWRC_readSingleArgumentFromString(arg,"K",&GP_LDPCEncoder->K,"%d")==1) {
    printf("K=%d\n",GP_LDPCEncoder->K);
  }
  // if (SWRC_readSingleArgumentFromString(arg,"N_row_H",&GP_LDPCEncoder->N_row_H,"%d")==1) {
  //   printf("N_row_H=%d\n",GP_LDPCEncoder->N_row_H);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"N_col_H",&GP_LDPCEncoder->N_col_H,"%d")==1) {
  //   printf("N_col_H=%d\n",GP_LDPCEncoder->N_col_H);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"R",&GP_LDPCEncoder->R,"%lf")==1) {
  //   printf("R=%lf\n",GP_LDPCEncoder->R);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"trainFlag",&GP_LDPCEncoder->trainFlag,"%"SCNu8"")==1) {
  //   printf("trainFlag=%"SCNu8"\n",GP_LDPCEncoder->trainFlag);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"N_train",&GP_LDPCEncoder->N_train,"%ld")==1) {
  //   printf("N_train=%ld\n",GP_LDPCEncoder->N_train);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"i_train",&GP_LDPCEncoder->i_train,"%ld")==1) {
  //   printf("i_train=%ld\n",GP_LDPCEncoder->i_train);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfMult",&GP_LDPCEncoder->numberOfMult,"%lu")==1) {
  //   printf("numberOfMult=%lu\n",GP_LDPCEncoder->numberOfMult);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveNoOfMultPerFrame",&GP_LDPCEncoder->aveNoOfMultPerFrame,"%lf")==1) {
  //   printf("aveNoOfMultPerFrame=%lf\n",GP_LDPCEncoder->aveNoOfMultPerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfAdd",&GP_LDPCEncoder->numberOfAdd,"%lu")==1) {
  //   printf("numberOfAdd=%lu\n",GP_LDPCEncoder->numberOfAdd);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveNoOfAddPerFrame",&GP_LDPCEncoder->aveNoOfAddPerFrame,"%lf")==1) {
  //   printf("aveNoOfAddPerFrame=%lf\n",GP_LDPCEncoder->aveNoOfAddPerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfComp",&GP_LDPCEncoder->numberOfComp,"%lu")==1) {
  //   printf("numberOfComp=%lu\n",GP_LDPCEncoder->numberOfComp);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveNoOfCompPerFrame",&GP_LDPCEncoder->aveNoOfCompPerFrame,"%lf")==1) {
  //   printf("aveNoOfCompPerFrame=%lf\n",GP_LDPCEncoder->aveNoOfCompPerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"simTime",&GP_LDPCEncoder->simTime,"%lf")==1) {
  //   printf("simTime=%lf\n",GP_LDPCEncoder->simTime);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveSimTimePerFrame",&GP_LDPCEncoder->aveSimTimePerFrame,"%lf")==1) {
  //   printf("aveSimTimePerFrame=%lf\n",GP_LDPCEncoder->aveSimTimePerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfCalls",&GP_LDPCEncoder->numberOfCalls,"%lu")==1) {
  //   printf("numberOfCalls=%lu\n",GP_LDPCEncoder->numberOfCalls);
  // }
  if (*arg!='\0') {
    printf("GP_LDPCEncoder module: Remaining unknown parms in arg list:%s\n Please correct and run again.\n",arg);exit(-1);
  }
}

// A command comes from the user
// This function processes and executes the command
// some commands need a signal to operate on, which is
// passed via the signalStruct. 
void processCommandGP_LDPCEncoder (GP_LDPCEncoderStruct *GP_LDPCEncoder, signalStruct *signal, const char *command) {
  char commandParameter[400];
  int i;
  printf("processCommandGP_LDPCEncoder:%s\n",command);
  for(i=0;i<400 && i<strlen(command);) {
    if (SWRC_matchCommand(command,"load",&i,commandParameter,400)==1) {
      loadGP_LDPCEncoderStruct(GP_LDPCEncoder,commandParameter);
      continue;
    }

    if (SWRC_matchCommand(command,"print",&i,commandParameter,400)==1) {
      printGP_LDPCEncoderStruct(GP_LDPCEncoder,"GP_LDPCEncoder",0,0);
      continue;
    }

    if (SWRC_matchCommand(command,"setParm",&i,commandParameter,400)==1) {
      setParmGP_LDPCEncoderStruct(GP_LDPCEncoder,commandParameter);
      continue;
    }

    if (SWRC_matchCommand(command,"checkParm",&i,commandParameter,400)==1) {
      checkParametersGP_LDPCEncoder(GP_LDPCEncoder);
      continue;
    }

    if (SWRC_matchCommand(command,"precomp",&i,commandParameter,400)==1) {
      precompGP_LDPCEncoder(GP_LDPCEncoder);
      continue;
    }

    if (SWRC_matchCommand(command,"postcomp",&i,commandParameter,400)==1) {
      postcompGP_LDPCEncoder(GP_LDPCEncoder,0);
      continue;
    }

    if (SWRC_matchCommand(command,"help",&i,commandParameter,400)==1) {
      helpCommandGP_LDPCEncoder(0);
      continue;
    }

    if (SWRC_matchCommand(command,"run",&i,commandParameter,400)==1) {
      runGP_LDPCEncoder(GP_LDPCEncoder, signal);
      continue;
    }

    printf("processCommandGP_LDPCEncoder: Unknown command:%s\n",&command[i]);
    break;
  }
}

// Provides instructions on the commands that this module is able to process.
void helpCommandGP_LDPCEncoder (int index) {
  printf("Commands recognized by %d:GP_LDPCEncoderStruct:\n",index);
  printf("  \"print();\"        : print the GP_LDPCEncoderStruct fields\n");
  printf("  \"setParm(arg);\"   : set the GP_LDPCEncoderStruct fields\n");
  printf("  \"help();\"         : display this help screen\n");
}

// Check that all the parameters needed to run the simulation are present.
// Uncomment any/all variables that _need_ to be present for the simulation to run.
int checkParametersGP_LDPCEncoder (GP_LDPCEncoderStruct *GP_LDPCEncoder) {
  int output=0;
  //if (GP_LDPCEncoder->H==NULL) {output++;printf("GP_LDPCEncoder->H needed, but not set\n");}
  //if (GP_LDPCEncoder->N==0) {output++;printf("GP_LDPCEncoder->N needed, but not set\n");}
  //if (GP_LDPCEncoder->M==0) {output++;printf("GP_LDPCEncoder->M needed, but not set\n");}
  //if (GP_LDPCEncoder->K==0) {output++;printf("GP_LDPCEncoder->K needed, but not set\n");}
  //if (GP_LDPCEncoder->R==0.0) {output++;printf("GP_LDPCEncoder->R needed, but not set\n");}
  //if (GP_LDPCEncoder->trainFlag==0) {output++;printf("GP_LDPCEncoder->trainFlag needed, but not set\n");}
  //if (GP_LDPCEncoder->N_train==0) {output++;printf("GP_LDPCEncoder->N_train needed, but not set\n");}
  //if (GP_LDPCEncoder->i_train==0) {output++;printf("GP_LDPCEncoder->i_train needed, but not set\n");}
  //if (GP_LDPCEncoder->numberOfMult==0) {output++;printf("GP_LDPCEncoder->numberOfMult needed, but not set\n");}
  //if (GP_LDPCEncoder->aveNoOfMultPerFrame==0.0) {output++;printf("GP_LDPCEncoder->aveNoOfMultPerFrame needed, but not set\n");}
  //if (GP_LDPCEncoder->numberOfAdd==0) {output++;printf("GP_LDPCEncoder->numberOfAdd needed, but not set\n");}
  //if (GP_LDPCEncoder->aveNoOfAddPerFrame==0.0) {output++;printf("GP_LDPCEncoder->aveNoOfAddPerFrame needed, but not set\n");}
  //if (GP_LDPCEncoder->numberOfComp==0) {output++;printf("GP_LDPCEncoder->numberOfComp needed, but not set\n");}
  //if (GP_LDPCEncoder->aveNoOfCompPerFrame==0.0) {output++;printf("GP_LDPCEncoder->aveNoOfCompPerFrame needed, but not set\n");}
  //if (GP_LDPCEncoder->simTime==0.0) {output++;printf("GP_LDPCEncoder->simTime needed, but not set\n");}
  //if (GP_LDPCEncoder->aveSimTimePerFrame==0.0) {output++;printf("GP_LDPCEncoder->aveSimTimePerFrame needed, but not set\n");}
  //if (GP_LDPCEncoder->numberOfCalls==0) {output++;printf("GP_LDPCEncoder->numberOfCalls needed, but not set\n");}
  return(output);
}

void positive_matrix(GP_LDPCEncoderStruct *GP_LDPCEncoder, int row_B, int column_B, int row_H, int column_H, int expFactor, int B[row_B][column_B], int H[row_H][column_H], int pK, int pM)
{

  int i,j;
  for (i=(pK*expFactor);i<(pK*expFactor)+expFactor;i++)
    {
      for (j=(pM*expFactor);j<(pM*expFactor)+expFactor;j++)
	{
	  if ((i+1)%5==(j+1)%5)
	    {
	      H[i][j]=1;
	    }
	  else
	    {
	      H[i][j]=0;
	    }
	}
    }
  int n, temp;
  int b=B[pK][pM];
  if (b>0)
    {
      for (n=0;n<b;n++)
	{
	  for (i=(pK*expFactor);i<(pK*expFactor)+expFactor;i++)
	    {
	      temp=H[i][((pM*expFactor)+expFactor)-1];
	      for (j=((pM*expFactor)+expFactor)-1;j>(pM*expFactor);j--)
		{
		  H[i][j]=H[i][j-1];
		}
	      H[i][(pM*expFactor)]= temp;
	    }
	}
    }
}


void negative_matrix(GP_LDPCEncoderStruct *GP_LDPCEncoder, int row_B, int column_B, int row_H, int column_H, int expFactor, int B[row_B][column_B], int H[row_H][column_H], int nK, int nM)
{
  int i,j;
  for (i=(nK*expFactor);i<(nK*expFactor)+expFactor;i++)
    {
      for (j=(nM*expFactor);j<(nM*expFactor)+expFactor;j++)
	{
	  H[i][j]=0;
	  //To check result of negative numbers
	  // printf("H[%d][%d][%d][%d]: %d\n",k,m,i,j, H[k][m][i][j]);
	}
    }
}

void pchk2alist(GP_LDPCEncoderStruct *GP_LDPCEncoder, int row_B, int column_B, int row_H, int column_H, int expFactor, int H[row_H][column_H]){

  int i,j,k;
  
  FILE* f;
  f=fopen("H_matrix.txt", "r"); //reading dense matrix

  if (!feof(f))
    {
      for (i=0;i< row_H ;i++)
        {
	  for (j=0;j< column_H ;j++)
            {
	      fscanf(f, "%d",&H[i][j]);
               
            }
        }
    }
  fclose(f);
   

  //Write size of H matrix
  FILE * file;
  file = fopen ("1_2_5.alist", "w+");
  fprintf(file, "%d %d\n", row_H, column_H);
  int sum = 0;
  //Sum matrix in each row (Weight in row)
  int row_weight [row_B*expFactor];
  int row_temp [row_B*expFactor];

  for (i=0;i<row_H;i++)
    {
      for (j=0;j<column_H;j++)
	{
	  if (H[i][j] == 1)
	    {
	      sum+=1;
	    }
	   
	}
      //printf("%d ",sum);
      //fprintf(file, "%d ", sum);
      row_weight[i] = sum;
      row_temp[i] = sum;
      sum = 0; //reset before new row
    }

   
  //Sum matrix in each column (Weight in column)
  int column_weight [column_B*expFactor];
  int column_temp [column_B*expFactor];

  for (i=0; i<column_H; i++)
    {
      for (j=0; j<row_H; j++)
	{
	  if (H[j][i] == 1)
	    {
	      sum+=1;
	    }
	   
	}
      //printf("%d ",sum);
      //fprintf(file, "%d ", sum);
      column_weight[i] = sum;
      column_temp[i] = sum;
      sum = 0; //reset before new column      
    }

  //Find max weight
  for (i=0; i<row_H; i++)
    {
      if (row_temp[0] < row_temp[i])
	{
	  row_temp[0] = row_temp[i];
	}
    }

  for (i=0; i<column_H; i++)
    {
      if (column_temp[0] < column_temp[i])
	{
	  column_temp[0] = column_temp[i];
	}
    }

  //Writing max weight to file
  fprintf(file,"%d %d\n", row_temp[0], column_temp[0]);

  //Writing weight in each row and column to file
  for (i=0; i<row_H; i++)
    {
      fprintf(file, "%d ", row_weight[i]);
    }
     
  fprintf(file, "\n");

  for (i=0; i<column_H; i++)
    {
      fprintf(file, "%d ", column_weight[i]);
    }

  fprintf(file, "\n");

  //Find max number of ones in column
  int num_c=0, num_r=0;
     
  for (i=0; i< (1); i++)
    {
      for (j=0; j <column_H; j++)
	{
	  if (H[i][j] != 0)
	    {			        
	      num_c+=1;
	    }
	   
		
	}
      //printf("%d ",num);
    }

  for (i=0; i< (1); i++)
    {
      for (j=0; j <row_H; j++)
	{
	  if (H[j][i] != 0)
	    {			        
	      num_r+=1;
	    }		
	}
      //printf("\n%d\n ",num_r);
    }
	 
  //Writing column index of non-zero elements in each row
  int pos[]={}, pos_temp[]={0};
  int x=0;
  for (i=0; i<row_H; i++)
    {
      for (j=0; j <column_H; j++)
	{
	  if (H[i][j] != 0)
	    {
	      pos[x] = j+1;
	      //pos_temp[x] = pos[x];
	      //printf(" %d",pos[x]);
	      fprintf(file, "%d ", pos[x]);
	      //num+=1;
	    }
	   
	  //printf("%d ",pos_temp[0]);
	}
	   

	 
      //printf("\n");
      fprintf(file, "\n");
      x=0;
    }

     
  int pos2[]={};
  for (i=0; i<column_H; i++)
    {
      for (j=0; j <row_H; j++)
	{
	  if (H[j][i] != 0)
	    {
	      pos2[x] = j+1;		
	      fprintf(file, "%d ", pos2[x]);
	    }
	  
	}
      //printf("\n");
      fprintf(file, "\n");
    }
     
  fclose(file);
}

// Precomputation done just prior to the main for loop
// iterating the BER/FER are put into this subroutine
void precompGP_LDPCEncoder (GP_LDPCEncoderStruct *GP_LDPCEncoder) {
  GP_LDPCEncoder->i_train=0;
  GP_LDPCEncoder->numberOfMult=0;
  GP_LDPCEncoder->aveNoOfMultPerFrame=0.0;
  GP_LDPCEncoder->numberOfAdd=0;
  GP_LDPCEncoder->aveNoOfAddPerFrame=0.0;
  GP_LDPCEncoder->numberOfComp=0;
  GP_LDPCEncoder->aveNoOfCompPerFrame=0.0;
  GP_LDPCEncoder->simTime=0.0;
  GP_LDPCEncoder->aveSimTimePerFrame=0.0;
  GP_LDPCEncoder->numberOfCalls=0;

  //generate parity check matrix and convert to alist format
  int N = GP_LDPCEncoder->N;
  int K = GP_LDPCEncoder->K;
  GP_LDPCEncoder->N_row_H=N - K;
  int row_H = GP_LDPCEncoder->N_row_H;
  int column_H = N;
  int expFactor= 5;
  int column_msg_B= K/expFactor;
  int row_B, column_B;
  
  if (N==340 || N==260)
    {
      row_B=(N-K)/expFactor;
      column_B=N/expFactor;
      if (row_B==46 && column_B==68)
	{
	  column_msg_B=22;
	}
      else if (row_B==42 && column_B==52)
	{
	  column_msg_B=10;
	}
    }
  else
    {
      printf("Try again.");
      exit(-1);
    }
  
  int B[row_B][column_B];
  int k, m, i;
  int H[row_H][column_H];
  //Import base matrix from txt file
  FILE* f;
  if (row_B==46 && column_B==68)
    {
      f=fopen("NR_1_2_5.txt", "r");
      if (!feof(f))
	{
	  for (k=0;k<row_B;k++)
	    {
	      for (m=0;m<column_B;m++)
		{
		  fscanf(f, "%d",&B[k][m]);
		  // printf("B[%d][%d]: %d\n", k, j, B[k][j]);
		}
	    }
	}
      fclose(f);
    }
  else if (row_B==42 && column_B==52)
    {
      f=fopen("NR_2_2_5.txt", "r");
      if (!feof(f))
	{
	  for (k=0;k<row_B;k++)
	    {
	      for (m=0;m<column_B;m++)
		{
		  fscanf(f, "%d",&B[k][m]);
		  // printf("B[%d][%d]: %d\n", k, j, B[k][j]);
		}
	    }
	}
      fclose(f);
    }
  
  //Check whether the elements is positive, negative or zero
  for (k=0;k<row_B;k++)
    {
      for (m=0;m<column_B;m++)
        {
 	  if (B[k][m]<0)
 	    {
	      int nK=k;
	      int nM=m;
	      negative_matrix(GP_LDPCEncoder, row_B, column_B, row_H, column_H, expFactor, B, H, nK, nM);
 	    }
	  else
	    {
	      int pK=k;
	      int pM=m;
	      positive_matrix(GP_LDPCEncoder, row_B, column_B, row_H, column_H, expFactor, B, H, pK, pM);
	      
 	    }
 	}
    }

  //convert to alist
  pchk2alist(GP_LDPCEncoder, row_B, column_B, row_H, column_H, expFactor, H);
  
    printf("Done write to alist\n");
}

// postComputation, such as freeing up any memory, done after
// the iteration of the BER/FER are put into this subroutine
void postcompGP_LDPCEncoder (GP_LDPCEncoderStruct *GP_LDPCEncoder, char finishedFlag) {

  GP_LDPCEncoder->aveNoOfMultPerFrame=(double)GP_LDPCEncoder->numberOfMult/GP_LDPCEncoder->numberOfCalls;
  GP_LDPCEncoder->aveNoOfAddPerFrame=(double)GP_LDPCEncoder->numberOfAdd/GP_LDPCEncoder->numberOfCalls;
  GP_LDPCEncoder->aveNoOfCompPerFrame=(double)GP_LDPCEncoder->numberOfComp/GP_LDPCEncoder->numberOfCalls;
  GP_LDPCEncoder->aveSimTimePerFrame=(double)GP_LDPCEncoder->simTime/GP_LDPCEncoder->numberOfCalls;
}

// Function called prior to training. Zero out statistics matrices,
// set the i_train index to zero etc...
void pretrainGP_LDPCEncoder (GP_LDPCEncoderStruct *GP_LDPCEncoder) {
  GP_LDPCEncoder->i_train=0;
}

// Function called after training. Free allocated memory etc...
void posttrainGP_LDPCEncoder (GP_LDPCEncoderStruct *GP_LDPCEncoder) {
}

// Some modules have a training phase where modules before them are run
// and statistics collected so the module can run properly.
// This function performs the training for the module then 
// saved back to the .cfg file.
// Returns 1 if training is complete
// Returns 0 otherwise
int trainGP_LDPCEncoder (GP_LDPCEncoderStruct *GP_LDPCEncoder, signalStruct *signal) {
  if ((GP_LDPCEncoder->trainFlag&1)==1) { // Training complete, call the run function
    printf("Running GP_LDPCEncoder\n");
    runGP_LDPCEncoder(GP_LDPCEncoder,signal);
    return(1);
  } else {                 // Do the training
    printf("Training GP_LDPCEncoder %ld/%ld\n",GP_LDPCEncoder->i_train,GP_LDPCEncoder->N_train);
    // Accumulate the statistics
    GP_LDPCEncoder->i_train++;
    if (GP_LDPCEncoder->i_train>=GP_LDPCEncoder->N_train) { // Statistics accumulated, post-training computation
      GP_LDPCEncoder->trainFlag=1;
    }
    return(0);
  }
}

// Contribute the fields to the berResultStruct that will be 
// printed in the berResult file. Every module contributes
// its own fields. User has to choose the fields to be saved
// using pushBerResultField() once per field to be added
void initBerResultStructGP_LDPCEncoder (GP_LDPCEncoderStruct *GP_LDPCEncoder,berResultStruct *berResult) {
  //pushBerResultField(berResult,"N","int","%1d",&GP_LDPCEncoder->N);
  //pushBerResultField(berResult,"M","int","%1d",&GP_LDPCEncoder->M);
  //pushBerResultField(berResult,"K","int","%1d",&GP_LDPCEncoder->K);
  //pushBerResultField(berResult,"R","double","%1lf",&GP_LDPCEncoder->R);
  //pushBerResultField(berResult,"trainFlag","uint8_t","%9"SCNu8"",&GP_LDPCEncoder->trainFlag);
  //pushBerResultField(berResult,"N_train","long int","%7ld",&GP_LDPCEncoder->N_train);
  //pushBerResultField(berResult,"i_train","long int","%7ld",&GP_LDPCEncoder->i_train);
  //pushBerResultField(berResult,"numberOfMult","long unsigned int","%12lu",&GP_LDPCEncoder->numberOfMult);
  //pushBerResultField(berResult,"aveNoOfMultPerFrame","double","%19lf",&GP_LDPCEncoder->aveNoOfMultPerFrame);
  //pushBerResultField(berResult,"numberOfAdd","long unsigned int","%11lu",&GP_LDPCEncoder->numberOfAdd);
  //pushBerResultField(berResult,"aveNoOfAddPerFrame","double","%18lf",&GP_LDPCEncoder->aveNoOfAddPerFrame);
  //pushBerResultField(berResult,"numberOfComp","long unsigned int","%12lu",&GP_LDPCEncoder->numberOfComp);
  //pushBerResultField(berResult,"aveNoOfCompPerFrame","double","%19lf",&GP_LDPCEncoder->aveNoOfCompPerFrame);
  //pushBerResultField(berResult,"simTime","double","%7lf",&GP_LDPCEncoder->simTime);
  //pushBerResultField(berResult,"aveSimTimePerFrame","double","%18lf",&GP_LDPCEncoder->aveSimTimePerFrame);
  //pushBerResultField(berResult,"numberOfCalls","long unsigned int","%13lu",&GP_LDPCEncoder->numberOfCalls);
}

int syndrome(int codeword[], int row_B, int column_B, int row_H, int column_H,  int expFactor, int h[row_H][column_H]){

  //This section calculates the syndrome to check validity of final codeword
  //If syndrome is 0, it is a valid codeword
  //If syndrome is 1, it is an invalid codeword

  int multiply[column_H], sum_temp[]={};
  int synd[row_H];
  int sum;
  int i,j,k,m;
  for (i=0; i<row_H; i++)
    {
      for (j=0; j<column_H; j++)
	{
	  multiply[j] = h[i][j] * codeword[j];
	 	  
	  //printf("\ni: %d ",i);
	}
      //printf("\n\n");
      sum = 0;

      for (k=0; k<column_H; k++)
	{
	  sum = sum + multiply[k]; //Updating
	}

      synd[i] = sum%2;   //perform modulo 2
    }
  int ss=0;
  for(i=0; i<row_H; i++)
    {
      ss+=synd[i];
    }

  // printf("\n\n%d ",ss);
  return ss;    
}

//Function to print codeword
void print_codeword(int codeword[], int N){

  int i;
  
  printf("\n\n--------------------codeword:-------------\n\n");
  for(i=0; i<N; i++)
    {
      printf("%d ", codeword[i]);   
    }

  printf("\n\n-------------Codeword is printed---------------\n\n");
}

//Appending final non-shifted p1 to codeworf
void append_p1(int codeword[], int parity[], int expFactor, int K, int N){
  //append p1 to codeword
  int i;
  for(i=0; i<expFactor; i++)
    {
      codeword[i+K] = parity[i];      
      //printf("\n%d",parity[i]); 
    }
  //print_codeword();
}

void rotating_p1(int start, int end, int parity[]){

  while (start < end)
    {
      int temp = parity[start];
      parity[start] = parity[end];
      parity[end] = temp;
      start++;
      end--;
    }
}

//Function to shift p1 and get original p1 bits
void shifting_p1(int n, int z, int codeword[], int parity[], int expFactor, int K, int N){

  rotating_p1(0, z-1, parity);
  rotating_p1(0, n-1, parity);
  rotating_p1(n, z-1, parity);
  append_p1(codeword, parity, expFactor, K, N);
}


void get_parity(int newInput[], int codeword[], int parity[], int expFactor, int row_B, int column_B, int column_msg_B, int N, int K, int H[row_B][column_B][expFactor][expFactor]){

  int m, k, i, j, r, b, q, z=expFactor, sum, bb;
  int product[]={}, prodIM[row_B*z], multiply[z], temp[z], sum_temp[z];
  int B[row_B][column_B];
  //Import base matrix from txt file
  FILE* f;
  f=fopen("NR_1_2_5.txt", "r");
  if (!feof(f))
    {
      for (k=0;k<row_B;k++)
        {
	  for (m=0;m<column_B;m++)
            {
	      fscanf(f, "%d",&B[k][m]);
	      // printf("B[%d][%d]: %d\n", k, j, B[k][j]);
            }
        }
    }
  fclose(f);
  
  //-------------------P1------------------//
  
  //reset parity array
  for(i=0; i<z; i++)
    {
      parity[i]=0;  //temp
      sum_temp[i] = 0;
    }

  //Finding p1
  for(m=0; m<column_msg_B; m++) //1st x col of H (msg part)
    {
      for(k=0; k<4; k++) //1st 4 rows of B
	{
	  //printf("\nH Col %d ",m);
	  // printf("\nH Row %d ",k);
	  for(i=0; i<z; i++) //First I col... got z bits
	    {
	      //printf("\nI col %d:  ",i);
	      
	      for(j=0; j<z; j++) //First I row... got z bits
		{
		  //printf("%d ",m);
		  
		  temp[j] = newInput[j + m*z];
		      
		  multiply[j] = (temp[j] * H[k][m][i][j] );
	     
		  //printf(" %d", H[k][m][i][j]);
		  //printf("\n");		  		  
		}//j

	      //printf("\n\n");
	      int sum=0;
	      for(r=0; r<z; r++)
	      	{
		  sum = sum + multiply[r]; //value of product of every I*m
	        		
	      	}
	       	     
	      prodIM[i] = sum;
	      sum_temp[i] = sum_temp[i] + prodIM[i];
        			       	      
	    }//i
	  
	   
	}//k
    }//m

  for(int r=0; r<z; r++)
    {
	      
      parity[r] = sum_temp[r]%2;     //perform modulo 2 
      //printf("\n %d  ", parity[r]);
	   
    }
  
  //print_codeword();

  //printf("\n");

  //---------------Reshifting for P1--------------//
  //Now, need to shift the parity[] to get original bits (non-shifted version).
  //Getting value of p1 shift value from B
  int n;

  //Choose such that n is not -1.
  //If value in B is -1, then the H is z-by-z 0 matrix.
  //This causes the p1 to be all 0s because I*p1. Hence, need to choose non -1 value.
  if (B[1][column_msg_B] == -1)  
    { n = B[2][column_msg_B]; }
  else
    { n = B[1][column_msg_B]; }
  //printf("\n%d",z-n-1);
  shifting_p1( n, z, codeword, parity, expFactor, K, N); //shift by n to the right to get original parity bit

  //print_codeword();

    
    
  //-------P2 TO P4-------//

  //reset parity array
  for(i=0; i<z; i++)
    {
      parity[i]=0;
      sum_temp[i] = 0;
    }

  int  cword_temp[(column_B - column_msg_B - 1)*z];  //Initialise temp with size to avoid stack smashing
      
  //traverse by row and Hcolumn in codeword (all msg and one p)
  for(q=0; q<3; q++)  //Only until 3 rows 
    {
      for (m=0; m<column_msg_B+(q+1); m++ ) //all msg columns and p1 column
	{
	  //printf("\nm: %d \n",m);
	  for (k=0; k<(1+q); k++) 
	    {
	      //printf("\nk: %d ",k);
	    
	      for (i=0; i<z; i++) //I row
		{
		  for (j=0; j<z; j++) //I col
		    {

		      temp[j] = codeword[j + m*z];  //Assign temp to codeword of z index (z=expFactor)
		      //printf("\nm:%d k:%d i:%d   %d ",m,k,i,j+m*z);
		  
		      multiply[j] = (temp[j] * H[k][m][i][j] );  //Individual element multiplication of I and msg bits
		      //printf("%d ",  H[k][m][i][j]);
		      //printf("\nm: %d  k: %d i: %d  j: %d",m,k,i,j);
		    }//j

		  //printf("\n");
		  //SUm of individual products of I*msg
		  int sum=0;
		  for(r=0; r<z; r++)
		    {
		      sum = sum + multiply[r]; 		 
		    }
		  //printf(" \n %d ",sum);
	      
		  prodIM[i] = sum;
		  sum_temp[i] = sum_temp[i] + prodIM[i];  //Summing up values of I*msg to get parity bits
		  //printf(" \n %d  %d",m,sum_temp[i]);	           
		
		}//i
	    	    
		 //printf("\n");
	    }//k

	  //append parity bits to temp codeword
	  int w;
	  for(w=0; w<z; w++)
	    {
	      parity[w] = sum_temp[w];
	      cword_temp[w+q*z] = parity[w];
	      //printf("\nm: %d   %d ",m,w+q*z);
	      //printf("\nk:%d %d",k, cword_temp[(K+z) + w + q*z] );	    	    
	    }

	}//m

      //reset arrays before going to next loop
      int y;
      for(y=0; y<z; y++)
	{
	  parity[y]=0;
	  prodIM[y]=0;
	  sum_temp[y]=0;
	}

    }//q

  //Append cword_temp(containing p2-p4) to final codeword
  for(bb=0; bb<(3*z); bb++)
    {	    
      codeword[(K+z) + bb] = cword_temp[bb]%2; //perform modulo 2
      //printf("\n %d ",codeword[(K+z) + bb]);
	    
    }
  //print_codeword();
      
    
  //-------P5 TO PN-------//

  //reset parity array
  for(i=0; i<z; i++)
    {
      parity[i]=0;
    }

  int cword_temp2[(column_B - column_msg_B - 4)*z]; //fix stash smashing
           
  //traverse by row and Hcolumn in codeword (all msg bits and p1-p4)
  for(q=0; q<(column_B - column_msg_B - 4); q++)  //<length of parity bits from p5 to pn
    {
      for (m=0; m<column_msg_B+(q+4); m++ ) 
	{
	  //printf("\nm: %d\n ",m);
	  for (k=4+q; k<(5+q); k++) //Starts from 5th row
	    {
	      //printf("\nk: %d ",k);
	    
	      for (i=0; i<z; i++) 
		{
		  for (j=0; j<z; j++) 
		    {

		      temp[j] = codeword[j + m*z]; //Assign codeword to temp
		    
		      multiply[j] = (temp[j] * H[k][m][i][j] );  //Multiplying I(from H) with msg bits
		      //printf("%d ", j + m*z);
		      //printf("\nk: %d  m: %d",k,m);
		    }//j

		  //printf("\n");
		  //Continuing matrix multiplication by summing up the individual product
		  int sum=0;
		  for(r=0; r<z; r++)
		    {
		      sum = sum + multiply[r]; //value of product of every I*m		 
		    }
		  //printf(" \n %d ",sum);
	      
		  prodIM[i] = sum;
		  sum_temp[i] = sum_temp[i] + prodIM[i]; //Sum up all the I*msg components to find parity bits
		  //printf(" \nm:%d  %d",m,sum_temp[i]);	           
		
		}//i
	   
	    }//k

	  //append parity bits to temp codeword
	  int w;
	  for(w=0; w<z; w++)
	    {
	      parity[w] = sum_temp[w];
	      cword_temp2[w+q*z] = parity[w];
	      //printf("\nm: %d   %d ",m,w+q*z);
	      //printf("\nk:%d %d",k, cword_temp2[w + q*z] );	    	    
	    }

	}//m

      //Reset arrays before going into next loop
      int y; 
      for(y=0; y<z; y++)
	{
	  parity[y]=0;
	  prodIM[y]=0;
	  sum_temp[y]=0;
	}

    }//q

  //append cword_temp array to final codeword starting from p5 index
  for(bb=0; bb< (column_B - column_msg_B - 4) * z; bb++)
    {	    
      codeword[(K+4*z) + bb] = cword_temp2[bb]%2; //perform modulo 2 operation
      //printf("\n %d ",(K+4*z) + bb);	    
    }      
    
}//get_parity fx


void initialise_codeword(int N_input, int N_output, int newInput[], int codeword[])
{

  int i, j, k;
  

  for(i=0; i<N_output; i++)
    {
      codeword[i] = 0;
      // printf("Codeword[%d]: %d\n",i, codeword[i]);
    }

  //Append message or input bits to codeword array
  for (k=0; k<N_input; k++) //row index of input
    {
      // printf("Input[%d]: %d\n",k, newInput[k]);
      //printf("\n%d ",k);
      codeword[k] =newInput[k];
      // printf("Codeword input[%d]: %d\n",k, codeword[k]);
      //codeword_temp[k] = input[k];	 
    }

  // get_parity(input);
  
}

void alist2pchk(int row_B, int column_B, int row_H, int column_H, int expFactor, int h[row_H][column_H]){

  int maxinrow, junk, maxincol;
 
  int i, j;
  
  FILE * f;
  f = fopen ("1_2_5.alist", "r+");

  fscanf(f, "%d",&row_H);
  fscanf(f, "%d",&column_H);
  int Hnew[row_H][column_H];

  fscanf(f, "%d",&maxinrow); //19
  fscanf(f, "%d",&maxincol); //30


  //Number of 1s in each row
  int numbers_row[row_H], nummax[row_H];;

  for (i=0; i<row_H; i++)
    {
      fscanf(f, "%d",&numbers_row[i]);
      //printf("\n%d ",numbers[i]);
    }

  //For rows in alist
  for(i=0; i<row_H; i++)
    {
      nummax[i] = maxinrow;
    }

  int numbers_col[column_H];
  for (i=0; i<column_H; i++)
    {
      fscanf(f, "%d",&numbers_col[i]);
      //printf("\n%d ",junk2[i]);
    }

  int position[row_H][maxinrow];
  for (i=0; i<row_H; i++)  //initialise as all zeros
    {
      for (j=0; j<maxinrow; j++)
	{
	  position[i][j] = 0;
	}
    }

  //scan every row in alist H, in each row: put each element in each column
  for (i=0; i<row_H; i++)
    {
      for (j=0; j<numbers_row[i]; j++)
	{
	  fscanf(f, "%d",&position[i][j]);
	  //printf("%d ",position[i][j]);
	}
      //printf("\n");
    }
      
  //Initialise all 0 H
  for (i = 0; i<row_H; i++)
    {
      for (j=0; j<column_H; j++)
	{
	    
	  h[i][j]=0;
	      
	}
    }

  for (i = 0; i<row_H; i++)
    {
      for (j=0; j<numbers_row[i]; j++)
	{
	  //printf("%d ",position[i][j]);
	  h[i][(position[i][j])-1]=1;
	    	    	      
	}
      //printf("\n");
    }

  FILE * p;
  p = fopen ("PCHK generated by alist", "w+");

  for (i = 0; i<row_H; i++)
    {
      for (j=0; j<column_H; j++)
	{
	    
	  //printf("%d", h[i][j]);
	  fprintf(p,"%d ", h[i][j]);
	      
	}
      //printf("\n");
      fprintf(p,"\n");
    }
}


// Finally when everything is in place, the module must be
// run during the actual simulation. The code for running
// the module is in this function.
void runGP_LDPCEncoder (GP_LDPCEncoderStruct *GP_LDPCEncoder, signalStruct *signal) {

  clock_t beginTime, endTime;
  int N_input,N_output;
  uint8_t *input;
  uint8_t *output;
  beginTime=clock();
  printf("In function runGP_LDPCEncoder\n");
  // Allocate memory for 1 more signal. The output of this function should go there.
  // USER NEEDS TO EDIT: the LENGTH of the output vector and the TYPE of
  // the output vector 0=uint8_t, 1=char, 2=int, 3=unsigned int, 4=long unsigned int, 5=float, 6=double
  // The type of the input vector should also be set correctly by the USER.
  N_input  = signal->N[signal->N_N-1];        // Length of the input vector
  input    = (uint8_t*) signal->x[signal->N_N-1]; // Assign pointer to the input memory
  N_output = GP_LDPCEncoder->N; // Length of output vector
  output   = (uint8_t*) incrementByOneSignal(signal,N_output,0,"GP_LDPCEncoder");    // Create a new output vector on end of signal list
  
  // Computation engine :
  int expFactor=5;
  int N=GP_LDPCEncoder->N;
  int K=GP_LDPCEncoder->K;
  int column_msg_B=K/expFactor;
  int row_B= 46;
  int column_B= 68;
  // Computation engine :
  int codeword[N];
  int parity[expFactor];
  int row_H=row_B*expFactor;
  int column_H=column_B*expFactor;
  int H[row_B][column_B][expFactor][expFactor];
  int h[row_H][column_H];
  int newInput[N_input];
  int i,j,k,m;
  for (i=0;i<N_input;i++)
    {
      newInput[i]= (int) input[i];
      // printf("New input[%d]: %d\n", i, newInput[i]);
    }
  
  alist2pchk(row_B, column_B, row_H, column_H, expFactor, h);
  
  
  //printf("\n\n-----------------------------------------\n\n");
  //printf("            Converting 2D H to 4D H            ");
  //printf("\n\n-----------------------------------------\n\n");
   
  for (k=0; k<row_B; k++)  //row B
    {
      for (i=0; i<expFactor; i++)
	{
	  for (m=0; m<column_B; m++) //column B
	    {
	      for (j=0; j<expFactor; j++)
		{
		  H[k][m][i][j] =  h[((expFactor-1)*k)+k+i][((expFactor-1)*m)+m+j];
		  //printf("H[%d][%d][%d][%d]:  %d\n",k,m,i,j,H[k][m][i][j] );
		}
	    }
	}
      //printf("\n");
    }

  printf("\n\n Finish converting to 4D H  \n\n\n");
  
  initialise_codeword(N_input, N_output, newInput, codeword);
  //print_codeword(codeword);
  get_parity(newInput, codeword, parity, expFactor, row_B, column_B, column_msg_B, N, K, H); //Calculate parity bits

  // print_codeword(codeword, N);
  int check = syndrome(codeword, row_B, column_B, row_H, column_H, expFactor, h);  
  //To check for valid codeword

  if (check == 0)
    {
      printf("\n\nValue of check is : %d ",check);
      printf("\n\nCodeword is Valid\n\n\n");
    }
  else
    {
      printf("\n\nValue of check is : %d ",check);
      printf("\n\nCodeword is Invalid\n\n\n");
    }

  //Codeword=output
  for(i=0; i<N_output; i++)
    {
      output[i] = (uint8_t) codeword[i];
    }
  
  
  // Save the time for the computation engine
  endTime = clock();
  GP_LDPCEncoder->simTime+=(double)(endTime-beginTime)/CLOCKS_PER_SEC;
  GP_LDPCEncoder->numberOfCalls++;
}


