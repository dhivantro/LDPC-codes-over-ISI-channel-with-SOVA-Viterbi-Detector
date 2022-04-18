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

#include "../modules/SWRC.h"
#include "../modules/encoder/GP_LDPCEncoder/GP_LDPCEncoder.h"
#include "../modules/channel/GP_ISIChannel/GP_ISIChannel.h"
#include "../modules/detector/GP_Viterbi/GP_Viterbi.h"
#include "../modules/decoder/GP_LDPCDecoder/GP_LDPCDecoder.h"
typedef struct swrcGP_LDPCStruct {
///////////////////////////////
// Channel module substructures
///////////////////////////////
  GP_LDPCEncoderStruct GP_LDPCEncoder; // Structure for GP_LDPCEncoder
  GP_ISIChannelStruct GP_ISIChannel;  // Structure for GP_ISIChannel
  GP_ViterbiStruct GP_Viterbi;        // Structure for GP_Viterbi
  GP_LDPCDecoderStruct GP_LDPCDecoder; // Structure for GP_LDPCDecoder
///////////////////////////////
// General housekeeping fields
///////////////////////////////
  time_t startTime;                   // Start time of the simulation
  time_t endTime;                     // End time of the simulation
  time_t runTime;                     // run time of the simulation
  char startTimeString[26];           // The start time in string format
  char endTimeString[26];             // The end time in string format
  char CPID[99];                      // computer/process ID
  int dumpEvery;                      // dump to berResult file every dumpEvery secs
/////////////////////////////////////
// Fields for running the simulation
/////////////////////////////////////
  int K;                              // Length of user word before coding 
  int M;                              // Number of parity check bits 
  int N;                              // Length of code word after coding 
  int numberOfFrames;                 // Number of frames executed in the simulation
  int numberOfFrameErrors;            // Number of frame errors found in the simulation
  int minNumberOfFrames;              // minimum number of frames before terminate simulation
  int minNumberOfFrameErrors;         // minimum number of frame errors before terminate simulation
  int maxNumberOfFrames;              // maximum number of frames before terminate simulation
  long int numberOfBits;              // Number of bits passed through the channel
  int numberOfBitErrors;              // Number of bit errors found during the simulation
  double BER;                         // Bit error rate
  double FER;                         // Frame error rate
  signalStruct signal;                // Signals passed from one module to the next
  } swrcGP_LDPCStruct;

// Initialize the fields in the module structure
// Set pointers to NULL (so they can be called with realloc)
// Initialize the parameters to sane start-up values.
void initSwrcGP_LDPCStruct(swrcGP_LDPCStruct *swrcGP_LDPC);

// Frees up all the memory in the structure
void freeSwrcGP_LDPCStruct(swrcGP_LDPCStruct *swrcGP_LDPC);

// Prints the contents of the structure.
// Used for determining the status of the simulation
// as well as for debugging.
void printSwrcGP_LDPCStruct(swrcGP_LDPCStruct *swrcGP_LDPC, char *name, int index, int pre);

// Plot function generates any plots associated with the 
// structure
void plotSwrcGP_LDPCStruct(swrcGP_LDPCStruct *swrcGP_LDPC, const char *filename);

// All the data from all the modules is packed into an
// array of uint8_vectors for saving. One uint8_vector per module. 
// Each uint8_vector contains a stringified version of the
// data in the struct. uint8_vectors are then written to and 
// read from disk by the SWRC_saveuint8_vector and SWRC_loaduint8_vector 
// functions. This function packs struct data into a uint_8_vector
void packSwrcGP_LDPCStruct(swrcGP_LDPCStruct *swrcGP_LDPC, uint8_vector *cfgFile);

// After loading the data back from a .cfg file, the data is unpacked
// back into the struct with this function.
void unpackSwrcGP_LDPCStruct(swrcGP_LDPCStruct *swrcGP_LDPC, uint8_vector *cfgFile);

// Function for loading the struct
int loadSwrcGP_LDPCStruct(swrcGP_LDPCStruct *swrcGP_LDPC, char *filename);

// Function for saving the struct
void saveSwrcGP_LDPCStruct(swrcGP_LDPCStruct *swrcGP_LDPC, char *filename);

// Set parameters (fields) in the structure
// Change the values of fields in the structure
void setParmSwrcGP_LDPCStruct(swrcGP_LDPCStruct *swrcGP_LDPC, char *arg);

// A command comes from the user
// This function processes and executes the command
// some commands need a signal to operate on, which is
// passed via the signalStruct. 
void processCommandSwrcGP_LDPC(swrcGP_LDPCStruct *swrcGP_LDPC, signalStruct *signal, const char *command);

// Provides instructions on the commands that this module is able to process.
void helpCommandSwrcGP_LDPC(int index);

// Check that all the parameters needed to run the simulation are present.
// Uncomment any/all variables that _need_ to be present for the simulation to run.
int checkParametersSwrcGP_LDPC(swrcGP_LDPCStruct *swrcGP_LDPC);

// Precomputation done just prior to the main for loop
// iterating the BER/FER are put into this subroutine
void precompSwrcGP_LDPC(swrcGP_LDPCStruct *swrcGP_LDPC);

// postComputation, such as freeing up any memory, done after
// the iteration of the BER/FER are put into this subroutine
void postcompSwrcGP_LDPC(swrcGP_LDPCStruct *swrcGP_LDPC, char finishedFlag);

// Function called prior to training. Zero out statistics matrices,
// set the i_train index to zero etc...
void pretrainSwrcGP_LDPC(swrcGP_LDPCStruct *swrcGP_LDPC);

// Function called after training. Free allocated memory etc...
void posttrainSwrcGP_LDPC(swrcGP_LDPCStruct *swrcGP_LDPC);

// Some modules have a training phase where modules before them are run
// and statistics collected so the module can run properly.
// This function performs the training for the module then 
// saved back to the .cfg file. 
void trainSwrcGP_LDPC(swrcGP_LDPCStruct *swrcGP_LDPC);

// Count the BER/FER between 2 signals in the signal struct
// obi is the original bit index 
// dbi is the detected bit index
void countBERSwrcGP_LDPC(swrcGP_LDPCStruct *swrcGP_LDPC,int obi, int dbi);

// Contribute the fields to the berResultStruct that will be 
// printed in the berResult file. Every module contributes
// its own fields. User has to choose the fields to be saved
// using pushBerResultField() once per field to be added
void initBerResultStructSwrcGP_LDPC(swrcGP_LDPCStruct *swrcGP_LDPC,berResultStruct *berResult,char *berResultFilename);

// Finally when everything is in place, the module must be
// run during the actual simulation. The code for running
// the module is in this function.
void runSwrcGP_LDPC(swrcGP_LDPCStruct *swrcGP_LDPC);

