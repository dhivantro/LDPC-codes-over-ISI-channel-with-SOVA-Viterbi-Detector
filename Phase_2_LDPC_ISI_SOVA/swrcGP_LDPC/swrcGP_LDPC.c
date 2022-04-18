#define _GNU_SOURCE    // needed for asprintf
// Software Recording Channel (SWRC) platform in C.
// Name      : swrcGP_LDPC
// Type      : main.
// Path      : 
// Dependency: modules/encoder/GP_LDPCEncoder,modules/channel/GP_ISIChannel,modules/detector/GP_Viterbi,modules/decoder/GP_LDPCDecoder
// Version   : 1.0
// Author(s) : Kheong Sann Chan.
// Date      : Mon Mar 28 17:14:44 2022
// Comment   : SWRC simulation for the LDPC encoder/decoder over an ISI channel 
//             for the group project. 

#include "swrcGP_LDPC.h"
#include <getopt.h>
#include <fcntl.h>
#include <sys/types.h> // needed for
#include <unistd.h>    // getpid()

///////////////////////////////////////////
// The main swrcGP_LDPC program
///////////////////////////////////////////
int main (int argc,char **argv) {
  char c;
  int i;
  // A cfgFile stores the configuration of a simulation as a string of bytes.
  // The bytes are stored in type uint8_vector
  // There is 1 cfgfile per module used in the simulation
  uint8_vector cfgFile[4];
  for (i=0;i<4;i++){
      SWRC_init_uint8_vector(&cfgFile[i]);
  }
  swrcGP_LDPCStruct swrcGP_LDPC;
  initSwrcGP_LDPCStruct(&swrcGP_LDPC);
  if (loadSwrcGP_LDPCStruct(&swrcGP_LDPC,"swrcGP_LDPC.cfg")==1) { // load the swrcGP_LDPC.cfg file into the struct
    printf("Unable to load swrcGP_LDPC.cfg, resuming default configuration.\n");
  }
  // Process the command-line switches supplied by the user
  while ((c=getopt(argc,argv,"cp:rthsk0:1:2:3:4:"))!=EOF) {
    switch (c) {
    case '0':                                                  // process base module swrcGP_LDPC commands
      printf("whileSwitchCase swrcGP_LDPC module: swrcGP_LDPC. optarg=\"%s\"\n",optarg);
      processCommandSwrcGP_LDPC(&swrcGP_LDPC,&swrcGP_LDPC.signal,optarg);
      break;
    case '1':                                                 // process submodule GP_LDPCEncoder commands
      printf("whileSwitchCase swrcGP_LDPC module: GP_LDPCEncoder. optarg=\"%s\"\n",optarg);
      processCommandGP_LDPCEncoder(&swrcGP_LDPC.GP_LDPCEncoder,&swrcGP_LDPC.signal,optarg);
      break;
    case '2':                                                 // process submodule GP_ISIChannel commands
      printf("whileSwitchCase swrcGP_LDPC module: GP_ISIChannel. optarg=\"%s\"\n",optarg);
      processCommandGP_ISIChannel(&swrcGP_LDPC.GP_ISIChannel,&swrcGP_LDPC.signal,optarg);
      break;
    case '3':                                                 // process submodule GP_Viterbi commands
      printf("whileSwitchCase swrcGP_LDPC module: GP_Viterbi. optarg=\"%s\"\n",optarg);
      processCommandGP_Viterbi(&swrcGP_LDPC.GP_Viterbi,&swrcGP_LDPC.signal,optarg);
      break;
    case '4':                                                 // process submodule GP_LDPCDecoder commands
      printf("whileSwitchCase swrcGP_LDPC module: GP_LDPCDecoder. optarg=\"%s\"\n",optarg);
      processCommandGP_LDPCDecoder(&swrcGP_LDPC.GP_LDPCDecoder,&swrcGP_LDPC.signal,optarg);
      break;
    case 'p': // print the structs
      //swrcGP_LDPC.printFlag=1;
      printf("swrcGP_LDPC: Printing struct.\n");
      if (SWRC_ifAnyChar(optarg,'0')) printSwrcGP_LDPCStruct(&swrcGP_LDPC,"swrcGP_LDPC",0,0);
      if (SWRC_ifAnyChar(optarg,'1')) printGP_LDPCEncoderStruct(&swrcGP_LDPC.GP_LDPCEncoder,"swrcGP_LDPC->GP_LDPCEncoder",1,0);
      if (SWRC_ifAnyChar(optarg,'2')) printGP_ISIChannelStruct(&swrcGP_LDPC.GP_ISIChannel,"swrcGP_LDPC->GP_ISIChannel",2,0);
      if (SWRC_ifAnyChar(optarg,'3')) printGP_ViterbiStruct(&swrcGP_LDPC.GP_Viterbi,"swrcGP_LDPC->GP_Viterbi",3,0);
      if (SWRC_ifAnyChar(optarg,'4')) printGP_LDPCDecoderStruct(&swrcGP_LDPC.GP_LDPCDecoder,"swrcGP_LDPC->GP_LDPCDecoder",4,0);
      break;
    case 'c': // Precomputation for modules
      printf("swrcGP_LDPC: Precomputing mode.\n");
      precompSwrcGP_LDPC(&swrcGP_LDPC);
      break;
    case 't': // train the modules
      printf("swrcGP_LDPC: Training mode.\n");
      trainSwrcGP_LDPC(&swrcGP_LDPC);
      break;
    case 'r': // run the simulation modules
      printf("swrcGP_LDPC: Running simulation mode.\n");
      runSwrcGP_LDPC(&swrcGP_LDPC);
      break;
    case 'h': // print help for all modules
      printf("swrcGP_LDPC: Help.\n");
      helpCommandSwrcGP_LDPC(0);
      break;
    case 's': // save the config file
      printf("swrcGP_LDPC: Save.\n");
      saveSwrcGP_LDPCStruct(&swrcGP_LDPC,"swrcGP_LDPC.cfg");
      break;
    case 'k': // check the parameters
      printf("swrcGP_LDPC: Check parameters.\n");
      checkParametersSwrcGP_LDPC(&swrcGP_LDPC);
      break;
    }
  }

  // Free the uint8Vectors 
  for (i=0;i<4;i++) {
      SWRC_free_uint8_vector(&cfgFile[i]);
  }
  freeSwrcGP_LDPCStruct(&swrcGP_LDPC); 
  exit(0);
}
////////////////////////////////////////
// Functions for dealing with the struct
////////////////////////////////////////
// Initialize the fields in the module structure
// Set pointers to NULL (so they can be called with realloc)
// Initialize the parameters to sane start-up values.
void initSwrcGP_LDPCStruct (swrcGP_LDPCStruct *swrcGP_LDPC) {
  uint8_t *tmp;
  int i;
  tmp=(uint8_t*)swrcGP_LDPC;
  for (i=0;i<sizeof(*swrcGP_LDPC);i++) tmp[i]=0; // zero out the entire structure avoid errors reported by valgrind.
// General housekeeping fields
  swrcGP_LDPC->startTime              = 0;
  swrcGP_LDPC->endTime                = 0;
  swrcGP_LDPC->runTime                = 0;
  swrcGP_LDPC->startTimeString[26]    = ' ';
  swrcGP_LDPC->endTimeString[26]      = ' ';
  swrcGP_LDPC->CPID[99]               = ' ';
  swrcGP_LDPC->dumpEvery              = 3600;
// Fields for running the simulation
  swrcGP_LDPC->K                      = 0;
  swrcGP_LDPC->M                      = 0;
  swrcGP_LDPC->N                      = 0;
  swrcGP_LDPC->numberOfFrames         = 0;
  swrcGP_LDPC->numberOfFrameErrors    = 0;
  swrcGP_LDPC->minNumberOfFrames      = 1000;
  swrcGP_LDPC->minNumberOfFrameErrors = 50;
  swrcGP_LDPC->maxNumberOfFrames      = 10000;
  swrcGP_LDPC->numberOfBits           = 0;
  swrcGP_LDPC->numberOfBitErrors      = 0;
  swrcGP_LDPC->BER                    = 0.0;
  swrcGP_LDPC->FER                    = 0.0;
  initSignalStruct(&swrcGP_LDPC->signal);

  //Initialize each submodule
  initGP_LDPCEncoderStruct(&swrcGP_LDPC->GP_LDPCEncoder);
  initGP_ISIChannelStruct(&swrcGP_LDPC->GP_ISIChannel);
  initGP_ViterbiStruct(&swrcGP_LDPC->GP_Viterbi);
  initGP_LDPCDecoderStruct(&swrcGP_LDPC->GP_LDPCDecoder);
  time(&swrcGP_LDPC->startTime);
}

