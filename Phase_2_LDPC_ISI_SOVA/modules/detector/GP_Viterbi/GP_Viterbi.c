// Software Recording Channel (SWRC) platform in C.
// Name      : GP_Viterbi
// Type      : module.
// Path      : modules/detector/GP_Viterbi
// Dependency: 
// Version   : 1.0
// Author(s) : Kheong Sann Chan.
// Date      : Mon Mar 28 17:14:28 2022
// Comment   : Viterbi detector parameters 

#include "GP_Viterbi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct LL{
  uint8_t bit;         // Incoming bit
  char state;          // State for that node (using binary representation)
  double path_met;     // Path Metric
  double LLR;          // For storing the Log Likelihood Ratio value
  struct LL *next;     // pointer to the next element in the LL
}LL;

typedef struct vitDecStruct {
  int sk_length;              // length of the Sk Table
  int h_length;               // length of the h coefficients
  double Sk[32];              // Sk table array
  double h[5];                // h coefficient array
  struct LL *head_arr1[16];   // For storing heads of linked list
  struct LL *head_arr2[16];   // For storing heads of linked list (for second list with the same state)
  struct LL *node_arr1[16];   // For storing the corresponding node to head_arr1
  struct LL *node_arr2[16];   // For storing the corresponding node to head_arr2
}vitDecStruct;

// Print the double *sk struct
void printSkGP_ViterbiStruct (GP_ViterbiStruct *GP_Viterbi) {
}

// Free the memory allocated to double *sk
void freeSkGP_ViterbiStruct (GP_ViterbiStruct *GP_Viterbi) {
}

// Allocate memory for double *sk
void allocateSkGP_ViterbiStruct (GP_ViterbiStruct *GP_Viterbi) {
}

// Print the double *h struct
void printHGP_ViterbiStruct (GP_ViterbiStruct *GP_Viterbi) {
}

// Free the memory allocated to double *h
void freeHGP_ViterbiStruct (GP_ViterbiStruct *GP_Viterbi) {
}

// Allocate memory for double *h
void allocateHGP_ViterbiStruct (GP_ViterbiStruct *GP_Viterbi) {
}

// Initialize the fields in the module structure
// Set pointers to NULL (so they can be called with realloc)
// Initialize the parameters to sane start-up values.
void initGP_ViterbiStruct (GP_ViterbiStruct *GP_Viterbi) {
// Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
  GP_Viterbi->N                       = 0;
  GP_Viterbi->h                       = NULL;
  GP_Viterbi->sk                      = NULL;
  GP_Viterbi->Ns                      = 0;
  GP_Viterbi->SNR                     = 0.0;
// Fields automatically included in every module that request $args{i}
  GP_Viterbi->trainFlag               = 0;
  GP_Viterbi->N_train                 = 0;
  GP_Viterbi->i_train                 = 0;
  GP_Viterbi->numberOfMult            = 0;
  GP_Viterbi->aveNoOfMultPerFrame     = 0.0;
  GP_Viterbi->numberOfAdd             = 0;
  GP_Viterbi->aveNoOfAddPerFrame      = 0.0;
  GP_Viterbi->numberOfComp            = 0;
  GP_Viterbi->aveNoOfCompPerFrame     = 0.0;
  GP_Viterbi->simTime                 = 0.0;
  GP_Viterbi->aveSimTimePerFrame      = 0.0;
  GP_Viterbi->numberOfCalls           = 0;
}

// Frees up all the memory in the structure
void freeGP_ViterbiStruct (GP_ViterbiStruct *GP_Viterbi) {
  if (GP_Viterbi==NULL) {printf("GP_Viterbi=NULL in function freeGP_ViterbiStruct not free'ing\n");return;}
  int i;
  GP_Viterbi->N                 =0;
  //Free double *h
  freeHGP_ViterbiStruct(GP_Viterbi);
  //Free double *sk
  freeSkGP_ViterbiStruct(GP_Viterbi);
  GP_Viterbi->Ns                =0;
  GP_Viterbi->SNR               =0.0;
  GP_Viterbi->trainFlag         =0;
  GP_Viterbi->N_train           =0;
  GP_Viterbi->i_train           =0;
  GP_Viterbi->numberOfMult      =0;
  GP_Viterbi->aveNoOfMultPerFrame=0.0;
  GP_Viterbi->numberOfAdd       =0;
  GP_Viterbi->aveNoOfAddPerFrame=0.0;
  GP_Viterbi->numberOfComp      =0;
  GP_Viterbi->aveNoOfCompPerFrame=0.0;
  GP_Viterbi->simTime           =0.0;
  GP_Viterbi->aveSimTimePerFrame=0.0;
  GP_Viterbi->numberOfCalls     =0;
  //free(GP_Viterbi);GP_Viterbi=NULL;
}

// Prints the contents of the structure.
// Used for determining the status of the simulation
// as well as for debugging.
void printGP_ViterbiStruct (GP_ViterbiStruct *GP_Viterbi, char *name, int index, int pre) {
  int i,j;
  char *preString,*name2;
  if (GP_Viterbi==NULL) {printf("%s%s=NULL\n",preString,name);return;}
  preString=(char*)calloc((pre+1),sizeof(char));
  for (i=0;i<pre;i++) preString[i]=' '; preString[i]='\0';
  printf("%s[--%d:%s--------\n",preString,index,name);
// Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
    printf("%s  int                  %s->N=%d\n",preString,name,GP_Viterbi->N);                        // Print int N
    printHGP_ViterbiStruct(GP_Viterbi);                                                                // Print double *h
    printSkGP_ViterbiStruct(GP_Viterbi);                                                               // Print double *sk
    printf("%s  int                  %s->Ns=%d\n",preString,name,GP_Viterbi->Ns);                      // Print int Ns
    printf("%s  double               %s->SNR=%lf\n",preString,name,GP_Viterbi->SNR);                   // Print double SNR
// Fields automatically included in every module that request $args{i}
    printf("%s  uint8_t              %s->trainFlag=%"SCNu8"\n",preString,name,GP_Viterbi->trainFlag);  // Print uint8_t trainFlag
    printf("%s  long int             %s->N_train=%ld\n",preString,name,GP_Viterbi->N_train);           // Print long int N_train
    printf("%s  long int             %s->i_train=%ld\n",preString,name,GP_Viterbi->i_train);           // Print long int i_train
    printf("%s  long unsigned int    %s->numberOfMult=%lu\n",preString,name,GP_Viterbi->numberOfMult); // Print long unsigned int numberOfMult
    printf("%s  double               %s->aveNoOfMultPerFrame=%lf\n",preString,name,GP_Viterbi->aveNoOfMultPerFrame); // Print double aveNoOfMultPerFrame
    printf("%s  long unsigned int    %s->numberOfAdd=%lu\n",preString,name,GP_Viterbi->numberOfAdd);   // Print long unsigned int numberOfAdd
    printf("%s  double               %s->aveNoOfAddPerFrame=%lf\n",preString,name,GP_Viterbi->aveNoOfAddPerFrame); // Print double aveNoOfAddPerFrame
    printf("%s  long unsigned int    %s->numberOfComp=%lu\n",preString,name,GP_Viterbi->numberOfComp); // Print long unsigned int numberOfComp
    printf("%s  double               %s->aveNoOfCompPerFrame=%lf\n",preString,name,GP_Viterbi->aveNoOfCompPerFrame); // Print double aveNoOfCompPerFrame
    printf("%s  double               %s->simTime=%lf\n",preString,name,GP_Viterbi->simTime);           // Print double simTime
    printf("%s  double               %s->aveSimTimePerFrame=%lf\n",preString,name,GP_Viterbi->aveSimTimePerFrame); // Print double aveSimTimePerFrame
    printf("%s  long unsigned int    %s->numberOfCalls=%lu\n",preString,name,GP_Viterbi->numberOfCalls); // Print long unsigned int numberOfCalls
  printf("%s---%d:%s-------]\n",preString,index,name);
  free(preString);
}

