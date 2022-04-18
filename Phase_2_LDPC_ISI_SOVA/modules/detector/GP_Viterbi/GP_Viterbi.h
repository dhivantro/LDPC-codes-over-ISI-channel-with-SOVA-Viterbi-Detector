// Software Recording Channel (SWRC) platform in C.
// Name      : GP_Viterbi
// Type      : module.
// Path      : modules/detector/GP_Viterbi
// Dependency: 
// Version   : 1.0
// Author(s) : Kheong Sann Chan.
// Date      : Mon Mar 28 17:14:28 2022
// Comment   : Viterbi detector parameters 

#ifndef GP_VITERBI_H
#define GP_VITERBI_H
#include "../../SWRC.h"


typedef struct GP_ViterbiStruct {
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fields entered by the user during module creation (saved to .cfg file, and initialized by init routine)
///////////////////////////////////////////////////////////////////////////////////////////////////////////
  int N;                              // Number of taps in the Viterbi target
  double *h;                          // coefficients of the Viterbi target
  int N_h;                            // Length of h
  double *sk;                         // noise-free channel-outputs of the ISI channel
  int N_sk;                           // Length of Sk table
  int Ns;                             // number of elements in the vector sk (32)
  double SNR;                         // The SNR of the noise on the AWGN channel
///////////////////////////////////////////////////////////////////////
// Fields automatically included in every module that request $args{i}
///////////////////////////////////////////////////////////////////////
  uint8_t trainFlag;                  // Flag indicating training status
  long int N_train;                   // # training iterations
  long int i_train;                   // Training counter
  long unsigned int numberOfMult;     // Number of multiplications for the module
  double aveNoOfMultPerFrame;         // Average number of multiplications per frame
  long unsigned int numberOfAdd;      // Number of additions for the module
  double aveNoOfAddPerFrame;          // Average number of additions per frame
  long unsigned int numberOfComp;     // Number of compares for the module
  double aveNoOfCompPerFrame;         // Average number of compares per frame
  double simTime;                     // Total time for running the current module's compute engine
  double aveSimTimePerFrame;          // Average simulation time per frame
  long unsigned int numberOfCalls;    // Number of times this subroutine is called
} GP_ViterbiStruct;

typedef struct arrayGP_ViterbiStruct {
  GP_ViterbiStruct *x;
  long unsigned int N_x;
} arrayGP_ViterbiStruct;

typedef struct doubleArrayGP_ViterbiStruct {
  GP_ViterbiStruct **x;
  long unsigned int *N_x;
  long unsigned int N_N_x;
} doubleArrayGP_ViterbiStruct;

// Print the double *sk struct
void printSkGP_ViterbiStruct(GP_ViterbiStruct *GP_Viterbi);

// Free the memory allocated to double *sk
void freeSkGP_ViterbiStruct(GP_ViterbiStruct *GP_Viterbi);

// Allocate memory for double *sk
void allocateSkGP_ViterbiStruct(GP_ViterbiStruct *GP_Viterbi);

// Print the double *h struct
void printHGP_ViterbiStruct(GP_ViterbiStruct *GP_Viterbi);

// Free the memory allocated to double *h
void freeHGP_ViterbiStruct(GP_ViterbiStruct *GP_Viterbi);

// Allocate memory for double *h
void allocateHGP_ViterbiStruct(GP_ViterbiStruct *GP_Viterbi);

// Initialize the fields in the module structure
// Set pointers to NULL (so they can be called with realloc)
// Initialize the parameters to sane start-up values.
void initGP_ViterbiStruct(GP_ViterbiStruct *GP_Viterbi);

// Frees up all the memory in the structure
void freeGP_ViterbiStruct(GP_ViterbiStruct *GP_Viterbi);

// Prints the contents of the structure.
// Used for determining the status of the simulation
// as well as for debugging.
void printGP_ViterbiStruct(GP_ViterbiStruct *GP_Viterbi, char *name, int index, int pre);

// Store random values into the fields of GP_ViterbiStruct.
// For testing that saving to .cfg file works.
// User should help to write appropriate random-generating values
// to be stored in the appropriate fields.
void randomizeGP_ViterbiStruct(GP_ViterbiStruct *GP_Viterbi);

// Initialize an array of GP_ViterbiStruct's to sane starting values
void initArrayGP_ViterbiStruct(arrayGP_ViterbiStruct *GP_Viterbi);

// Allocate memory for an array of N GP_ViterbiStruct's
void allocateArrayGP_ViterbiStruct(arrayGP_ViterbiStruct *GP_Viterbi,int N);

// Free an array of GP_ViterbiStruct's
void freeArrayGP_ViterbiStruct(arrayGP_ViterbiStruct *GP_Viterbi);

// Fill the arrayGP_ViterbiStruct with random values.
// The GP_Viterbi->N_GP_Viterbi parameter 
// must be set to the number of elements in the array.
// Array must be allocated before calling this function.
void randomizeArrayGP_ViterbiStruct(arrayGP_ViterbiStruct *GP_Viterbi);

// Print arrayGP_ViterbiStruct
void printArrayGP_ViterbiStruct(arrayGP_ViterbiStruct *GP_Viterbi);