// Frees up all the memory in the structure
void freeSwrcGP_LDPCStruct (swrcGP_LDPCStruct *swrcGP_LDPC) {
  //Free struct fields
  if (swrcGP_LDPC==NULL) {printf("swrcGP_LDPC=NULL in function freeSwrcGP_LDPCStruct not free'ing\n");return;}
  int i;
  swrcGP_LDPC->startTime        =0;
  swrcGP_LDPC->endTime          =0;
  swrcGP_LDPC->runTime          =0;
  swrcGP_LDPC->startTimeString[26]=' ';
  swrcGP_LDPC->endTimeString[26]=' ';
  swrcGP_LDPC->CPID[99]         =' ';
  swrcGP_LDPC->dumpEvery        =3600;
  swrcGP_LDPC->K                =0;
  swrcGP_LDPC->M                =0;
  swrcGP_LDPC->N                =0;
  swrcGP_LDPC->numberOfFrames   =0;
  swrcGP_LDPC->numberOfFrameErrors=0;
  swrcGP_LDPC->minNumberOfFrames=1000;
  swrcGP_LDPC->minNumberOfFrameErrors=50;
  swrcGP_LDPC->maxNumberOfFrames=10000;
  swrcGP_LDPC->numberOfBits     =0;
  swrcGP_LDPC->numberOfBitErrors=0;
  swrcGP_LDPC->BER              =0.0;
  swrcGP_LDPC->FER              =0.0;
  freeSignalStruct(&swrcGP_LDPC->signal);
  //free(swrcGP_LDPC);swrcGP_LDPC=NULL;

  //Free each submodule
  freeGP_LDPCEncoderStruct(&swrcGP_LDPC->GP_LDPCEncoder);
  freeGP_ISIChannelStruct(&swrcGP_LDPC->GP_ISIChannel);
  freeGP_ViterbiStruct(&swrcGP_LDPC->GP_Viterbi);
  freeGP_LDPCDecoderStruct(&swrcGP_LDPC->GP_LDPCDecoder);
}