// Store random values into the fields of GP_ViterbiStruct.
// For testing that saving to .cfg file works.
// User should help to write appropriate random-generating values
// to be stored in the appropriate fields.
void randomizeGP_ViterbiStruct (GP_ViterbiStruct *GP_Viterbi) {
  int idum=1;SWRC_randomize(&idum);
  //GP_Viterbi->N=rand();
  //GP_Viterbi->h=ran2(&idum);
  //GP_Viterbi->sk=ran2(&idum);
  //GP_Viterbi->Ns=rand();
  //GP_Viterbi->SNR=ran2(&idum);
}

// Initialize an array of GP_ViterbiStruct's to sane starting values
void initArrayGP_ViterbiStruct (arrayGP_ViterbiStruct *GP_Viterbi) {
  GP_Viterbi->N_x=0;
  GP_Viterbi->x=NULL;
}

// Allocate memory for an array of N GP_ViterbiStruct's
void allocateArrayGP_ViterbiStruct (arrayGP_ViterbiStruct *GP_Viterbi,int N) {
  int i;
  GP_Viterbi->N_x=N;
  GP_Viterbi->x = (GP_ViterbiStruct*)realloc(GP_Viterbi->x,N*sizeof(GP_ViterbiStruct));
  for (i=0;i<GP_Viterbi->N_x;i++) {
    initGP_ViterbiStruct(&GP_Viterbi->x[i]);
  }
}

// Free an array of GP_ViterbiStruct's
void freeArrayGP_ViterbiStruct (arrayGP_ViterbiStruct *GP_Viterbi) {
  if (GP_Viterbi==NULL) {printf("GP_Viterbi=NULL in function freeArrayGP_ViterbiStruct not free'ing\n");return;}
  int i;
  for (i=0;i<GP_Viterbi->N_x;i++) {
    freeGP_ViterbiStruct(&GP_Viterbi->x[i]);
  } free(GP_Viterbi->x);GP_Viterbi->x=NULL;
}

// Fill the arrayGP_ViterbiStruct with random values.
// The GP_Viterbi->N_GP_Viterbi parameter 
// must be set to the number of elements in the array.
// Array must be allocated before calling this function.
void randomizeArrayGP_ViterbiStruct (arrayGP_ViterbiStruct *GP_Viterbi) {
  int i;
  for (i=0;i<GP_Viterbi->N_x;i++) randomizeGP_ViterbiStruct(&GP_Viterbi->x[i]);
}

// Print arrayGP_ViterbiStruct
void printArrayGP_ViterbiStruct (arrayGP_ViterbiStruct *GP_Viterbi) {
  int i;
  for (i=0;i<GP_Viterbi->N_x;i++) {
    printGP_ViterbiStruct(&GP_Viterbi->x[i],"GP_Viterbi",i,0);
  }
}

// Initialize a double array of GP_ViterbiStruct to sane startup values
void initDoubleArrayGP_ViterbiStruct (doubleArrayGP_ViterbiStruct *GP_Viterbi) {
  GP_Viterbi->N_N_x=0;
  GP_Viterbi->N_x=NULL;
  GP_Viterbi->x=NULL;
}

// Allocate memory for a rectangular double array of GP_ViterbiStruct
void allocateDoubleArrayGP_ViterbiStruct (doubleArrayGP_ViterbiStruct *GP_Viterbi, int N, int M) {
  int i,j;
  GP_Viterbi->N_N_x=N;
  GP_Viterbi->N_x=(long unsigned int*)realloc(GP_Viterbi->N_x,N*sizeof(long unsigned int));
  for (i=0;i<GP_Viterbi->N_N_x;i++) GP_Viterbi->N_x[i]=M;
  GP_Viterbi->x=(GP_ViterbiStruct**)realloc(GP_Viterbi->x,N*sizeof(GP_ViterbiStruct*));
  for (i=0;i<GP_Viterbi->N_N_x;i++) {
    GP_Viterbi->x[i]=(GP_ViterbiStruct*)calloc(M,sizeof(GP_ViterbiStruct));
  for(j=0;j<GP_Viterbi->N_x[i];j++) initGP_ViterbiStruct(&GP_Viterbi->x[i][j]);
  }
}

// Free a double array of GP_ViterbiStruct's
void freeDoubleArrayGP_ViterbiStruct (doubleArrayGP_ViterbiStruct *GP_Viterbi) {
  int i;
  for (i=0;i<GP_Viterbi->N_N_x;i++) {
    if (GP_Viterbi->x[i]!=NULL) free(GP_Viterbi->x[i]);
  }
  free(GP_Viterbi->N_x);GP_Viterbi->N_x=NULL;
  free(GP_Viterbi->x);GP_Viterbi->x=NULL;
}

// Print arrayGP_ViterbiStruct
void printDoubleArrayGP_ViterbiStruct (doubleArrayGP_ViterbiStruct *GP_Viterbi, char *name, int index, int pre) {
}

// Plot function generates any plots associated with the 
// structure
void plotGP_ViterbiStruct (GP_ViterbiStruct *GP_Viterbi, const char *filename) {
}

// All the data from all the modules is packed into an
// array of uint8_vectors for saving. One uint8_vector per module. 
// Each uint8_vector contains a stringified version of the
// data in the struct. uint8_vectors are then written to and 
// read from disk by the SWRC_saveuint8_vector and SWRC_loaduint8_vector 
// functions. This function packs struct data into a uint_8_vector
void packGP_ViterbiStruct (GP_ViterbiStruct *GP_Viterbi, uint8_vector *cfgFile) {
  int i;
 //Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
  // Pack int N
  SWRC_packToUint8((uint8_t*)&GP_Viterbi->N,1,sizeof(int),cfgFile);
  // Pack double *h
  SWRC_packToUint8((uint8_t*)GP_Viterbi->h, GP_Viterbi->N_h,sizeof(double),cfgFile);
  // Pack double *sk
  SWRC_packToUint8((uint8_t*)GP_Viterbi->sk, GP_Viterbi->N_sk,sizeof(double),cfgFile);
  // Pack int Ns
  SWRC_packToUint8((uint8_t*)&GP_Viterbi->Ns,1,sizeof(int),cfgFile);
  // Pack double SNR
  SWRC_packToUint8((uint8_t*)&GP_Viterbi->SNR,1,sizeof(double),cfgFile);
 //Fields automatically included in every module that request $args{i}
  // Pack uint8_t trainFlag
  SWRC_packToUint8((uint8_t*)&GP_Viterbi->trainFlag,1,sizeof(uint8_t),cfgFile);
  // Pack long int N_train
  SWRC_packToUint8((uint8_t*)&GP_Viterbi->N_train,1,sizeof(long int),cfgFile);
  // Pack long int i_train
  SWRC_packToUint8((uint8_t*)&GP_Viterbi->i_train,1,sizeof(long int),cfgFile);
  // Pack long unsigned int numberOfMult
  SWRC_packToUint8((uint8_t*)&GP_Viterbi->numberOfMult,1,sizeof(long unsigned int),cfgFile);
  // Pack double aveNoOfMultPerFrame
  SWRC_packToUint8((uint8_t*)&GP_Viterbi->aveNoOfMultPerFrame,1,sizeof(double),cfgFile);
  // Pack long unsigned int numberOfAdd
  SWRC_packToUint8((uint8_t*)&GP_Viterbi->numberOfAdd,1,sizeof(long unsigned int),cfgFile);
  // Pack double aveNoOfAddPerFrame
  SWRC_packToUint8((uint8_t*)&GP_Viterbi->aveNoOfAddPerFrame,1,sizeof(double),cfgFile);
  // Pack long unsigned int numberOfComp
  SWRC_packToUint8((uint8_t*)&GP_Viterbi->numberOfComp,1,sizeof(long unsigned int),cfgFile);
  // Pack double aveNoOfCompPerFrame
  SWRC_packToUint8((uint8_t*)&GP_Viterbi->aveNoOfCompPerFrame,1,sizeof(double),cfgFile);
  // Pack double simTime
  SWRC_packToUint8((uint8_t*)&GP_Viterbi->simTime,1,sizeof(double),cfgFile);
  // Pack double aveSimTimePerFrame
  SWRC_packToUint8((uint8_t*)&GP_Viterbi->aveSimTimePerFrame,1,sizeof(double),cfgFile);
  // Pack long unsigned int numberOfCalls
  SWRC_packToUint8((uint8_t*)&GP_Viterbi->numberOfCalls,1,sizeof(long unsigned int),cfgFile);
}

