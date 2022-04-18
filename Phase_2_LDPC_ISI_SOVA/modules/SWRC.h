#ifndef SWRC_H
#define SWRC_H
#define _GNU_SOURCE    // needed to suppress implicit asprintf warning
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <regex.h>
#include <math.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h> // needed for mkdir
///////////////////////////
// typedef struct for uint8_vector
///////////////////////////
typedef struct uint8_vector {
  int N;                    // Length of vector
  long unsigned int offset; // an offset into *x. Used during unpack function.
  uint8_t *x;               // Elements of the vector
} uint8_vector;
typedef struct coordInt {
  int x;
  int y;
} coordInt;
void SWRC_init_uint8_vector(uint8_vector *x);
void SWRC_print_uint8_vector(uint8_vector *x,char *name);
void SWRC_free_uint8_vector(uint8_vector *x);

typedef struct signalStruct {
//////////////////////////////
// Fields entered by the user
//////////////////////////////
  long unsigned int N_N;              // Length of *N
  long unsigned int *N;               // Length of **x
  uint8_t **x;                        // A vector of signals
  long unsigned int N_N_name;         // Length of *N_name
  long unsigned int *N_name;          // Length of **name
  char **name;                        // name of module that generated this signal
  long unsigned int N_type;           // Length of *type
  uint8_t *type;                      // type of each array. 0=uint8_t, 1=char, 2=int, 3=unsigned int, 4=long unsigned int, 5=float, 6=double
} signalStruct;

#include "berResult/berResult.h"

///////////////////////////////////////////
// Functions for dealing with the cfg file
///////////////////////////////////////////
int SWRC_packStruct(uint8_t *sourceStruct, int N, uint8_vector *cfgFile);
int SWRC_unpackStruct(uint8_t *destStruct, int N, uint8_vector *cfgFile);
int SWRC_packVect(uint8_t *vect, int N, int unitSize, uint8_vector *cfgFile);
int SWRC_unpackVect(uint8_t *vect, int N, int unitSize, uint8_t *cfgFile);
int SWRC_packToUint8(uint8_t *vect, int N, int unitSize, uint8_vector *cfgFile);
int SWRC_unpackFromUint8(uint8_t *vect, int N, int unitSize, uint8_vector *cfgFile);
int SWRC_allocateMemAndUnpackFromUint8(uint8_t **output, int N, int unitSize, uint8_vector *cfgFile);
int SWRC_packStringToUint8(char **string, uint8_vector *cfgFile);
int SWRC_unpackStringFromUint8(char **string, uint8_vector *cfgFile);
int SWRC_packStringArrayToUint8(char ***string, int *Ns, uint8_vector *cfgFile);
int SWRC_unpackStringArrayFromUint8(char ***string, int *Ns, uint8_vector *cfgFile);
int SWRC_checkVectorWithDefault(uint8_t **vect, int N, uint8_t *defaul, int unitSize,int (*IsOK)(uint8_t *x));
void SWRC_extendPrintStructName(char *output, const char *input, const char *ext);
void SWRC_saveuint8_vector(uint8_vector *x, int N, char *filename,time_t startTime);
long int SWRC_loaduint8_vector(uint8_vector *x, int N, char *filename);
void SWRC_getDirnameFilenameFilenumFileext(char *ifn, char **dirname,char **filename,char **fileNum, char **fileExt);
long int SWRC_loadcfgFile(uint8_vector *cfgFile, int N,char *filename);