// Prints the contents of the structure.
// Used for determining the status of the simulation
// as well as for debugging.
void printSwrcGP_LDPCStruct (swrcGP_LDPCStruct *swrcGP_LDPC, char *name, int index, int pre) {
  int i,j;
  char *preString,*name2;
  if (swrcGP_LDPC==NULL) {printf("%s%s=NULL\n",preString,name);return;}
  preString=(char*)calloc((pre+1),sizeof(char));
  for (i=0;i<pre;i++) preString[i]=' '; preString[i]='\0';
  printf("%s[--%d:%s--------\n",preString,index,name);
// General housekeeping fields
    printf("%s  time_t               %s->startTime=%lu\n",preString,name,swrcGP_LDPC->startTime);      // Print time_t startTime
    printf("%s  time_t               %s->endTime=%lu\n",preString,name,swrcGP_LDPC->endTime);          // Print time_t endTime
    printf("%s  time_t               %s->runTime=%lu\n",preString,name,swrcGP_LDPC->runTime);          // Print time_t runTime
    printf("%s  char                 %s->startTimeString[26]=%c\n",preString,name,swrcGP_LDPC->startTimeString[26]); // Print char startTimeString[26]
    printf("%s  char                 %s->endTimeString[26]=%c\n",preString,name,swrcGP_LDPC->endTimeString[26]); // Print char endTimeString[26]
    printf("%s  char                 %s->CPID[99]=%c\n",preString,name,swrcGP_LDPC->CPID[99]);         // Print char CPID[99]
    printf("%s  int                  %s->dumpEvery=%d\n",preString,name,swrcGP_LDPC->dumpEvery);       // Print int dumpEvery
// Fields for running the simulation
    printf("%s  int                  %s->K=%d\n",preString,name,swrcGP_LDPC->K);                       // Print int K
    printf("%s  int                  %s->M=%d\n",preString,name,swrcGP_LDPC->M);                       // Print int M
    printf("%s  int                  %s->N=%d\n",preString,name,swrcGP_LDPC->N);                       // Print int N
    printf("%s  int                  %s->numberOfFrames=%d\n",preString,name,swrcGP_LDPC->numberOfFrames); // Print int numberOfFrames
    printf("%s  int                  %s->numberOfFrameErrors=%d\n",preString,name,swrcGP_LDPC->numberOfFrameErrors); // Print int numberOfFrameErrors
    printf("%s  int                  %s->minNumberOfFrames=%d\n",preString,name,swrcGP_LDPC->minNumberOfFrames); // Print int minNumberOfFrames
    printf("%s  int                  %s->minNumberOfFrameErrors=%d\n",preString,name,swrcGP_LDPC->minNumberOfFrameErrors); // Print int minNumberOfFrameErrors
    printf("%s  int                  %s->maxNumberOfFrames=%d\n",preString,name,swrcGP_LDPC->maxNumberOfFrames); // Print int maxNumberOfFrames
    printf("%s  long int             %s->numberOfBits=%ld\n",preString,name,swrcGP_LDPC->numberOfBits); // Print long int numberOfBits
    printf("%s  int                  %s->numberOfBitErrors=%d\n",preString,name,swrcGP_LDPC->numberOfBitErrors); // Print int numberOfBitErrors
    printf("%s  double               %s->BER=%lf\n",preString,name,swrcGP_LDPC->BER);                  // Print double BER
    printf("%s  double               %s->FER=%lf\n",preString,name,swrcGP_LDPC->FER);                  // Print double FER
  printf("%s---%d:%s-------]\n",preString,index,name);
  free(preString);
}

// Plot function generates any plots associated with the 
// structure
void plotSwrcGP_LDPCStruct (swrcGP_LDPCStruct *swrcGP_LDPC, const char *filename) {
}

// All the data from all the modules is packed into an
// array of uint8_vectors for saving. One uint8_vector per module. 
// Each uint8_vector contains a stringified version of the
// data in the struct. uint8_vectors are then written to and 
// read from disk by the SWRC_saveuint8_vector and SWRC_loaduint8_vector 
// functions. This function packs struct data into a uint_8_vector
void packSwrcGP_LDPCStruct (swrcGP_LDPCStruct *swrcGP_LDPC, uint8_vector *cfgFile) {
  // Pack struct fields
  int i;
 //General housekeeping fields
  // Pack time_t startTime
  SWRC_packToUint8((uint8_t*)&swrcGP_LDPC->startTime,1,sizeof(time_t),cfgFile);
  // Pack time_t endTime
  SWRC_packToUint8((uint8_t*)&swrcGP_LDPC->endTime,1,sizeof(time_t),cfgFile);
  // Pack time_t runTime
  SWRC_packToUint8((uint8_t*)&swrcGP_LDPC->runTime,1,sizeof(time_t),cfgFile);
  // Pack char startTimeString[26]
  SWRC_packToUint8((uint8_t*)&swrcGP_LDPC->startTimeString[26],1,sizeof(char),cfgFile);
  // Pack char endTimeString[26]
  SWRC_packToUint8((uint8_t*)&swrcGP_LDPC->endTimeString[26],1,sizeof(char),cfgFile);
  // Pack char CPID[99]
  SWRC_packToUint8((uint8_t*)&swrcGP_LDPC->CPID[99],1,sizeof(char),cfgFile);
  // Pack int dumpEvery
  SWRC_packToUint8((uint8_t*)&swrcGP_LDPC->dumpEvery,1,sizeof(int),cfgFile);
 //Fields for running the simulation
  // Pack int K
  SWRC_packToUint8((uint8_t*)&swrcGP_LDPC->K,1,sizeof(int),cfgFile);
  // Pack int M
  SWRC_packToUint8((uint8_t*)&swrcGP_LDPC->M,1,sizeof(int),cfgFile);
  // Pack int N
  SWRC_packToUint8((uint8_t*)&swrcGP_LDPC->N,1,sizeof(int),cfgFile);
  // Pack int numberOfFrames
  SWRC_packToUint8((uint8_t*)&swrcGP_LDPC->numberOfFrames,1,sizeof(int),cfgFile);
  // Pack int numberOfFrameErrors
  SWRC_packToUint8((uint8_t*)&swrcGP_LDPC->numberOfFrameErrors,1,sizeof(int),cfgFile);
  // Pack int minNumberOfFrames
  SWRC_packToUint8((uint8_t*)&swrcGP_LDPC->minNumberOfFrames,1,sizeof(int),cfgFile);
  // Pack int minNumberOfFrameErrors
  SWRC_packToUint8((uint8_t*)&swrcGP_LDPC->minNumberOfFrameErrors,1,sizeof(int),cfgFile);
  // Pack int maxNumberOfFrames
  SWRC_packToUint8((uint8_t*)&swrcGP_LDPC->maxNumberOfFrames,1,sizeof(int),cfgFile);
  // Pack long int numberOfBits
  SWRC_packToUint8((uint8_t*)&swrcGP_LDPC->numberOfBits,1,sizeof(long int),cfgFile);
  // Pack int numberOfBitErrors
  SWRC_packToUint8((uint8_t*)&swrcGP_LDPC->numberOfBitErrors,1,sizeof(int),cfgFile);
  // Pack double BER
  SWRC_packToUint8((uint8_t*)&swrcGP_LDPC->BER,1,sizeof(double),cfgFile);
  // Pack double FER
  SWRC_packToUint8((uint8_t*)&swrcGP_LDPC->FER,1,sizeof(double),cfgFile);
  // signal
  SWRC_packSignalStruct(&swrcGP_LDPC->signal,cfgFile);

  // Pack Submodules
  packGP_LDPCEncoderStruct(&swrcGP_LDPC->GP_LDPCEncoder,&cfgFile[1]);
  packGP_ISIChannelStruct(&swrcGP_LDPC->GP_ISIChannel,&cfgFile[2]);
  packGP_ViterbiStruct(&swrcGP_LDPC->GP_Viterbi,&cfgFile[3]);
  packGP_LDPCDecoderStruct(&swrcGP_LDPC->GP_LDPCDecoder,&cfgFile[4]);
}