// After loading the data back from a .cfg file, the data is unpacked
// back into the struct with this function.
void unpackGP_ViterbiStruct (GP_ViterbiStruct *GP_Viterbi, uint8_vector *cfgFile) {
  int i;
  freeGP_ViterbiStruct(GP_Viterbi);
// Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
  // Unpack int N
  SWRC_unpackFromUint8((uint8_t*)&GP_Viterbi->N,1,sizeof(int),cfgFile);
  // Unpack double *h
  if ((GP_Viterbi->N_h)!=0) {
    GP_Viterbi->h = (double*)calloc(GP_Viterbi->N_h,sizeof(double));
    SWRC_unpackFromUint8((uint8_t*)GP_Viterbi->h,GP_Viterbi->N_h,sizeof(double),cfgFile);
  }
  // Unpack double *sk
  if ((GP_Viterbi->N_sk)!=0) {
    GP_Viterbi->sk = (double*)calloc(GP_Viterbi->N_sk,sizeof(double));
    SWRC_unpackFromUint8((uint8_t*)GP_Viterbi->sk,GP_Viterbi->N_sk, sizeof(double),cfgFile);
  }
  // Unpack int Ns
  SWRC_unpackFromUint8((uint8_t*)&GP_Viterbi->Ns,1,sizeof(int),cfgFile);
  // Unpack double SNR
  SWRC_unpackFromUint8((uint8_t*)&GP_Viterbi->SNR,1,sizeof(double),cfgFile);
// Fields automatically included in every module that request $args{i}
  // Unpack uint8_t trainFlag
  SWRC_unpackFromUint8((uint8_t*)&GP_Viterbi->trainFlag,1,sizeof(uint8_t),cfgFile);
  // Unpack long int N_train
  SWRC_unpackFromUint8((uint8_t*)&GP_Viterbi->N_train,1,sizeof(long int),cfgFile);
  // Unpack long int i_train
  SWRC_unpackFromUint8((uint8_t*)&GP_Viterbi->i_train,1,sizeof(long int),cfgFile);
  // Unpack long unsigned int numberOfMult
  SWRC_unpackFromUint8((uint8_t*)&GP_Viterbi->numberOfMult,1,sizeof(long unsigned int),cfgFile);
  // Unpack double aveNoOfMultPerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_Viterbi->aveNoOfMultPerFrame,1,sizeof(double),cfgFile);
  // Unpack long unsigned int numberOfAdd
  SWRC_unpackFromUint8((uint8_t*)&GP_Viterbi->numberOfAdd,1,sizeof(long unsigned int),cfgFile);
  // Unpack double aveNoOfAddPerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_Viterbi->aveNoOfAddPerFrame,1,sizeof(double),cfgFile);
  // Unpack long unsigned int numberOfComp
  SWRC_unpackFromUint8((uint8_t*)&GP_Viterbi->numberOfComp,1,sizeof(long unsigned int),cfgFile);
  // Unpack double aveNoOfCompPerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_Viterbi->aveNoOfCompPerFrame,1,sizeof(double),cfgFile);
  // Unpack double simTime
  SWRC_unpackFromUint8((uint8_t*)&GP_Viterbi->simTime,1,sizeof(double),cfgFile);
  // Unpack double aveSimTimePerFrame
  SWRC_unpackFromUint8((uint8_t*)&GP_Viterbi->aveSimTimePerFrame,1,sizeof(double),cfgFile);
  // Unpack long unsigned int numberOfCalls
  SWRC_unpackFromUint8((uint8_t*)&GP_Viterbi->numberOfCalls,1,sizeof(long unsigned int),cfgFile);
}

// Pack the contents of arrayGP_ViterbiStruct to a uint8_vector
void packArrayGP_ViterbiStruct (arrayGP_ViterbiStruct *GP_Viterbi, uint8_vector *cfgFile) {
  SWRC_packToUint8((uint8_t*)&GP_Viterbi->N_x,1,sizeof(long unsigned int),cfgFile);
  SWRC_packToUint8((uint8_t*)GP_Viterbi->x,GP_Viterbi->N_x,sizeof(GP_ViterbiStruct),cfgFile);
}

// Unpack the contents of arrayGP_ViterbiStruct from a uint8_vector.
void unpackArrayGP_ViterbiStruct (arrayGP_ViterbiStruct *GP_Viterbi, uint8_vector *cfgFile) {
  SWRC_unpackFromUint8((uint8_t*)&GP_Viterbi->N_x,1,sizeof(long unsigned int),cfgFile);
  GP_Viterbi->x = (GP_ViterbiStruct*)realloc(GP_Viterbi->x,GP_Viterbi->N_x*sizeof(GP_ViterbiStruct));
  SWRC_unpackFromUint8((uint8_t*)GP_Viterbi->x,GP_Viterbi->N_x,sizeof(GP_ViterbiStruct),cfgFile);
}

// Pack the contents of doubleArrayGP_ViterbiStruct to a uint8_vector
void packDoubleArrayGP_ViterbiStruct (doubleArrayGP_ViterbiStruct *GP_Viterbi, uint8_vector *cfgFile) {
  int i;
  SWRC_packToUint8((uint8_t*)&GP_Viterbi->N_N_x,1,sizeof(long unsigned int),cfgFile);
  SWRC_packToUint8((uint8_t*)GP_Viterbi->N_x,GP_Viterbi->N_N_x,sizeof(long unsigned int),cfgFile);
  for (i=0;i<GP_Viterbi->N_N_x;i++) 
    SWRC_packToUint8((uint8_t*)GP_Viterbi->x[i],GP_Viterbi->N_x[i],sizeof(GP_ViterbiStruct),cfgFile);
}

