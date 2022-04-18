// Software Recording Channel (SWRC) platform in C. 
// Type      : support.
// Dependency: 
// Copyright : DSI
// Version   : 1.0
// Author(s) : Kheong Sann Chan.
// Date      : Tue Oct  6 16:11:19 2015

#ifndef BERRESULT_H
#define BERRESULT_H
#include "../SWRC.h"


typedef struct berResultStruct {
//////////////////////////////
// Fields entered by the user
//////////////////////////////
  long unsigned int N_N_name;         // Length of *N_name
  long unsigned int *N_name;          // Length of **name
  char **name;                        // array of names of each header field
  long unsigned int N_N_type;         // Length of *N_type
  long unsigned int *N_type;          // Length of **type
  char **type;                        // The type of the current field
  long unsigned int N_N_headerFS;     // Length of *N_headerFS
  long unsigned int *N_headerFS;      // Length of **headerFS
  char **headerFS;                    // format string for the header with the corresponding name
  long unsigned int N_N_fieldFS;      // Length of *N_fieldFS
  long unsigned int *N_fieldFS;       // Length of **fieldFS
  char **fieldFS;                     // format string for the value to be printed below the header.
  long unsigned int N_N_p;            // Length of *N_p
  long unsigned int *N_p;             // Length of **p
  void **p;                           // Array of pointers to the memory locations of the values.
  long unsigned int N_berResultFilename; // Length of *berResultFilename
  char *berResultFilename;            // name of the .berResults file.
  char *lockFilename;                 // name of file to used as semaphore to lock
} berResultStruct;


// Initialize the fields in the module structure
// Set pointers to NULL (so they can be called with realloc)
// Initialize the parameters to sane start-up values.
// Function called each time structure is instantiated.
void initBerResultStruct(berResultStruct *berResult);

// The counter part to the init function. Frees up all the memory 
// in the structure
void freeBerResultStruct(berResultStruct *berResult);

// Prints the contents of the structure. 
// Used for determining the status of the simulation
// as well as for debugging.
void printBerResultStruct(berResultStruct *berResult, char *name, int index, int pre);

// Plot function generates any plots associated with the 
// structure
void plotBerResultStruct(berResultStruct *berResult, const char *filename);

// All the data from all the modules is packed into an
// array of uint8_vectors for saving. One uint8_vector per module. 
// Each uint8_vector contains a stringified version of the
// data in the struct. uint8_vectors are then written to and 
// read from disk by the saveuint8_vector and loaduint8_vector 
// functions. This function packs struct data into a uint_8_vector
void packBerResultStruct(berResultStruct *berResult, uint8_vector *cfgFile);

// After loading the data back from a .cfg file, the data is unpacked
// back into the struct with this function.
void unpackBerResultStruct(berResultStruct *berResult, uint8_vector *cfgFile);

// Function for loading the struct
int loadBerResultStruct(berResultStruct *berResult, const char *filename);

// Function for saving the struct
void saveBerResultStruct(berResultStruct *berResult, const char *filename);

// Provides instructions on the commands that this module is able to process.
void helpCommandBerResult(int index);
void pushBerResultField(berResultStruct *berResult, const char *fieldName, const char *fieldType, const char *fieldFormatString, void *fieldPointer);
int saveBerResultFile(berResultStruct *berStruct,time_t *startTime, time_t *endTime, time_t *runTime, int dumpEvery);
void getHeaderString(berResultStruct *berResult, char *header);
void getValueString(berResultStruct *berResult, char *line);
#endif