// After loading the data back from a .cfg file, the data is unpacked
// back into the struct with this function.
void unpackSwrcGP_LDPCStruct (swrcGP_LDPCStruct *swrcGP_LDPC, uint8_vector *cfgFile) {
  // Unpack struct fields
  int i;
  freeSwrcGP_LDPCStruct(swrcGP_LDPC);
// General housekeeping fields
  // Unpack time_t startTime
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_LDPC->startTime,1,sizeof(time_t),cfgFile);
  // Unpack time_t endTime
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_LDPC->endTime,1,sizeof(time_t),cfgFile);
  // Unpack time_t runTime
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_LDPC->runTime,1,sizeof(time_t),cfgFile);
  // Unpack char startTimeString[26]
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_LDPC->startTimeString[26],1,sizeof(char),cfgFile);
  // Unpack char endTimeString[26]
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_LDPC->endTimeString[26],1,sizeof(char),cfgFile);
  // Unpack char CPID[99]
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_LDPC->CPID[99],1,sizeof(char),cfgFile);
  // Unpack int dumpEvery
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_LDPC->dumpEvery,1,sizeof(int),cfgFile);
// Fields for running the simulation
  // Unpack int K
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_LDPC->K,1,sizeof(int),cfgFile);
  // Unpack int M
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_LDPC->M,1,sizeof(int),cfgFile);
  // Unpack int N
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_LDPC->N,1,sizeof(int),cfgFile);
  // Unpack int numberOfFrames
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_LDPC->numberOfFrames,1,sizeof(int),cfgFile);
  // Unpack int numberOfFrameErrors
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_LDPC->numberOfFrameErrors,1,sizeof(int),cfgFile);
  // Unpack int minNumberOfFrames
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_LDPC->minNumberOfFrames,1,sizeof(int),cfgFile);
  // Unpack int minNumberOfFrameErrors
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_LDPC->minNumberOfFrameErrors,1,sizeof(int),cfgFile);
  // Unpack int maxNumberOfFrames
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_LDPC->maxNumberOfFrames,1,sizeof(int),cfgFile);
  // Unpack long int numberOfBits
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_LDPC->numberOfBits,1,sizeof(long int),cfgFile);
  // Unpack int numberOfBitErrors
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_LDPC->numberOfBitErrors,1,sizeof(int),cfgFile);
  // Unpack double BER
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_LDPC->BER,1,sizeof(double),cfgFile);
  // Unpack double FER
  SWRC_unpackFromUint8((uint8_t*)&swrcGP_LDPC->FER,1,sizeof(double),cfgFile);
  // signal
  SWRC_unpackSignalStruct(&swrcGP_LDPC->signal,cfgFile);

  // Unpack submodules
  unpackGP_LDPCEncoderStruct(&swrcGP_LDPC->GP_LDPCEncoder,&cfgFile[1]);
  unpackGP_ISIChannelStruct(&swrcGP_LDPC->GP_ISIChannel,&cfgFile[2]);
  unpackGP_ViterbiStruct(&swrcGP_LDPC->GP_Viterbi,&cfgFile[3]);
  unpackGP_LDPCDecoderStruct(&swrcGP_LDPC->GP_LDPCDecoder,&cfgFile[4]);
}

// Function for loading the struct
int loadSwrcGP_LDPCStruct (swrcGP_LDPCStruct *swrcGP_LDPC, char *filename) {
  int i;
  uint8_vector cfgFile[5];
  for (i=0;i<5;i++){SWRC_init_uint8_vector(&cfgFile[i]);}
  freeSwrcGP_LDPCStruct(swrcGP_LDPC);
  long int startTime=SWRC_loaduint8_vector(cfgFile,5,"swrcGP_LDPC.cfg");
  if(startTime==1) { // no cfg file found
    return(1);
  }
  unpackSwrcGP_LDPCStruct(swrcGP_LDPC,cfgFile);
  for (i=0;i<5;i++) {SWRC_free_uint8_vector(&cfgFile[i]);}
}

// Function for saving the struct
void saveSwrcGP_LDPCStruct (swrcGP_LDPCStruct *swrcGP_LDPC, char *filename) {
  int i;
  uint8_vector cfgFile[5];
  for (i=0;i<5;i++){SWRC_init_uint8_vector(&cfgFile[i]);}
  packSwrcGP_LDPCStruct(swrcGP_LDPC,cfgFile);
  SWRC_saveuint8_vector(cfgFile,5,"swrcGP_LDPC.cfg",swrcGP_LDPC->startTime);
  for (i=0;i<5;i++) {SWRC_free_uint8_vector(&cfgFile[i]);}
}