// Unpack the contents of doubleArrayGP_ViterbiStruct from a uint8_vector
void unpackDoubleArrayGP_ViterbiStruct (doubleArrayGP_ViterbiStruct *GP_Viterbi, uint8_vector *cfgFile) {
  int i;
  SWRC_unpackFromUint8((uint8_t*)&GP_Viterbi->N_N_x,1,sizeof(long unsigned int),cfgFile);
  // allocate memory for and unpack GP_Viterbi->N_GP_Viterbi
  GP_Viterbi->N_x=(long unsigned int*) realloc(GP_Viterbi->N_x,GP_Viterbi->N_N_x*sizeof(long unsigned int));
  SWRC_unpackFromUint8((uint8_t*)GP_Viterbi->N_x,GP_Viterbi->N_N_x,sizeof(long unsigned int),cfgFile);
  // allocate memory for GP_Viterbi->GP_Viterbi
  GP_Viterbi->x=(GP_ViterbiStruct**)realloc(GP_Viterbi->x,GP_Viterbi->N_N_x*sizeof(GP_ViterbiStruct*));
  for (i=0;i<GP_Viterbi->N_N_x;i++) {
    SWRC_unpackFromUint8((uint8_t*)GP_Viterbi->x[i],GP_Viterbi->N_x[i],sizeof(GP_ViterbiStruct),cfgFile);
  }
}

// Function for loading the struct
int loadGP_ViterbiStruct (GP_ViterbiStruct *GP_Viterbi, char *filename) {
}

// Function for saving the struct
void saveGP_ViterbiStruct (GP_ViterbiStruct *GP_Viterbi, char *filename) {
}

// Set parameters (fields) in the structure
// Change the values of fields in the structure
void setParmGP_ViterbiStruct (GP_ViterbiStruct *GP_Viterbi, char *arg) {
  int i;
  SWRC_removeSpaces(arg);
   if (SWRC_readSingleArgumentFromString(arg,"N",&GP_Viterbi->N,"%d")==1) {
     printf("N=%d\n",GP_Viterbi->N);
   }
  // if (SWRC_readMultipleArgumentsFromString(arg,"h",(void**)&GP_Viterbi->h,&GP_Viterbi->,sizeof(double),"%lf")>0) {
  //   printf("h=[");for (i=0;i<GP_Viterbi->;i++){printf("%lf ",GP_Viterbi->h[i]);}printf("]\n");
  // }
  // if (SWRC_readMultipleArgumentsFromString(arg,"sk",(void**)&GP_Viterbi->sk,&GP_Viterbi->,sizeof(double),"%lf")>0) {
  //   printf("sk=[");for (i=0;i<GP_Viterbi->;i++){printf("%lf ",GP_Viterbi->sk[i]);}printf("]\n");
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"Ns",&GP_Viterbi->Ns,"%d")==1) {
  //   printf("Ns=%d\n",GP_Viterbi->Ns);
  // }
  if (SWRC_readSingleArgumentFromString(arg,"SNR",&GP_Viterbi->SNR,"%lf")==1) {
    printf("SNR=%lf\n",GP_Viterbi->SNR);
  }
  // if (SWRC_readSingleArgumentFromString(arg,"trainFlag",&GP_Viterbi->trainFlag,"%"SCNu8"")==1) {
  //   printf("trainFlag=%"SCNu8"\n",GP_Viterbi->trainFlag);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"N_train",&GP_Viterbi->N_train,"%ld")==1) {
  //   printf("N_train=%ld\n",GP_Viterbi->N_train);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"i_train",&GP_Viterbi->i_train,"%ld")==1) {
  //   printf("i_train=%ld\n",GP_Viterbi->i_train);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfMult",&GP_Viterbi->numberOfMult,"%lu")==1) {
  //   printf("numberOfMult=%lu\n",GP_Viterbi->numberOfMult);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveNoOfMultPerFrame",&GP_Viterbi->aveNoOfMultPerFrame,"%lf")==1) {
  //   printf("aveNoOfMultPerFrame=%lf\n",GP_Viterbi->aveNoOfMultPerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfAdd",&GP_Viterbi->numberOfAdd,"%lu")==1) {
  //   printf("numberOfAdd=%lu\n",GP_Viterbi->numberOfAdd);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveNoOfAddPerFrame",&GP_Viterbi->aveNoOfAddPerFrame,"%lf")==1) {
  //   printf("aveNoOfAddPerFrame=%lf\n",GP_Viterbi->aveNoOfAddPerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfComp",&GP_Viterbi->numberOfComp,"%lu")==1) {
  //   printf("numberOfComp=%lu\n",GP_Viterbi->numberOfComp);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveNoOfCompPerFrame",&GP_Viterbi->aveNoOfCompPerFrame,"%lf")==1) {
  //   printf("aveNoOfCompPerFrame=%lf\n",GP_Viterbi->aveNoOfCompPerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"simTime",&GP_Viterbi->simTime,"%lf")==1) {
  //   printf("simTime=%lf\n",GP_Viterbi->simTime);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"aveSimTimePerFrame",&GP_Viterbi->aveSimTimePerFrame,"%lf")==1) {
  //   printf("aveSimTimePerFrame=%lf\n",GP_Viterbi->aveSimTimePerFrame);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfCalls",&GP_Viterbi->numberOfCalls,"%lu")==1) {
  //   printf("numberOfCalls=%lu\n",GP_Viterbi->numberOfCalls);
  // }
  if (*arg!='\0') {
    printf("GP_Viterbi module: Remaining unknown parms in arg list:%s\n Please correct and run again.\n",arg);exit(-1);
  }
}

// A command comes from the user
// This function processes and executes the command
// some commands need a signal to operate on, which is
// passed via the signalStruct. 
void processCommandGP_Viterbi (GP_ViterbiStruct *GP_Viterbi, signalStruct *signal, const char *command) {
  char commandParameter[400];
  int i;
  printf("processCommandGP_Viterbi:%s\n",command);
  for(i=0;i<400 && i<strlen(command);) {
    if (SWRC_matchCommand(command,"load",&i,commandParameter,400)==1) {
	loadGP_ViterbiStruct(GP_Viterbi,commandParameter);
	continue;
    }

    if (SWRC_matchCommand(command,"print",&i,commandParameter,400)==1) {
	printGP_ViterbiStruct(GP_Viterbi,"GP_Viterbi",0,0);
	continue;
    }

    if (SWRC_matchCommand(command,"setParm",&i,commandParameter,400)==1) {
	setParmGP_ViterbiStruct(GP_Viterbi,commandParameter);
	continue;
    }

    if (SWRC_matchCommand(command,"checkParm",&i,commandParameter,400)==1) {
	checkParametersGP_Viterbi(GP_Viterbi);
	continue;
    }

    if (SWRC_matchCommand(command,"precomp",&i,commandParameter,400)==1) {
	precompGP_Viterbi(GP_Viterbi);
	continue;
    }

    if (SWRC_matchCommand(command,"postcomp",&i,commandParameter,400)==1) {
	postcompGP_Viterbi(GP_Viterbi,0);
	continue;
    }

    if (SWRC_matchCommand(command,"help",&i,commandParameter,400)==1) {
	helpCommandGP_Viterbi(0);
	continue;
    }

    if (SWRC_matchCommand(command,"run",&i,commandParameter,400)==1) {
	runGP_Viterbi(GP_Viterbi, signal);
	continue;
    }

    printf("processCommandGP_Viterbi: Unknown command:%s\n",&command[i]);
    break;
  }
}

// Provides instructions on the commands that this module is able to process.
void helpCommandGP_Viterbi (int index) {
  printf("Commands recognized by %d:GP_ViterbiStruct:\n",index);
  printf("  \"print();\"        : print the GP_ViterbiStruct fields\n");
  printf("  \"setParm(arg);\"   : set the GP_ViterbiStruct fields\n");
  printf("  \"help();\"         : display this help screen\n");
}