// Initialize a double array of GP_ViterbiStruct to sane startup values
void initDoubleArrayGP_ViterbiStruct(doubleArrayGP_ViterbiStruct *GP_Viterbi);

// Allocate memory for a rectangular double array of GP_ViterbiStruct
void allocateDoubleArrayGP_ViterbiStruct(doubleArrayGP_ViterbiStruct *GP_Viterbi, int N, int M);

// Free a double array of GP_ViterbiStruct's
void freeDoubleArrayGP_ViterbiStruct(doubleArrayGP_ViterbiStruct *GP_Viterbi);

// Print arrayGP_ViterbiStruct
void printDoubleArrayGP_ViterbiStruct(doubleArrayGP_ViterbiStruct *GP_Viterbi, char *name, int index, int pre);

// Plot function generates any plots associated with the 
// structure
void plotGP_ViterbiStruct(GP_ViterbiStruct *GP_Viterbi, const char *filename);

// All the data from all the modules is packed into an
// array of uint8_vectors for saving. One uint8_vector per module. 
// Each uint8_vector contains a stringified version of the
// data in the struct. uint8_vectors are then written to and 
// read from disk by the SWRC_saveuint8_vector and SWRC_loaduint8_vector 
// functions. This function packs struct data into a uint_8_vector
void packGP_ViterbiStruct(GP_ViterbiStruct *GP_Viterbi, uint8_vector *cfgFile);

// After loading the data back from a .cfg file, the data is unpacked
// back into the struct with this function.
void unpackGP_ViterbiStruct(GP_ViterbiStruct *GP_Viterbi, uint8_vector *cfgFile);

// Pack the contents of arrayGP_ViterbiStruct to a uint8_vector
void packArrayGP_ViterbiStruct(arrayGP_ViterbiStruct *GP_Viterbi, uint8_vector *cfgFile);

// Unpack the contents of arrayGP_ViterbiStruct from a uint8_vector.
void unpackArrayGP_ViterbiStruct(arrayGP_ViterbiStruct *GP_Viterbi, uint8_vector *cfgFile);

// Pack the contents of doubleArrayGP_ViterbiStruct to a uint8_vector
void packDoubleArrayGP_ViterbiStruct(doubleArrayGP_ViterbiStruct *GP_Viterbi, uint8_vector *cfgFile);

// Unpack the contents of doubleArrayGP_ViterbiStruct from a uint8_vector
void unpackDoubleArrayGP_ViterbiStruct(doubleArrayGP_ViterbiStruct *GP_Viterbi, uint8_vector *cfgFile);

// Function for loading the struct
int loadGP_ViterbiStruct(GP_ViterbiStruct *GP_Viterbi, char *filename);

// Function for saving the struct
void saveGP_ViterbiStruct(GP_ViterbiStruct *GP_Viterbi, char *filename);

// Set parameters (fields) in the structure
// Change the values of fields in the structure
void setParmGP_ViterbiStruct(GP_ViterbiStruct *GP_Viterbi, char *arg);

// A command comes from the user
// This function processes and executes the command
// some commands need a signal to operate on, which is
// passed via the signalStruct. 
void processCommandGP_Viterbi(GP_ViterbiStruct *GP_Viterbi, signalStruct *signal, const char *command);

// Provides instructions on the commands that this module is able to process.
void helpCommandGP_Viterbi(int index);

// Check that all the parameters needed to run the simulation are present.
// Uncomment any/all variables that _need_ to be present for the simulation to run.
int checkParametersGP_Viterbi(GP_ViterbiStruct *GP_Viterbi);

// Precomputation done just prior to the main for loop
// iterating the BER/FER are put into this subroutine
void precompGP_Viterbi(GP_ViterbiStruct *GP_Viterbi);

// postComputation, such as freeing up any memory, done after
// the iteration of the BER/FER are put into this subroutine
void postcompGP_Viterbi(GP_ViterbiStruct *GP_Viterbi, char finishedFlag);

// Function called prior to training. Zero out statistics matrices,
// set the i_train index to zero etc...
void pretrainGP_Viterbi(GP_ViterbiStruct *GP_Viterbi);

// Function called after training. Free allocated memory etc...
void posttrainGP_Viterbi(GP_ViterbiStruct *GP_Viterbi);

// Some modules have a training phase where modules before them are run
// and statistics collected so the module can run properly.
// This function performs the training for the module then 
// saved back to the .cfg file.
// Returns 1 if training is complete
// Returns 0 otherwise
int trainGP_Viterbi(GP_ViterbiStruct *GP_Viterbi, signalStruct *signal);

// Contribute the fields to the berResultStruct that will be 
// printed in the berResult file. Every module contributes
// its own fields. User has to choose the fields to be saved
// using pushBerResultField() once per field to be added
void initBerResultStructGP_Viterbi(GP_ViterbiStruct *GP_Viterbi,berResultStruct *berResult);

// Finally when everything is in place, the module must be
// run during the actual simulation. The code for running
// the module is in this function.
void runGP_Viterbi(GP_ViterbiStruct *GP_Viterbi, signalStruct *signal);

#endif