// Set parameters (fields) in the structure
// Change the values of fields in the structure
void setParmSwrcGP_LDPCStruct (swrcGP_LDPCStruct *swrcGP_LDPC, char *arg) {
  int i;
  SWRC_removeSpaces(arg);
  // if (SWRC_readSingleArgumentFromString(arg,"startTime",&swrcGP_LDPC->startTime,"%lu")==1) {
  //   printf("startTime=%lu\n",swrcGP_LDPC->startTime);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"endTime",&swrcGP_LDPC->endTime,"%lu")==1) {
  //   printf("endTime=%lu\n",swrcGP_LDPC->endTime);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"runTime",&swrcGP_LDPC->runTime,"%lu")==1) {
  //   printf("runTime=%lu\n",swrcGP_LDPC->runTime);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"startTimeString[26]",&swrcGP_LDPC->startTimeString[26],"%c")==1) {
  //   printf("startTimeString[26]=%c\n",swrcGP_LDPC->startTimeString[26]);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"endTimeString[26]",&swrcGP_LDPC->endTimeString[26],"%c")==1) {
  //   printf("endTimeString[26]=%c\n",swrcGP_LDPC->endTimeString[26]);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"CPID[99]",&swrcGP_LDPC->CPID[99],"%c")==1) {
  //   printf("CPID[99]=%c\n",swrcGP_LDPC->CPID[99]);
  // }
   if (SWRC_readSingleArgumentFromString(arg,"dumpEvery",&swrcGP_LDPC->dumpEvery,"%d")==1) {
     printf("dumpEvery=%d\n",swrcGP_LDPC->dumpEvery);
   }
   if (SWRC_readSingleArgumentFromString(arg,"K",&swrcGP_LDPC->K,"%d")==1) {
     printf("K=%d\n",swrcGP_LDPC->K);
   }
  // if (SWRC_readSingleArgumentFromString(arg,"M",&swrcGP_LDPC->M,"%d")==1) {
  //   printf("M=%d\n",swrcGP_LDPC->M);
  // }
   if (SWRC_readSingleArgumentFromString(arg,"N",&swrcGP_LDPC->N,"%d")==1) {
     printf("N=%d\n",swrcGP_LDPC->N);
   }

   
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfFrames",&swrcGP_LDPC->numberOfFrames,"%d")==1) {
  //   printf("numberOfFrames=%d\n",swrcGP_LDPC->numberOfFrames);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfFrameErrors",&swrcGP_LDPC->numberOfFrameErrors,"%d")==1) {
  //   printf("numberOfFrameErrors=%d\n",swrcGP_LDPC->numberOfFrameErrors);
  // }
   if (SWRC_readSingleArgumentFromString(arg,"minNumberOfFrames",&swrcGP_LDPC->minNumberOfFrames,"%d")==1) {
     printf("minNumberOfFrames=%d\n",swrcGP_LDPC->minNumberOfFrames);
   }
   if (SWRC_readSingleArgumentFromString(arg,"minNumberOfFrameErrors",&swrcGP_LDPC->minNumberOfFrameErrors,"%d")==1) {
     printf("minNumberOfFrameErrors=%d\n",swrcGP_LDPC->minNumberOfFrameErrors);
   }
   if (SWRC_readSingleArgumentFromString(arg,"maxNumberOfFrames",&swrcGP_LDPC->maxNumberOfFrames,"%d")==1) {
     printf("maxNumberOfFrames=%d\n",swrcGP_LDPC->maxNumberOfFrames);
   }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfBits",&swrcGP_LDPC->numberOfBits,"%ld")==1) {
  //   printf("numberOfBits=%ld\n",swrcGP_LDPC->numberOfBits);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"numberOfBitErrors",&swrcGP_LDPC->numberOfBitErrors,"%d")==1) {
  //   printf("numberOfBitErrors=%d\n",swrcGP_LDPC->numberOfBitErrors);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"BER",&swrcGP_LDPC->BER,"%lf")==1) {
  //   printf("BER=%lf\n",swrcGP_LDPC->BER);
  // }
  // if (SWRC_readSingleArgumentFromString(arg,"FER",&swrcGP_LDPC->FER,"%lf")==1) {
  //   printf("FER=%lf\n",swrcGP_LDPC->FER);
  // }
  // setParmSignalStruct(&swrcGP_LDPC->signal, arg);
  if (*arg!='\0') {
    printf("swrcGP_LDPC module: Remaining unknown parms in arg list:%s\n Please correct and run again.\n",arg);exit(-1);
  }
}

// A command comes from the user
// This function processes and executes the command
// some commands need a signal to operate on, which is
// passed via the signalStruct. 
void processCommandSwrcGP_LDPC (swrcGP_LDPCStruct *swrcGP_LDPC, signalStruct *signal, const char *command) {
  char commandParameter[400];
  int i;
  printf("processCommandSwrcGP_LDPC:%s\n",command);
  for(i=0;i<400 && i<strlen(command);) {
    if (SWRC_matchCommand(command,"load",&i,commandParameter,400)==1) {
	loadSwrcGP_LDPCStruct(swrcGP_LDPC,commandParameter);
	continue;
    }

    if (SWRC_matchCommand(command,"print",&i,commandParameter,400)==1) {
	printSwrcGP_LDPCStruct(swrcGP_LDPC,"swrcGP_LDPC",0,0);
	continue;
    }

    if (SWRC_matchCommand(command,"setParm",&i,commandParameter,400)==1) {
	setParmSwrcGP_LDPCStruct(swrcGP_LDPC,commandParameter);
	continue;
    }

    if (SWRC_matchCommand(command,"help",&i,commandParameter,400)==1) {
	helpCommandSwrcGP_LDPC(0);
	continue;
    }

    if (SWRC_matchCommand(command,"run",&i,commandParameter,400)==1) {
	generatePseudoRandomUserBitsSignal(&swrcGP_LDPC->signal,swrcGP_LDPC->K);
	continue;
    }

    if (SWRC_matchCommand(command,"printAllSignals",&i,commandParameter,400)==1) {
	printAllSignals(&swrcGP_LDPC->signal);
	continue;
    }

    if (SWRC_matchCommand(command,"saveSignalBinary",&i,commandParameter,400)==1) {
	saveSignalBinary_wrap(&swrcGP_LDPC->signal,commandParameter);
	continue;
    }

    if (SWRC_matchCommand(command,"loadSignalBinary",&i,commandParameter,400)==1) {
	loadSignalBinary_wrap(&swrcGP_LDPC->signal,commandParameter);
	continue;
    }

    printf("processCommandSwrcGP_LDPC: Unknown command:%s\n",&command[i]);
    break;
  }
}