/////////////////////////////////////////
// Functions for handling command strings
/////////////////////////////////////////
//int SWRC_copyStringUptoNextDelimiter(char *output,int N_output, const char *commandString);
int SWRC_matchCommand(const char *command, const char *toMatch, int *index,char *commandParameter,int N_cp);
int SWRC_getNextArgument(const char *CSV_parm,int *index,int *nextEqualSign, const char *argName);
void SWRC_removeSpaces(char *string);
int SWRC_readSingleArgumentFromString(char *arg, const char *stringName, void *output, const char *formatString);
void SWRC_deleteArgumentFromString(char *arg, int i, int j);
int SWRC_readMultipleArgumentsFromString(char *arg, const char *stringName, void **output, long unsigned int *N,int unitSize, const char *formatString);
int SWRC_readStringArgumentFromString(char *arg, const char *stringName, void **output, long unsigned int *N, const char *formatString);
int SWRC_readDateArgumentFromString(char *arg, const char *stringName, struct tm *output);
int SWRC_readTimeArgumentFromString(char *arg, const char *stringName, struct tm *output);
bool SWRC_ifAnyChar(char *s, char c);
char *SWRC_appendExtToString();
/////////////////////////////////////////
// Functions for random number generation
/////////////////////////////////////////
void SWRC_randomize(int *idum);
float SWRC_ran1(int *idum);
float SWRC_ran0(int *idum);
double SWRC_ran2(int *idum);
float SWRC_randn(int *idum);
int SWRC_log2(int N);
int SWRC_irbit2(unsigned long *iseed);
float SWRC_normalDist(float mean, float sigma_percent, int *idum);
/////////////////////////////////////////
// Functions for doubleArrays
/////////////////////////////////////////
void SWRC_pushNewEntryToDoubleArray();
long int SWRC_getArraySizeFromNdims(int nDims,int N0, int N1, int N2, int N3);

/////////////////////////////////////////
// Functions for running the simulation
/////////////////////////////////////////
void SWRC_printHeader(char *moduleName);//print a header for each module during running
int SWRC_mod(double x, int lim);
double SWRC_gaussian2D(double y, double x, double sigmaY, double sigmaX);
////////////////////////////////////////
// Functions for getting the time/date//
////////////////////////////////////////
char *SWRC_getTimeString();
void SWRC_printTimet(time_t *t,char *timeName);

////////////////////////////////////////
// Functions for manipulating filenames of the codes
////////////////////////////////////////
void SWRC_checkCodeDirExistenceAndCopyName(const char *filename, char **filaname2);
int SWRC_countFileLines(char *filename);
////////////////////////////////////////
// Functions for drawing latex docs to a file
////////////////////////////////////////
void SWRC_fwriteLatexFileHeader(FILE *f);
void SWRC_fwriteLatexFileHeaderArticle(FILE *f);
void SWRC_fwriteLatexBeginDocument(FILE *f);
void SWRC_fwriteLatexEndDocument(FILE *f);
void SWRC_fwriteLatexBeginFrame(FILE *f,char *frameTitle, char *options);
void SWRC_fwriteLatexEndFrame(FILE *f);
void SWRC_fwriteLatexBeginTikzPicture(FILE *f,const char *options);
void SWRC_fwriteLatexBoundingBox(FILE *f,float xmin,float ymin,float xmax,float ymax);
void SWRC_fwriteLatexEndTikzPicture(FILE *f);
void SWRC_typesetTexFile(char *filename);
////////////////////////////////////////
// Functions for coordInt
////////////////////////////////////////

////////////////////////////////////////
// Functions zero'ing out a chunk of memory
////////////////////////////////////////
void SWRC_zeroOutMem(uint8_t *p, long unsigned int N);

////////////////////////////////////////
// Sorting routines
////////////////////////////////////////
void SWRC_getIntegerPermutation(unsigned long int n, int *arr, unsigned int *indx);
int SWRC_HammingDistance(uint8_t *s1, uint8_t *s2, int N);