// Check that all the parameters needed to run the simulation are present.
// Uncomment any/all variables that _need_ to be present for the simulation to run.
int checkParametersGP_Viterbi (GP_ViterbiStruct *GP_Viterbi) {
  int output=0;
  //if (GP_Viterbi->N==0) {output++;printf("GP_Viterbi->N needed, but not set\n");}
  //if (GP_Viterbi->h==NULL) {output++;printf("GP_Viterbi->h needed, but not set\n");}
  //if (GP_Viterbi->sk==NULL) {output++;printf("GP_Viterbi->sk needed, but not set\n");}
  //if (GP_Viterbi->Ns==0) {output++;printf("GP_Viterbi->Ns needed, but not set\n");}
  //if (GP_Viterbi->SNR==0.0) {output++;printf("GP_Viterbi->SNR needed, but not set\n");}
  //if (GP_Viterbi->trainFlag==0) {output++;printf("GP_Viterbi->trainFlag needed, but not set\n");}
  //if (GP_Viterbi->N_train==0) {output++;printf("GP_Viterbi->N_train needed, but not set\n");}
  //if (GP_Viterbi->i_train==0) {output++;printf("GP_Viterbi->i_train needed, but not set\n");}
  //if (GP_Viterbi->numberOfMult==0) {output++;printf("GP_Viterbi->numberOfMult needed, but not set\n");}
  //if (GP_Viterbi->aveNoOfMultPerFrame==0.0) {output++;printf("GP_Viterbi->aveNoOfMultPerFrame needed, but not set\n");}
  //if (GP_Viterbi->numberOfAdd==0) {output++;printf("GP_Viterbi->numberOfAdd needed, but not set\n");}
  //if (GP_Viterbi->aveNoOfAddPerFrame==0.0) {output++;printf("GP_Viterbi->aveNoOfAddPerFrame needed, but not set\n");}
  //if (GP_Viterbi->numberOfComp==0) {output++;printf("GP_Viterbi->numberOfComp needed, but not set\n");}
  //if (GP_Viterbi->aveNoOfCompPerFrame==0.0) {output++;printf("GP_Viterbi->aveNoOfCompPerFrame needed, but not set\n");}
  //if (GP_Viterbi->simTime==0.0) {output++;printf("GP_Viterbi->simTime needed, but not set\n");}
  //if (GP_Viterbi->aveSimTimePerFrame==0.0) {output++;printf("GP_Viterbi->aveSimTimePerFrame needed, but not set\n");}
  //if (GP_Viterbi->numberOfCalls==0) {output++;printf("GP_Viterbi->numberOfCalls needed, but not set\n");}
  return(output);
}

// Precomputation done just prior to the main for loop
// iterating the BER/FER are put into this subroutine
void precompGP_Viterbi (GP_ViterbiStruct *GP_Viterbi) {
  GP_Viterbi->i_train=0;
  GP_Viterbi->numberOfMult=0;
  GP_Viterbi->aveNoOfMultPerFrame=0.0;
  GP_Viterbi->numberOfAdd=0;
  GP_Viterbi->aveNoOfAddPerFrame=0.0;
  GP_Viterbi->numberOfComp=0;
  GP_Viterbi->aveNoOfCompPerFrame=0.0;
  GP_Viterbi->simTime=0.0;
  GP_Viterbi->aveSimTimePerFrame=0.0;
  GP_Viterbi->numberOfCalls=0;
}

// postComputation, such as freeing up any memory, done after
// the iteration of the BER/FER are put into this subroutine
void postcompGP_Viterbi (GP_ViterbiStruct *GP_Viterbi, char finishedFlag) {
  GP_Viterbi->aveNoOfMultPerFrame=(double)GP_Viterbi->numberOfMult/GP_Viterbi->numberOfCalls;
  GP_Viterbi->aveNoOfAddPerFrame=(double)GP_Viterbi->numberOfAdd/GP_Viterbi->numberOfCalls;
  GP_Viterbi->aveNoOfCompPerFrame=(double)GP_Viterbi->numberOfComp/GP_Viterbi->numberOfCalls;
  GP_Viterbi->aveSimTimePerFrame=(double)GP_Viterbi->simTime/GP_Viterbi->numberOfCalls;
}

// Function called prior to training. Zero out statistics matrices,
// set the i_train index to zero etc...
void pretrainGP_Viterbi (GP_ViterbiStruct *GP_Viterbi) {
  GP_Viterbi->i_train=0;
}

// Function called after training. Free allocated memory etc...
void posttrainGP_Viterbi (GP_ViterbiStruct *GP_Viterbi) {
}

// Some modules have a training phase where modules before them are run
// and statistics collected so the module can run properly.
// This function performs the training for the module then 
// saved back to the .cfg file.
// Returns 1 if training is complete
// Returns 0 otherwise
int trainGP_Viterbi (GP_ViterbiStruct *GP_Viterbi, signalStruct *signal) {
  if ((GP_Viterbi->trainFlag&1)==1) { // Training complete, call the run function
    printf("Running GP_Viterbi\n");
    runGP_Viterbi(GP_Viterbi,signal);
    return(1);
  } else {                 // Do the training
    printf("Training GP_Viterbi %ld/%ld\n",GP_Viterbi->i_train,GP_Viterbi->N_train);
    // Accumulate the statistics
    GP_Viterbi->i_train++;
    if (GP_Viterbi->i_train>=GP_Viterbi->N_train) { // Statistics accumulated, post-training computation
      GP_Viterbi->trainFlag=1;
    }
    return(0);
  }
}

// Contribute the fields to the berResultStruct that will be 
// printed in the berResult file. Every module contributes
// its own fields. User has to choose the fields to be saved
// using pushBerResultField() once per field to be added
void initBerResultStructGP_Viterbi (GP_ViterbiStruct *GP_Viterbi,berResultStruct *berResult) {
  //pushBerResultField(berResult,"N","int","%1d",&GP_Viterbi->N);
  //pushBerResultField(berResult,"Ns","int","%2d",&GP_Viterbi->Ns);
  //pushBerResultField(berResult,"SNR","double","%3lf",&GP_Viterbi->SNR);
  //pushBerResultField(berResult,"trainFlag","uint8_t","%9"SCNu8"",&GP_Viterbi->trainFlag);
  //pushBerResultField(berResult,"N_train","long int","%7ld",&GP_Viterbi->N_train);
  //pushBerResultField(berResult,"i_train","long int","%7ld",&GP_Viterbi->i_train);
  //pushBerResultField(berResult,"numberOfMult","long unsigned int","%12lu",&GP_Viterbi->numberOfMult);
  //pushBerResultField(berResult,"aveNoOfMultPerFrame","double","%19lf",&GP_Viterbi->aveNoOfMultPerFrame);
  //pushBerResultField(berResult,"numberOfAdd","long unsigned int","%11lu",&GP_Viterbi->numberOfAdd);
  //pushBerResultField(berResult,"aveNoOfAddPerFrame","double","%18lf",&GP_Viterbi->aveNoOfAddPerFrame);
  //pushBerResultField(berResult,"numberOfComp","long unsigned int","%12lu",&GP_Viterbi->numberOfComp);
  //pushBerResultField(berResult,"aveNoOfCompPerFrame","double","%19lf",&GP_Viterbi->aveNoOfCompPerFrame);
  //pushBerResultField(berResult,"simTime","double","%7lf",&GP_Viterbi->simTime);
  //pushBerResultField(berResult,"aveSimTimePerFrame","double","%18lf",&GP_Viterbi->aveSimTimePerFrame);
  //pushBerResultField(berResult,"numberOfCalls","long unsigned int","%13lu",&GP_Viterbi->numberOfCalls);
}

/////////////////// Eve: User-defined Functions starting below ///////////////////////////

/**
 * Find minimum between two numbers.
 */
double min(double num1, double num2) 
{
    return (num1 > num2 ) ? num2 : num1;
}