// Provides instructions on the commands that this module is able to process.
void helpCommandSwrcGP_LDPC (int index) {
  printf("Commands recognized by %d:swrcGP_LDPCStruct:\n",index);
  printf("  \"print();\"        : print the swrcGP_LDPCStruct fields\n");
  printf("  \"setParm(arg);\"   : set the swrcGP_LDPCStruct fields\n");
  printf("  \"help();\"         : display this help screen\n");
  helpCommandGP_LDPCEncoder(1);
  helpCommandGP_ISIChannel(2);
  helpCommandGP_Viterbi(3);
  helpCommandGP_LDPCDecoder(4);
}

// Check that all the parameters needed to run the simulation are present.
// Uncomment any/all variables that _need_ to be present for the simulation to run.
int checkParametersSwrcGP_LDPC (swrcGP_LDPCStruct *swrcGP_LDPC) {
  int output=0;
  output+=checkParametersGP_LDPCEncoder(&swrcGP_LDPC->GP_LDPCEncoder);
  output+=checkParametersGP_ISIChannel(&swrcGP_LDPC->GP_ISIChannel);
  output+=checkParametersGP_Viterbi(&swrcGP_LDPC->GP_Viterbi);
  output+=checkParametersGP_LDPCDecoder(&swrcGP_LDPC->GP_LDPCDecoder);
  if (swrcGP_LDPC->M==0) {output++; printf("swrcGP_LDPC->M needed, but not set\n");}
  if (swrcGP_LDPC->K==0) {output++; printf("swrcGP_LDPC->K needed, but not set\n");}
  if (swrcGP_LDPC->N==0) {output++; printf("swrcGP_LDPC->N needed, but not set\n");}
  if (swrcGP_LDPC->N<swrcGP_LDPC->K || swrcGP_LDPC->N<swrcGP_LDPC->M) {output++; printf("N=%d must be bigger than K=%d and M=%d, but not set\n",swrcGP_LDPC->N,swrcGP_LDPC->K,swrcGP_LDPC->M);}
  if (output==0) printf("All parameters check ok\n"); else printf("swrcGP_LDPC CheckParameters: %d parameters are not properly set\n",output);
  return(output);
}

// Precomputation done just prior to the main for loop
// iterating the BER/FER are put into this subroutine
void precompSwrcGP_LDPC (swrcGP_LDPCStruct *swrcGP_LDPC) {
   swrcGP_LDPC->M=swrcGP_LDPC->N-swrcGP_LDPC->K;    // Calculate Parity bit: M = N - K

  // Pass in N, K and M to Encoder structure
  swrcGP_LDPC->GP_LDPCEncoder.N = swrcGP_LDPC->N;
  swrcGP_LDPC->GP_LDPCEncoder.K = swrcGP_LDPC->K;
  swrcGP_LDPC->GP_LDPCEncoder.M = swrcGP_LDPC->M;

  // Pass in N and R to Channel structure
  swrcGP_LDPC->GP_ISIChannel.N = swrcGP_LDPC->N;
  swrcGP_LDPC->GP_ISIChannel.R = (double) swrcGP_LDPC->K/swrcGP_LDPC->N;

  // Pass in N and R to Channel structure
  swrcGP_LDPC->GP_Viterbi.N = swrcGP_LDPC->N;

  // Pass in N, K and M to Decoder structure
  swrcGP_LDPC->GP_LDPCDecoder.N = swrcGP_LDPC->N;
  swrcGP_LDPC->GP_LDPCDecoder.K = swrcGP_LDPC->K;
  swrcGP_LDPC->GP_LDPCDecoder.M = swrcGP_LDPC->M;
  
  time(&swrcGP_LDPC->startTime);
  time(&swrcGP_LDPC->endTime);
  strncpy(swrcGP_LDPC->startTimeString,ctime(&swrcGP_LDPC->startTime),24);
}

// postComputation, such as freeing up any memory, done after
// the iteration of the BER/FER are put into this subroutine
void postcompSwrcGP_LDPC (swrcGP_LDPCStruct *swrcGP_LDPC, char finishedFlag) {
  char hostname[90];
  if (finishedFlag!=' ') time(&swrcGP_LDPC->endTime);
  swrcGP_LDPC->runTime=swrcGP_LDPC->endTime-swrcGP_LDPC->startTime;
  strncpy(swrcGP_LDPC->endTimeString,ctime(&swrcGP_LDPC->endTime),24);
  gethostname(hostname,90);
  sprintf(swrcGP_LDPC->CPID,"%c%s_%d",finishedFlag,hostname,getpid());
}

// Function called prior to training. Zero out statistics matrices,
// set the i_train index to zero etc...
void pretrainSwrcGP_LDPC (swrcGP_LDPCStruct *swrcGP_LDPC) {
}

// Function called after training. Free allocated memory etc...
void posttrainSwrcGP_LDPC (swrcGP_LDPCStruct *swrcGP_LDPC) {
}