////////////////////////////////////////
// matrix routines
////////////////////////////////////////
// allocate memory for a double matrix
typedef struct doubleMatrix {
  double **x;  // element of the double matrix
  int Nrow;    // number of rows in the double matrix
  int Ncol;    // number of cols in the double matrix;
} doubleMatrix;
void SWRC_allocDoubleMatrix(doubleMatrix *C, int Nrow, int Ncol);
void SWRC_printDoubleMatrix(doubleMatrix *C, char *format);
void SWRC_printDoubleMatrixSquared(doubleMatrix *C,char *format);
void SWRC_copyDoubleMatrix(doubleMatrix *A, doubleMatrix *B);
void SWRC_matAdd_inplace(doubleMatrix *A, doubleMatrix *B);
void SWRC_matMult_inplace(doubleMatrix *A, doubleMatrix *B, int flag);
void SWRC_matMultConst_inplace(doubleMatrix *A, double B);
void SWRC_addIdent_inplace(doubleMatrix *A, double b);
void SWRC_matTranspose_inplace(doubleMatrix *A);
void SWRC_normalizeCols_inplace(doubleMatrix *A);
void SWRC_diagonalizeCorrMatrix(double C1, double C2, doubleMatrix *V, doubleMatrix *L);
void SWRC_ludcmp(double **A, int n, int *indx, float *d);
void SWRC_LUDcmpDoubleMatrix(doubleMatrix *A, int *indx);
void SWRC_lubksb(double **A, int n, int *indx, double *b);
void SWRC_LUBksbDoubleMatrix(doubleMatrix *A, doubleMatrix *b, int *indx);
int SWRC_packDoubleMatrixToUint8(doubleMatrix *A, uint8_vector *cfgFile);
int SWRC_unpackDoubleMatrixFromUint8(doubleMatrix *A, uint8_vector *cfgFile);
void SWRC_freeDoubleMatrix(doubleMatrix *C);
/////////////////////////////////////////////////
// functions for handling .out, .bit files etc...
// Needed for interacting with external files
// when collaborating with Simon.
/////////////////////////////////////////////////
void SWRC_readOutFile(char *basename, char *dir, signalStruct *signal);
void SWRC_readSOutFile(char *basename, char *dir, signalStruct *signal);
void SWRC_readBitFile(char *basename, char *dir, signalStruct *signal);
void SWRC_saveSoutFile(char *basename, char *dir, signalStruct *signal,int sigIndex,int delay);
void SWRC_octavePlotOutSout(char *basename);
void SWRC_saveDetBitFile(char *basename, char *dir, signalStruct *signal,int sigIndex,int delay);
void SWRC_saveSNRFile(char *basename, char *dir, signalStruct *signal,int rIndex, int sIndex,int delay);
void SWRC_saveHFile(char *basename, char *dir, double *h, long unsigned int Nh, int hInd);
void SWRC_loadHFile(char *filename, char *dir, double **h, long unsigned int *Nh);
/////////////////////////////////////////////////
// mkchdir and unmkchdir functions
/////////////////////////////////////////////////
int SWRC_mkchdir_obsolete(char *dirName, int dirNum, char *ext, char **cwd, uint8_t ssd);
int SWRC_mkchdir_obsolete2(char *baseName, int N, char *subDirName, char **cwd, uint8_t ssd);
int SWRC_mkchdir(char *dirName, char *subDirName, char **cwd, uint8_t ssd);
//void SWRC_getSubDirName2(char **dirName2, char *dirName, int dirNum, char *ext);
void SWRC_getSubDirName2(char **dirName2, char *dirName, int dirNum);
void SWRC_unmkchdir(char **cwd);
int SWRC_getBasenameNum(char *filename, char **basename, char **dirname, int *num);
int SWRC_getSubDirNum(char *basename);
/////////////////////////////////////////////////
// loadQ functions for polar Code
/////////////////////////////////////////////////
// load the reliability sequence from a .mat file
void SWRC_loadQ(int **Q ,int N,char *rsFilename);
void SWRC_getRS(int **Q, int N);
int SWRC_isFrozen(int index, int *Q, int N, int N_K);
///////////////////////////////////////////////
// Everything from signals.c is put below here.
///////////////////////////////////////////////
// Initialize the fields in the module structure
// Set pointers to NULL (so they can be called with realloc)
// Initialize the parameters to sane start-up values.
// Function called each time structure is instantiated.
void initSignalStruct(signalStruct *signal);

// Prints the contents of the structure. 
// Used for determining the status of the simulation
// as well as for debugging.
void printSignalStruct(signalStruct *signal, char *name, int index, int pre);
// The previous function didn't seem to work, so the function
// has been rewritten to just print the pertinent information
// in the function printAllSignals.
void printAllSignals(signalStruct *signal);
// Print signals only in the range startIndex to stopIndex
void printSignalRange(signalStruct *signal,int startIndex,int stopIndex);