//// Pre-computation: Generate the Sk table based on the h-coefficient
void precompVitDec(vitDecStruct *vitDecPtr) {
    int i = 0, j = 0;

    vitDecPtr->sk_length = 32;       // Assign the length of Sk lookup table
    vitDecPtr->h_length = 5;         // Assign the length of h-coefficients

    // Assign pointer to the h and sk inside struct
    double (*sk_table)= vitDecPtr->Sk;
    double (*h_coeff) = vitDecPtr->h;

    // Assign the coefficients to the h array
    double h_temp[5] = {0.1, 0.5, 0.7, 0.5, 0.1};
    //double h_temp[5] = {0.100001,0.500001,0.7000001,0.5000001,0.1000001};
    h_coeff = h_temp;

    // 5-bit possible combinations
    double sk_temp[32][5]= {
        {-1, -1, -1, -1, -1},
        {-1, -1, -1, -1,  1},
        {-1, -1, -1,  1, -1},
        {-1, -1, -1,  1,  1},
        {-1, -1,  1, -1, -1},
        {-1, -1,  1, -1,  1},
        {-1, -1,  1,  1, -1},
        {-1, -1,  1,  1,  1},
        {-1,  1, -1, -1, -1},
        {-1,  1, -1, -1,  1},
        {-1,  1, -1,  1, -1},
        {-1,  1, -1,  1,  1},
        {-1,  1,  1, -1, -1},
        {-1,  1,  1, -1,  1},
        {-1,  1,  1,  1, -1},
        {-1,  1,  1,  1,  1},
        { 1, -1, -1, -1, -1},
        { 1, -1, -1, -1,  1},
        { 1, -1, -1,  1, -1},
        { 1, -1, -1,  1,  1},
        { 1, -1,  1, -1, -1},
        { 1, -1,  1, -1,  1},
        { 1, -1,  1,  1, -1},
        { 1, -1,  1,  1,  1},
        { 1,  1, -1, -1, -1},
        { 1,  1, -1, -1,  1},
        { 1,  1, -1,  1, -1},
        { 1,  1, -1,  1,  1},
        { 1,  1,  1, -1, -1},
        { 1,  1,  1, -1,  1},
        { 1,  1,  1,  1, -1},
        { 1,  1,  1,  1,  1},
    };


    // Summing each bits together with multiplication with corresponding h-coefficients
    double sum = 0;
    for(i=0; i<(vitDecPtr->sk_length); i++){
        sum = 0;
        for(j=0; j<(vitDecPtr->h_length); j++){
            sum = sum + sk_temp[i][j]*h_coeff[j];
        }
        sk_table[i] = sum;
	// printf("sk[%d]: %lf\n", i, sk_table[i]);
    }
    //  printf("\n");
}

// // insert node at the front and return the head
// LL* insertFront(LL* head,  uint8_t node_bit, char node_state, double node_pathMet, int counter, double node_LLR) {
//     // allocate memory for newNode
//     LL* newNode = (LL*)malloc(sizeof(LL));

//     // assign data to newNode
//     newNode->bit = node_bit;
//     newNode->path_met = node_pathMet;
//     newNode->state = node_state;
//     newNode->LLR = node_LLR;

//     if (head ==  NULL){
//       newNode->next = NULL;
//     }
//     else{
//       // make newNode as a head
//       newNode->next = head;
//     }
 
//     // head points to newNode
//     head = newNode;

//     return head;
// }

// Delete the whole linked list
void deleteAllnodes(LL* head){
     //1. create a temp node
    LL* temp = head;

    //2. if the head is not null make temp as head and
    //   move head to head next, then delete the temp,
    //   continue the process till head becomes null
    while(head != NULL) {
        temp = head;
        head = (head)->next;
        free(temp);
    }
}

// print the linked list
void displayList(LL* node) {
    LL* last;

    while (node != NULL) {
        printf("Bit: %d, ", node->bit);
        printf("Path Metric: %f, ", node->path_met);
        printf("State: %-3d\t->", node->state);
	printf("LLR: %f->\n", node->LLR);
        last = node;
        node = node->next;
    }
    if (node == NULL)
        printf("NULL\n\n\n");
}


// void killing(LL* node) {
//   LL* temp;
  
//   // free the first node coming in
//   temp = node;
//   node = node->next;
//   node->count = (node->count)-1;
//   deleteOneNode(temp);

//   while(node != NULL) {
//     temp = node;
//     node = node->next;

//     // if the counter is reduced to 0, then continue killing
//     if (temp->count==0){
//       if (temp->next != NULL){
// 	(temp->next)->count = ((temp->next)->count)-1;
//       }
//       deleteOneNode(temp);
//     }
//     else{
//       break; // stop killing once the next node count is not 0
//     }
//   }

// }

LL* copyPath(LL* head){
  // allocate memory for newNode
  LL* node;

  //head = head->next; // start the copying below from the next incoming head node

  if (head == NULL) {
    return NULL;
  }
  else {
    // Allocate the memory for new Node
    // in the heap and set its data
    LL* newNode = (LL*)malloc(sizeof(LL));
  
    newNode->path_met = head->path_met;
    newNode->state = head->state;
    newNode->bit = head->bit;
    newNode->LLR = head->LLR;
  
    // Recursively set the next pointer of
    // the new Node by recurring for the
    // remaining nodes
    newNode->next = copyPath(head->next);
  
    return newNode;
 }

  // while(head->next != NULL){
  //   //// Get the info from the existing node
  //   node = head;
  //   newNode->path_met = node->path_met;
  //   newNode->state = node->state;
  //   newNode->bit = node->bit;
  //   // newNode->next = node->next;
  //   newNode->LLR = node->LLR;
  //   head = (head)->next;
  //   node->next = newNode;
  // }
}


// Access the corresponding Sk value for branch metric calculation
double getSk(vitDecStruct *vitDecPtr, int Sk_index){
    // From the LL struct, we can get the state
    double (*sk_table)= vitDecPtr->Sk;
    return sk_table[Sk_index];
}

// Calculation of the branch metric
double euclidean_metric(vitDecStruct *vitDecPtr, char sk_index, double rk){
  // printf("rk: %f, Sk: %f, (rk-sk)2: %f\n", rk, getSk(vitDecPtr, sk_index), pow((rk-getSk(vitDecPtr, sk_index)), 2));
    return pow((rk-getSk(vitDecPtr, sk_index)), 2);
}


int get_dfree(LL* survivor_head, LL* loser_head){
  LL* temp_survivor;
  LL* temp_loser;
  int dfree;
  
  temp_survivor = survivor_head->next;
  temp_loser = loser_head->next;

  dfree = 0;
  while(temp_survivor->next != NULL){
    if (temp_survivor->bit != temp_loser->bit) {
      dfree++;
    }
    
    if(temp_survivor->state == temp_loser->state){
      break;
    }

    temp_survivor = temp_survivor->next;
    temp_loser = temp_loser->next;
  }

  if(temp_survivor->next == NULL){
    //displayList(temp_survivor->next);
    dfree = 0; // if both paths didn't merge in the past time steps
  }

  return dfree;
}