// Some modules have a training phase where modules before them are run
// and statistics collected so the module can run properly.
// This function performs the training for the module then 
// saved back to the .cfg file. 
void trainSwrcGP_LDPC (swrcGP_LDPCStruct *swrcGP_LDPC) {
  int i;
  int idum=1;SWRC_randomize(&idum);
  printf("In trainSwrcGP_LDPC\n");
  pretrainSwrcGP_LDPC(swrcGP_LDPC);
  pretrainGP_LDPCEncoder(&swrcGP_LDPC->GP_LDPCEncoder);
  pretrainGP_ISIChannel(&swrcGP_LDPC->GP_ISIChannel);
  pretrainGP_Viterbi(&swrcGP_LDPC->GP_Viterbi);
  pretrainGP_LDPCDecoder(&swrcGP_LDPC->GP_LDPCDecoder);
  pretrainSwrcGP_LDPC(swrcGP_LDPC);
  if (checkParametersSwrcGP_LDPC(swrcGP_LDPC)>0) {
    printf("Exiting swrcGP_LDPC\n");
    exit(-1);
  }
  while(((swrcGP_LDPC->GP_LDPCEncoder.trainFlag&1)==0) || ((swrcGP_LDPC->GP_ISIChannel.trainFlag&1)==0) || ((swrcGP_LDPC->GP_Viterbi.trainFlag&1)==0) || ((swrcGP_LDPC->GP_LDPCDecoder.trainFlag&1)==0)) {
    //////////////////////////////////
    // 0. generate the pseudorandom bit input
    //////////////////////////////////
    SWRC_printHeader("0. generatePseudoRandomUserBitsSignal");
    generatePseudoRandomUserBitsSignal(&swrcGP_LDPC->signal,swrcGP_LDPC->K);
    //////////////////////////////////
    // 1. train the GP_LDPCEncoder module
    //////////////////////////////////
    SWRC_printHeader("1. GP_LDPCEncoder");
    if (trainGP_LDPCEncoder(&swrcGP_LDPC->GP_LDPCEncoder,&swrcGP_LDPC->signal)==0)
      {freeSignalStruct(&swrcGP_LDPC->signal);continue;}
    //////////////////////////////////
    // 2. train the GP_ISIChannel module
    //////////////////////////////////
    SWRC_printHeader("2. GP_ISIChannel");
    if (trainGP_ISIChannel(&swrcGP_LDPC->GP_ISIChannel,&swrcGP_LDPC->signal)==0)
      {freeSignalStruct(&swrcGP_LDPC->signal);continue;}
    //////////////////////////////////
    // 3. train the GP_Viterbi module
    //////////////////////////////////
    SWRC_printHeader("3. GP_Viterbi");
    if (trainGP_Viterbi(&swrcGP_LDPC->GP_Viterbi,&swrcGP_LDPC->signal)==0)
      {freeSignalStruct(&swrcGP_LDPC->signal);continue;}
    //////////////////////////////////
    // 4. train the GP_LDPCDecoder module
    //////////////////////////////////
    SWRC_printHeader("4. GP_LDPCDecoder");
    if (trainGP_LDPCDecoder(&swrcGP_LDPC->GP_LDPCDecoder,&swrcGP_LDPC->signal)==0)
      {freeSignalStruct(&swrcGP_LDPC->signal);continue;}
    //printAllSignals(&swrcGP_LDPC->signal);//exit(-1);
    freeSignalStruct(&swrcGP_LDPC->signal);
  }
  posttrainGP_LDPCEncoder(&swrcGP_LDPC->GP_LDPCEncoder);
  posttrainGP_ISIChannel(&swrcGP_LDPC->GP_ISIChannel);
  posttrainGP_Viterbi(&swrcGP_LDPC->GP_Viterbi);
  posttrainGP_LDPCDecoder(&swrcGP_LDPC->GP_LDPCDecoder);
  posttrainSwrcGP_LDPC(swrcGP_LDPC);
}

// Count the BER/FER between 2 signals in the signal struct
// obi is the original bit index 
// dbi is the detected bit index
void countBERSwrcGP_LDPC (swrcGP_LDPCStruct *swrcGP_LDPC,int obi, int dbi) {
  int i;
  uint8_t *original, *detected;
  uint8_t frameError=0;
  swrcGP_LDPC->numberOfFrames++;
  swrcGP_LDPC->numberOfBits+=swrcGP_LDPC->K;
  original = (uint8_t*) swrcGP_LDPC->signal.x[obi];
  detected = (uint8_t*) swrcGP_LDPC->signal.x[dbi];
  //for (i=0;i<swrcGP_LDPC->N;i++) printf("%d",original[i]);printf("\n");
  //for (i=0;i<swrcGP_LDPC->N;i++) printf("%d",detected[i]);printf("\n");
  for (i=0;i<swrcGP_LDPC->K;i++) {
    if (original[i]!=detected[i]) {
      if (frameError==0) {
	swrcGP_LDPC->numberOfFrameErrors++;
	frameError=1;
      }
      swrcGP_LDPC->numberOfBitErrors++;
    }
  }
  swrcGP_LDPC->FER = ((double)swrcGP_LDPC->numberOfFrameErrors)/((double)swrcGP_LDPC->numberOfFrames);
  swrcGP_LDPC->BER = ((double)swrcGP_LDPC->numberOfBitErrors)/((double)swrcGP_LDPC->numberOfBits);
  printf("FER : %d/%d = %lf, BER : %d/%ld = %lf\n",swrcGP_LDPC->numberOfFrameErrors,swrcGP_LDPC->numberOfFrames,swrcGP_LDPC->FER,swrcGP_LDPC->numberOfBitErrors,swrcGP_LDPC->numberOfBits,swrcGP_LDPC->BER);
}

// Contribute the fields to the berResultStruct that will be 
// printed in the berResult file. Every module contributes
// its own fields. User has to choose the fields to be saved
// using pushBerResultField() once per field to be added
void initBerResultStructSwrcGP_LDPC (swrcGP_LDPCStruct *swrcGP_LDPC,berResultStruct *berResult,char *berResultFilename) {
  printf("In function initBerResultStructSwrcGP_LDPC\n");
  asprintf(&berResult->berResultFilename,"%s",berResultFilename);
  asprintf(&berResult->lockFilename,"%s.lock",berResultFilename);
  berResult->N_berResultFilename=strlen(berResult->berResultFilename);
  //pushBerResultField(berResult,"startTime","time_t","%10d",&swrcGP_LDPC->startTime);
  //pushBerResultField(berResult,"endTime","time_t","%10d",&swrcGP_LDPC->endTime);
  pushBerResultField(berResult,"runTime","time_t","%7d",&swrcGP_LDPC->runTime);
  pushBerResultField(berResult,"N","int","%5d",&swrcGP_LDPC->N);
  pushBerResultField(berResult,"M","int","%4d",&swrcGP_LDPC->M);
  pushBerResultField(berResult,"K","int","%4d",&swrcGP_LDPC->K);
  pushBerResultField(berResult,"#Frames","int","%7d",&swrcGP_LDPC->numberOfFrames);
  pushBerResultField(berResult,"#FramesErr","int","%10d",&swrcGP_LDPC->numberOfFrameErrors);
  pushBerResultField(berResult,"#Bits","long int","%10ld",&swrcGP_LDPC->numberOfBits);
  pushBerResultField(berResult,"#BitErr","int","%7d",&swrcGP_LDPC->numberOfBitErrors);
  pushBerResultField(berResult,"FER","double","%10.8lf",&swrcGP_LDPC->FER);
  pushBerResultField(berResult,"BER","double","%10.8lf",&swrcGP_LDPC->BER);
  initBerResultStructGP_LDPCEncoder(&swrcGP_LDPC->GP_LDPCEncoder,berResult);
  initBerResultStructGP_ISIChannel(&swrcGP_LDPC->GP_ISIChannel,berResult);
  initBerResultStructGP_Viterbi(&swrcGP_LDPC->GP_Viterbi,berResult);
  initBerResultStructGP_LDPCDecoder(&swrcGP_LDPC->GP_LDPCDecoder,berResult);  
  pushBerResultField(berResult,"StartSimDateTime","char*","%26s",&swrcGP_LDPC->startTimeString);
  pushBerResultField(berResult,"EndSimDateTime","char*","%26s",&swrcGP_LDPC->endTimeString);
  pushBerResultField(berResult,"CPID","char*","%37s",&swrcGP_LDPC->CPID);
}