// Plot function generates any plots associated with the 
// structure
void plotSignal(signalStruct *signal);

// All the data from all the modules is packed into an
// array of uint8_vectors for saving. One uint8_vector per module. 
// Each uint8_vector contains a stringified version of the
// data in the struct. uint8_vectors are then written to and 
// read from disk by the saveuint8_vector and loaduint8_vector 
// functions. This function packs struct data into a uint_8_vector
void SWRC_packSignalStruct(signalStruct *signal, uint8_vector *cfgFile);

// After loading the data back from a .cfg file, the data is unpacked
// back into the struct with this function.
void SWRC_unpackSignalStruct(signalStruct *signal, uint8_vector *cfgFile);

// Function for loading the struct
int loadSignalStruct(signalStruct *signal, const char *filename);

// Function for saving the struct
void saveSignalStruct(signalStruct *signal, const char *filename,int *col,int Ncols);
void saveSignalBinary(signalStruct *signal, char *filename);
void saveSignalBinary_wrap(signalStruct *signal, char *arg);
int loadSignalBinary(signalStruct *signal, char *filename);
void loadSignalBinary_wrap(signalStruct *signal, char *arg);
void loadIndividualUint8Signal(signalStruct *signal,char *filename, int signalIndex);
void saveDoubleSignalTxt(signalStruct *signal, int sigIndex, char *filename);
// The counter part to the init function. Frees up all the memory 
// in the structure
void freeSignalStruct(signalStruct *signal);

// Set parameters (fields) in the structure
// Change the values of fields in the structure
void setParmSignalStruct(signalStruct *signal, char *arg);

// A command comes from the user
// This function processes the command, sets variables, 
// carries out the printing or plotting, etc...
void processCommandSignal(signalStruct *signal, const char *command);

// Provides instructions on the commands that this module is able to process.
void helpCommandSignal(int index);

// Some modules require a precomputation phase, perhaps 
// done after the training, perhaps without training. 
// That precomputation function is done here
void precompSignal(signalStruct *signal);

// Some modules have a training phase where modules before them are run
// and statistic collected so the module can run properly.
// This function performs the training for the module then 
// saved back to the .cfg file. 
void trainSignal(signalStruct *signal);

// Finally when everything is in place, the module must be
// run during the actual simulation. The code for running
// the module is in this function.
void runSignal(signalStruct *signal);

// Increment the list of vectors signal->x by 1 vector
// of size N. Push this vector onto the end of the **vector->x list.
// *signal is the signalStruct array 
uint8_t *incrementByOneSignal(signalStruct *signal,int N,uint8_t type,const char *moduleName);

// generate a sequence of random bits for vector of type uint8_t
// in the signals array. Since the bits are only 0 or 1, they fit
// inside uint8. Length of vector is N
void generatePseudoRandomUserBitsSignal(signalStruct *signal, int N);
// get a signal consisting of the index'th unity vector
// which is zeros everywhere except in the index position.
void SWRC_signal_getUnitVector(signalStruct *signal, int index, int N);

// create a new signal on the signal stack and copy the double array *x there.
void cpDoubleToSignal(signalStruct *signal, double *x, int N,char *descriptionString);

// Given a type code, return the sizeof this type
int getUnitSizeFromType(uint8_t type);
void appendSNRHToSignal(double SNR, int Nh, float *h, signalStruct *signal, int signalIndex);
void extractSNRHFromSignal(double *SNR, int *N_h, float **h, signalStruct *signal, int signalIndex);

// Upsample a signal in-place
void signal_upsample_signal_inplace(signalStruct *signal,int index,int U);
///////////////////////////////////////////////
// Routines to help create PBM/PNG files.
///////////////////////////////////////////////
void SWRC_printPBMHeader(FILE *f, int N, int M);
int SWRC_findLastSlash(char *filename);
#endif