void tracebackLLR(LL** L, LL* survivor_head, LL* loser_head, double delta){

  LL* temp_survivor;
  LL* temp_loser;
  temp_survivor = survivor_head->next;
  temp_loser = loser_head->next;

  int dfree = get_dfree(survivor_head, loser_head);
  // // printf("\n\ndfree: %d\n\n", dfree);
  
  while((temp_survivor->next != NULL) && (dfree !=0)){
    if (temp_survivor->bit != temp_loser->bit){
      // // printf("WinningLL\n");
      // // displayList(temp_survivor);
      // // printf("Losing LL\n");
      // // displayList(temp_loser);
      // // printf("\nNot equal bit, LLR before updated: %f\n", temp_survivor->LLR);
      temp_survivor->LLR = min(temp_survivor->LLR, delta);   // Update of Lj
      // // printf("\ndelta: %f; temp_survivorLLR: %f\n\n", delta, temp_survivor->LLR);
      // // printf("\nNot equal bit, LLR after updated: %f\n", temp_survivor->LLR);
    }
    // // else{
    // //   printf("\nSame bit\n");
    // // }

    if(temp_survivor->state == temp_loser->state){
      // // printf("Next node same, break out\n");
      // // displayList(temp_survivor);
      break;
    }
    
    temp_survivor = temp_survivor->next;
    temp_loser = temp_loser->next;
  }
}


// Implementation of branching, killing freeing
void subImplementation(vitDecStruct *vitDecPtr, LL** L, LL** Head1, LL** Head2, double rk, int index){
    int i;
    char prev_state, current_state_pos, current_state_neg, sk_index_pos, sk_index_neg;
    double prev_pathMet, current_pathMet_pos, current_pathMet_neg, delta;
    LL* temp;

    // Clear the temp arrays
    for (i=0; i<16; i++) Head1[i] = NULL;
    for (i=0; i<16; i++) Head2[i] = NULL;
    // for (i=0; i<16; i++) displayList(L[i]);

    // printf("\n\nDisplaying the lists\n");
    // for (i=0; i<16; i++) displayList(L[i]);

    for (i=0; i<16; i++){
      // Get the state of the current head for every available LL
      //// Access the last node state
      // store the head node temporarily (for later use)
      LL* head = L[i];

      // allocate memory for newNode
      LL* newNode_pos = (LL*)malloc(sizeof(LL));
      LL* newNode_neg = (LL*)malloc(sizeof(LL));
      
      //// Get the path metric and state info from the node
      prev_pathMet = head->path_met;
      prev_state = head->state;

      // States of the next node
      current_state_neg = (prev_state<<1) & 0b00001111;
      current_state_pos = current_state_neg + 1;
      sk_index_neg = (prev_state<<1) & 0b00011111;
      sk_index_pos = sk_index_neg + 1;

      // Path Metric
      current_pathMet_pos = prev_pathMet + euclidean_metric(vitDecPtr, sk_index_pos, rk);
      current_pathMet_neg = prev_pathMet + euclidean_metric(vitDecPtr, sk_index_neg, rk);

      // assign data to positive branch
      newNode_pos->bit = 1;
      newNode_pos->path_met = current_pathMet_pos;
      newNode_pos->state = current_state_pos;
      newNode_pos->next = head;
      newNode_pos->LLR = 1000000;

      // assign data to negative branch
      newNode_neg->bit = 0;
      newNode_neg->path_met = current_pathMet_neg;
      newNode_neg->state = current_state_neg;
      newNode_neg->next = head;
      newNode_neg->LLR = 1000000;

      // Group the state
      // Assign into the array
      newNode_neg->next = copyPath(newNode_neg->next); // create a new duplicated path for negative branch
      
      if (Head1[current_state_pos] == NULL){
        Head1[current_state_pos] = newNode_pos;
      }
      else{
        Head2[current_state_pos] = newNode_pos;
      }

      if (Head1[current_state_neg] == NULL){
        Head1[current_state_neg] = newNode_neg;
      }
      else{
        Head2[current_state_neg] = newNode_neg;
      }
    }

    // // printf("\n\n Branching out\n");
    // // for (i=0; i<16; i++){
    // //   displayList(Head1[i]);
    // //   displayList(Head2[i]);
    // // }

    // Killing by comparing the Head1 and Head2 same state, then kill the node with biggest path metric backwards
    double path_met1, path_met2;
    LL* node1;
    LL* node2;

    for (i=0; i<16; i++) L[i] = NULL;
    
    for (i=0; i<16; i++){
      node1 = Head1[i];
      node2 = Head2[i];

      if ((Head1[i] != NULL) && (Head2[i] != NULL)){
	path_met1 = node1->path_met;
	path_met2 = node2->path_met;
	delta = fabs(path_met1-path_met2);
	// printf("------------------\nCalculation of Path Metric:\nsk_index: %i, rk: %lf, Path Metric 1: %f; Path Metric 2: %f, delta: %lf\n", i, rk, path_met1, path_met2, delta);
	   
	if (path_met1 > path_met2){
	  L[i] = node2;
	  //if (index>=3){
	    // printf("\n-------------Before LLR Traceback----\n");
	    // displayList(node2);
	    // displayList(node1);
	    tracebackLLR(L, node2, node1, delta);
	    // printf("\nAfter LLR traceback\n");
	    // displayList(node2);
	    
	    // }
	  deleteAllnodes(node1); // pass in the node with biggest path metric
	}
	else{
	  L[i] = node1;
	  //if (index>=3){
	    // printf("\nBefore Traceback-----------------------LLR\n");
	    // displayList(node1);
	    // displayList(node2);
	    tracebackLLR(L, node1, node2, delta);
	    // printf("\nAfter LLR\n");
	    // displayList(node1);
	    // }
	  deleteAllnodes(node2);
	}
      }
    }
    // printf("\n\n After killing\n");
    // for (i=0; i<16; i++) displayList(L[i]);
}

void trellisTermination(vitDecStruct *vitDecPtr, LL** L, LL** Head1, LL** Head2, double rk){
    int i;
    char prev_state, current_state_neg, sk_index_neg;
    double prev_pathMet, current_pathMet_neg;

    // Clear the temp arrays
    for (i=0; i<16; i++) Head1[i] = NULL;
    for (i=0; i<16; i++) Head2[i] = NULL;

    // // printf("\n\nTrellis Termination\n");
    // // for (i=0; i<16; i++) displayList(L[i]);
    
    for (i=0; i<16; i++){

      if (L[i] != NULL){
	
	// Get the state of the current head for every available LL
	//// Access the last node state
	// store the head node temporarily (for later use)
	LL* head = L[i];

	// allocate memory for newNode
	LL* newNode_neg = (LL*)malloc(sizeof(LL));
      
	//// Get the path metric and state info from the node
	prev_pathMet = head->path_met;
	prev_state = head->state;

	// States of the next node
	current_state_neg = (prev_state<<1) & 0b00001111;
	sk_index_neg = (prev_state<<1) & 0b00011111;

	// Path Metric
	//current_pathMet_neg = prev_pathMet + 0;
	current_pathMet_neg = prev_pathMet + euclidean_metric(vitDecPtr, sk_index_neg, rk);


	// // Since only one branch is being attached, reduce the count of the previous node by 1 (only execute one time)
	// if (executed == false){
	//   head->count = (head->count)-1;
	// }

	// assign data to negative branch
	newNode_neg->bit = 0;
	newNode_neg->path_met = current_pathMet_neg;
	newNode_neg->state = current_state_neg;
	newNode_neg->next = head;
	newNode_neg->LLR = 1000000;

	// Group the state
	// Assign into the array
	if (Head1[current_state_neg] == NULL){
	  Head1[current_state_neg] = newNode_neg;
	}
	else{
	  Head2[current_state_neg] = newNode_neg;
	}
      }
    }

    // // printf("\n\n TT: Before Killing, with new node added\n");
    // // for (i=0; i<16; i++){
    // //   displayList(Head1[i]);
    // //   displayList(Head2[i]);
    // // }

    // Killing by comparing the Head1 and Head2 same state, then kill the node with biggest path metric backwards
    double path_met1, path_met2, delta;
    LL* node1;
    LL* node2;

    for (i=0; i<16; i++) L[i] = NULL;
    
    for (i=0; i<16; i++){
      node1 = Head1[i];
      node2 = Head2[i];

      if ((Head1[i] != NULL) && (Head2[i] != NULL)){
	path_met1 = node1->path_met;
	path_met2 = node2->path_met;
	delta = fabs(path_met1-path_met2);
	// // printf("sk_index: %i, rk: %lf, Path Metric 1: %f; Path Metric 2: %f; Delta: %f\n", i, rk, path_met1, path_met2, delta);
	   
	if (path_met1 > path_met2){
	  // printf("\n-------------Before Traceback\n");
	  // displayList(node2);
	  // displayList(node1);
	  L[i] = node2;   // store the node of smallest path metric
	  tracebackLLR(L, node2, node1, delta);
	  deleteAllnodes(node1); // pass in the node with biggest path metric
	  // printf("\nAfter LLR\n");
	  // displayList(node2);
	}
	else{
	  // printf("\n-------------Before Traceback\n");
	  // displayList(node1);
	  // displayList(node2);
	  L[i] = node1;
	  tracebackLLR(L, node1, node2, delta);
	  deleteAllnodes(node2);
	  // printf("\nAfter LLR\n");
	  // displayList(node1);
	}
      }
    
    }

    // printf("\n\nTrellis Termination\n");
    // for (i=0; i<16; i++) displayList(L[i]);

}