// Finally when everything is in place, the module must be
// run during the actual simulation. The code for running
// the module is in this function.
void runSwrcGP_LDPC (swrcGP_LDPCStruct *swrcGP_LDPC) {
  int i;
  berResultStruct berResult;
  int idum=1;SWRC_randomize(&idum);
  initBerResultStruct(&berResult);
  printf("In runSwrcGP_LDPC\n");
  precompSwrcGP_LDPC(swrcGP_LDPC);
  precompGP_LDPCEncoder(&swrcGP_LDPC->GP_LDPCEncoder);
  precompGP_ISIChannel(&swrcGP_LDPC->GP_ISIChannel);
  precompGP_Viterbi(&swrcGP_LDPC->GP_Viterbi);
  precompGP_LDPCDecoder(&swrcGP_LDPC->GP_LDPCDecoder);
  precompSwrcGP_LDPC(swrcGP_LDPC);
  initBerResultStructSwrcGP_LDPC(swrcGP_LDPC,&berResult,"swrcGP_LDPC.berResult");
  if (checkParametersSwrcGP_LDPC(swrcGP_LDPC)>0) {
    printf("Exiting swrcGP_LDPC\n");
    exit(-1);
  }
  for (swrcGP_LDPC->numberOfFrames=0,swrcGP_LDPC->numberOfBits=0;(swrcGP_LDPC->numberOfFrames<swrcGP_LDPC->minNumberOfFrames || swrcGP_LDPC->numberOfFrameErrors<swrcGP_LDPC->minNumberOfFrameErrors) && (swrcGP_LDPC->numberOfFrames<swrcGP_LDPC->maxNumberOfFrames);) {
    //////////////////////////////////
    // 0. generate the pseudorandom bit input
    //////////////////////////////////
    SWRC_printHeader("0. generatePseudoRandomUserBitsSignal");
    generatePseudoRandomUserBitsSignal(&swrcGP_LDPC->signal,swrcGP_LDPC->K);
    //printAllSignals(&swrcGP_LDPC->signal);
    //printAllSignals(&swrcGP_LDPC->signal);//exit(-1);
    //////////////////////////////////
    // 1. run the GP_LDPCEncoder module
    //////////////////////////////////
    SWRC_printHeader("1. GP_LDPCEncoder");
    runGP_LDPCEncoder(&swrcGP_LDPC->GP_LDPCEncoder,&swrcGP_LDPC->signal);
    //printAllSignals(&swrcGP_LDPC->signal);
    //////////////////////////////////
    // 2. run the GP_ISIChannel module
    //////////////////////////////////
    SWRC_printHeader("2. GP_ISIChannel");
    runGP_ISIChannel(&swrcGP_LDPC->GP_ISIChannel,&swrcGP_LDPC->signal);
    //printAllSignals(&swrcGP_LDPC->signal);
    //////////////////////////////////
    // 3. run the GP_Viterbi module
    //////////////////////////////////
    SWRC_printHeader("3. GP_Viterbi");
    runGP_Viterbi(&swrcGP_LDPC->GP_Viterbi,&swrcGP_LDPC->signal);
    //printAllSignals(&swrcGP_LDPC->signal);
    //////////////////////////////////
    // 4. run the GP_LDPCDecoder module
    //////////////////////////////////
    SWRC_printHeader("4. GP_LDPCDecoder");
    runGP_LDPCDecoder(&swrcGP_LDPC->GP_LDPCDecoder,&swrcGP_LDPC->signal);
    //printAllSignals(&swrcGP_LDPC->signal);//exit(-1);
    //////////////////////////////////
    // 5. Count BER
    //////////////////////////////////
    SWRC_printHeader("5. Count BER");
    countBERSwrcGP_LDPC(swrcGP_LDPC,0,4); //exit(-1);// Count the bit/frame errors. "1" and "5" are the indices of the 2 signals being compared and are hard-coded. User must set these values appropriately for their simulation.
    postcompSwrcGP_LDPC(swrcGP_LDPC,' '); // ' ' is a flag indicating this simulation is still ongoing
    saveBerResultFile(&berResult,&swrcGP_LDPC->startTime,&swrcGP_LDPC->endTime,&swrcGP_LDPC->runTime,swrcGP_LDPC->dumpEvery); // Try to save berResult
    freeSignalStruct(&swrcGP_LDPC->signal);
  }
  postcompGP_LDPCEncoder(&swrcGP_LDPC->GP_LDPCEncoder,'*');
  postcompGP_ISIChannel(&swrcGP_LDPC->GP_ISIChannel,'*');
  postcompGP_Viterbi(&swrcGP_LDPC->GP_Viterbi,'*');
  postcompGP_LDPCDecoder(&swrcGP_LDPC->GP_LDPCDecoder,'*');
  postcompSwrcGP_LDPC(swrcGP_LDPC,'*'); // '*' is a flag indicating this simulation is finished
  saveBerResultFile(&berResult,&swrcGP_LDPC->startTime,&swrcGP_LDPC->endTime,&swrcGP_LDPC->runTime,0); //force save of berResult.
  freeBerResultStruct(&berResult);	
}