// Get the most likely codeword from the survivor path
void getSoftOutput(GP_ViterbiStruct *GP_Viterbi, LL* head, double* output){
  // Traverse through the winning LL
  LL* temp = head->next->next->next->next;
  double temp_outArr[GP_Viterbi->N];

  int i = 0;
  while (temp != NULL && i !=GP_Viterbi->N){
    if (temp->bit == 1){
      temp_outArr[i] = temp->LLR;
    }
    else{
      temp_outArr[i] = -1.0*temp->LLR;
    }
    //printf("Output[%d]: %d\n", i, temp_outArr[i]);
    temp = temp->next;
    i++;
  }

  //Calculate length of array arr    
  int length = GP_Viterbi->N;
  //printf("length: %d\n", length);
  int j = 0;
  //Loop through the array in reverse order    
  for (i = length-1; i >= 0; i--) {
    output[j] = temp_outArr[i];
    //printf("%d\n", output[j]);
    j++;
  }    
}

// Get the most likely codeword from the survivor path
void getHardenedOutput(GP_ViterbiStruct *GP_Viterbi, LL* head, uint8_t* output){
  // Traverse through the winning LL
  LL* temp = head->next->next->next->next;
  double temp_outArr[GP_Viterbi->N];

  int i = 0;
  while (temp != NULL && i !=GP_Viterbi->N){
    if (temp->bit == 1){
      temp_outArr[i] = temp->LLR;
    }
    else{
      temp_outArr[i] = -1.0*temp->LLR;
    }
    //printf("Output[%d]: %d\n", i, temp_outArr[i]);
    temp = temp->next;
    i++;
  }

  //Calculate length of array arr    
  int length = GP_Viterbi->N;
  //printf("length: %d\n", length);
  int j = 0;
  //Loop through the array in reverse order    
  for (i = length-1; i >= 0; i--) {
    if (temp_outArr[i] >= 0){
      output[j] = 1;
    }
    else{
      output[j] = 0;
    }
    j++;
  }    
}

// Main Viterbi Detector
void viterbiDetector(GP_ViterbiStruct *GP_Viterbi, vitDecStruct *vitDecPtr, double* input, double* output){

  // printf("----------Inside Viterbi Detection---------------\n");

    int i, j;
    int N = GP_Viterbi->N;     // Assigning the length of codeword

    // Initialise array of 16 LL
    LL* L[16];
    LL* Head1[16];
    LL* Head2[16];

    // Initialise all LL to be NULL
    for (i=0; i<16; i++) L[i] = NULL;
    for (i=0; i<16; i++) Head1[i] = NULL;
    for (i=0; i<16; i++) Head2[i] = NULL;

    // Initialise by inserting the head node into each LL

    for (i=0; i<16; i++) {
      LL* head = (LL*)malloc(sizeof(LL));

      //  Initialise node with Bit:0, State: i (one of the 16 state), Path Metric: 0, Counter: 2 (2 branches coming out)
      head->bit = 0;
      head->path_met = 0;
      head->state = i;
      head->next = NULL;
      head->LLR = 1000000;

      L[i] = head;
      
      // //displayList(L[i]); // Uncomment this line to display the 16 LLs
    }
    
    // For each of the convoluted bit from ISI channel (The first N bits):
     for (j = 0; j < N; j++){
     
       subImplementation(vitDecPtr, L, Head1, Head2, input[j], j);

       
       // // // 	// Uncomment the for loop below to display the 16 LLs
       // // // printf("\n--------------------------------------New Kill-------------------------------\n\n");
       // // // for (i=0; i<16; i++) {
       // // // 	      displayList(L[i]);
	   
       // // //  }

     }

     // // // ------------------------Trellis Termination-------------------------------------- // // //
     // Pushing additional negative M bits (M = log2(16) = 4 bits) into the channel to return all the LL to the 0000 state
     // For the final 4 bits from the convoluted bits:
     for (j = 0; j < 4; j++){

       trellisTermination(vitDecPtr, L, Head1, Head2, input[N+j]);

	
     }

     // Finally, get the output bit by traverse through the ultimate survivor path
     for (i=0; i<16; i++) {
        if (L[i] != NULL) {
	  getSoftOutput(GP_Viterbi, L[i], output);
	  // printf("\n\nSurvivor LL:\n");
	  // displayList(L[i]->next->next->next->next);
	  break;
	}
     }

      // Free the memory of the survivor path
	for (i=0; i<16; i++) {
	  if (L[i] != NULL) {
	    deleteAllnodes(L[i]);
	    break;
	  }
	}
}



// Finally when everything is in place, the module must be
// run during the actual simulation. The code for running
// the module is in this function.
void runGP_Viterbi (GP_ViterbiStruct *GP_Viterbi, signalStruct *signal) {
  int i;
  clock_t beginTime, endTime;
  int N_input,N_output;
  double *input;
  double *output;
  beginTime=clock();
  printf("In function runGP_Viterbi\n");


  // Allocate memory for 1 more signal. The output of this function should go there.
  // USER NEEDS TO EDIT: the LENGTH of the output vector and the TYPE of
  // the output vector 0=uint8_t, 1=char, 2=int, 3=unsigned int, 4=long unsigned int, 5=float, 6=double
  // The type of the input vector should also be set correctly by the USER.
  N_input  = (signal->N[signal->N_N-1]);        // Length of the input vector
  input    = (double*) signal->x[signal->N_N-1]; // Assign pointer to the input memory
  N_output = GP_Viterbi->N;                               // Length of output vector

  output   = (double*) incrementByOneSignal(signal,N_output,6,"GP_Viterbi");

    // Eve: Pre-computation of Sk Table (I'm thinking should include the precomputation at the main file instead, as if including here the precomputation
    //      will run everytime for computation of each number of frame)
    vitDecStruct vitDec;
    precompVitDec(&vitDec);
   
    // Computation Engine
    viterbiDetector(GP_Viterbi, &vitDec, input, output);
  
  
  // Save the time for the computation engine
  endTime = clock();
  GP_Viterbi->simTime+=(double)(endTime-beginTime)/CLOCKS_PER_SEC;
  GP_Viterbi->numberOfCalls++;
}


