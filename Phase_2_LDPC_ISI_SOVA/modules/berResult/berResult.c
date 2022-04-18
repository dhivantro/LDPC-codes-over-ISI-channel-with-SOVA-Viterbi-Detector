// Software Recording Channel (SWRC) platform in C. 
// Type      : support.
// Dependency: 
// Copyright : DSI
// Version   : 1.0
// Author(s) : Kheong Sann Chan.
// Date      : Tue Oct  6 16:11:19 2015

#include "berResult.h"
#include <fcntl.h>
#include <errno.h>
#define BERRESULTLINELENGTH 100000
// Initialize the fields in the module structure
// Set pointers to NULL (so they can be called with realloc)
// Initialize the parameters to sane start-up values.
// Function called each time structure is instantiated.
void initBerResultStruct (berResultStruct *berResult) {
// Fields entered by the user
  berResult->N_N_name                 = 0;
  berResult->N_name                   = NULL;
  berResult->name                     = NULL;
  berResult->N_N_type                 = 0;
  berResult->N_type                   = NULL;
  berResult->type                     = NULL;
  berResult->N_N_headerFS             = 0;
  berResult->N_headerFS               = NULL;
  berResult->headerFS                 = NULL;
  berResult->N_N_fieldFS              = 0;
  berResult->N_fieldFS                = NULL;
  berResult->fieldFS                  = NULL;
  berResult->N_N_p                    = 0;
  berResult->N_p                      = NULL;
  berResult->p                        = NULL;
  berResult->N_berResultFilename      = 0;
  berResult->berResultFilename        = NULL;
}

// The counter part to the init function. Frees up all the memory 
// in the structure
void freeBerResultStruct (berResultStruct *berResult) {
  int i;
// Fields entered by the user
  for (i=0;i<berResult->N_N_name;i++) {
    if (berResult->N_name[i]!=0) { free(berResult->name[i]);berResult->name[i]=NULL;}
  }
  if (berResult->N_N_name!=0)    { free(berResult->name);berResult->name=NULL;}
  for (i=0;i<berResult->N_N_type;i++) {
    if (berResult->N_type[i]!=0) { free(berResult->type[i]);berResult->type[i]=NULL;}
  }
  if (berResult->N_N_type!=0)    { free(berResult->type);berResult->type=NULL;}
  for (i=0;i<berResult->N_N_headerFS;i++) {
    if (berResult->N_headerFS[i]!=0) { free(berResult->headerFS[i]);berResult->headerFS[i]=NULL;}
  }
  if (berResult->N_N_headerFS!=0) { free(berResult->headerFS);berResult->headerFS=NULL;}
  for (i=0;i<berResult->N_N_fieldFS;i++) {
    if (berResult->N_fieldFS[i]!=0) { free(berResult->fieldFS[i]);berResult->fieldFS[i]=NULL;}
  }
  if (berResult->N_N_fieldFS!=0) { free(berResult->fieldFS);berResult->fieldFS=NULL;}
  //for (i=0;i<berResult->N_N_p;i++) {
  //  if (berResult->N_p[i]!=0)    { free(berResult->p[i]);berResult->p[i]=NULL;}
  //}
  if (berResult->N_N_p!=0)       { free(berResult->p);berResult->p=NULL;}
  if (berResult->N_N_name!=0)    {free(berResult->N_name);berResult->N_name=NULL;}
  if (berResult->N_N_type!=0)    {free(berResult->N_type);berResult->N_type=NULL;}
  if (berResult->N_N_headerFS!=0) {free(berResult->N_headerFS);berResult->N_headerFS=NULL;}
  if (berResult->N_N_fieldFS!=0) {free(berResult->N_fieldFS);berResult->N_fieldFS=NULL;}
  //if (berResult->N_N_p!=0)       {free(berResult->N_p);berResult->N_p=NULL;}
  if (berResult->N_berResultFilename!=0) {
    free(berResult->berResultFilename);berResult->berResultFilename=NULL;
    free(berResult->lockFilename);berResult->lockFilename=NULL;
  }
  berResult->N_N_name           =0;
  berResult->N_N_type           =0;
  berResult->N_N_headerFS       =0;
  berResult->N_N_fieldFS        =0;
  berResult->N_N_p              =0;
  berResult->N_berResultFilename=0;
}

// Prints the contents of the structure. 
// Used for determining the status of the simulation
// as well as for debugging.
void printBerResultStruct (berResultStruct *berResult, char *name, int index, int pre) {
  int i,j;
  char *preString;
  preString=(char*)calloc((pre+1),sizeof(char));
  for (i=0;i<pre;i++) preString[i]=' '; preString[i]='\0';
  printf("%s---%d:%s--------\n",preString,index,name);
  // Fields entered by the user
  printf("%s  ---Fields entered by the user\n",preString);
  printf("%s  long unsigned int    %s->N_N_name=%lu\n",preString,name,berResult->N_N_name); // Print N_N_name
  if (berResult->N_N_name!=0) { // Print *N_name
    printf("%s  long unsigned int*   %s->N_name=[",preString,name);
    for (i=0;i<(berResult->N_N_name>20?20:berResult->N_N_name);i++) printf("%lu ",berResult->N_name[i]); printf("]\n");
  } else {
    printf("%s  long unsigned int*   %s->N_name=NULL\n",preString,name);
  }
  if (berResult->N_N_name!=0) { // Print **name
    for (i=0;i<(berResult->N_N_name>20?20:berResult->N_N_name);i++) {
      if (berResult->N_name[i]!=0) {
	printf("%s  char**               %s->name[%d]=[",preString,name,i);
	for (j=0;j<(berResult->N_name[i]>20?20:berResult->N_name[i]);j++) printf("%c",berResult->name[i][j]); printf("]\n");
      } else {
	printf("%s  %s->x[%d]=NULL\n",preString,name,i);
      }
    }
  } else {
    printf("%s  char**               berResult->name=NULL\n",preString);
  }
  printf("%s  long unsigned int    %s->N_N_type=%lu\n",preString,name,berResult->N_N_type); // Print N_N_type
  if (berResult->N_N_type!=0) { // Print *N_type
    printf("%s  long unsigned int*   %s->N_type=[",preString,name);
    for (i=0;i<(berResult->N_N_type>20?20:berResult->N_N_type);i++) printf("%lu ",berResult->N_type[i]); printf("]\n");
  } else {
    printf("%s  long unsigned int*   %s->N_type=NULL\n",preString,name);
  }
  if (berResult->N_N_type!=0) { // Print **type
    for (i=0;i<(berResult->N_N_type>20?20:berResult->N_N_type);i++) {
      if (berResult->N_type[i]!=0) {
	printf("%s  char**               %s->type[%d]=[",preString,name,i);
	for (j=0;j<(berResult->N_type[i]>20?20:berResult->N_type[i]);j++) printf("%c",berResult->type[i][j]); printf("]\n");
      } else {
	printf("%s  %s->x[%d]=NULL\n",preString,name,i);
      }
    }
  } else {
    printf("%s  char**               berResult->type=NULL\n",preString);
  }
  printf("%s  long unsigned int    %s->N_N_headerFS=%lu\n",preString,name,berResult->N_N_headerFS); // Print N_N_headerFS
  if (berResult->N_N_headerFS!=0) { // Print *N_headerFS
    printf("%s  long unsigned int*   %s->N_headerFS=[",preString,name);
    for (i=0;i<(berResult->N_N_headerFS>20?20:berResult->N_N_headerFS);i++) printf("%lu ",berResult->N_headerFS[i]); printf("]\n");
  } else {
    printf("%s  long unsigned int*   %s->N_headerFS=NULL\n",preString,name);
  }
  if (berResult->N_N_headerFS!=0) { // Print **headerFS
    for (i=0;i<(berResult->N_N_headerFS>20?20:berResult->N_N_headerFS);i++) {
      if (berResult->N_headerFS[i]!=0) {
	printf("%s  char**               %s->headerFS[%d]=[",preString,name,i);
	for (j=0;j<(berResult->N_headerFS[i]>20?20:berResult->N_headerFS[i]);j++) printf("%c",berResult->headerFS[i][j]); printf("]\n");
      } else {
	printf("%s  %s->x[%d]=NULL\n",preString,name,i);
      }
    }
  } else {
    printf("%s  char**               berResult->headerFS=NULL\n",preString);
  }
  printf("%s  long unsigned int    %s->N_N_fieldFS=%lu\n",preString,name,berResult->N_N_fieldFS); // Print N_N_fieldFS
  if (berResult->N_N_fieldFS!=0) { // Print *N_fieldFS
    printf("%s  long unsigned int*   %s->N_fieldFS=[",preString,name);
    for (i=0;i<(berResult->N_N_fieldFS>20?20:berResult->N_N_fieldFS);i++) printf("%lu ",berResult->N_fieldFS[i]); printf("]\n");
  } else {
    printf("%s  long unsigned int*   %s->N_fieldFS=NULL\n",preString,name);
  }
  if (berResult->N_N_fieldFS!=0) { // Print **fieldFS
    for (i=0;i<(berResult->N_N_fieldFS>20?20:berResult->N_N_fieldFS);i++) {
      if (berResult->N_fieldFS[i]!=0) {
	printf("%s  char**               %s->fieldFS[%d]=[",preString,name,i);
	for (j=0;j<(berResult->N_fieldFS[i]>20?20:berResult->N_fieldFS[i]);j++) printf("%c",berResult->fieldFS[i][j]); printf("]\n");
      } else {
	printf("%s  %s->x[%d]=NULL\n",preString,name,i);
      }
    }
  } else {
    printf("%s  char**               berResult->fieldFS=NULL\n",preString);
  }
  printf("%s  long unsigned int    %s->N_N_p=%lu\n",preString,name,berResult->N_N_p); // Print N_N_p
  //if (berResult->N_N_p!=0) { // Print *N_p
  //  printf("%s  long unsigned int*   %s->N_p=[",preString,name);
  //  for (i=0;i<(berResult->N_N_p>20?20:berResult->N_N_p);i++) printf("%lu ",berResult->N_p[i]); printf("]\n");
  //} else {
  //  printf("%s  long unsigned int*   %s->N_p=NULL\n",preString,name);
  //}
  if (berResult->N_N_p!=0) { // Print **p
    for (i=0;i<(berResult->N_N_p>20?20:berResult->N_N_p);i++) {
      //if (berResult->N_p[i]!=0) {
      //printf("%s  void**               %s->p[%d]=[",preString,name,i);
      //for (j=0;j<(berResult->N_p[i]>20?20:berResult->N_p[i]);j++) printf(" ",berResult->p[i][j]); printf("]\n");
      //} else {
      //printf("%s  %s->x[%d]=NULL\n",preString,name,i);
      //}
      printf("%s  void**               %s->p[%d]=%p (%s)\n",preString,name,i,berResult->p[i],berResult->name[i]);
    }
  } else {
    printf("%s  void**               berResult->p=NULL\n",preString);
  }
  printf("%s  long unsigned int    %s->N_berResultFilename=%lu\n",preString,name,berResult->N_berResultFilename); // Print N_berResultFilename
  if (berResult->N_berResultFilename!=0) { // Print *berResultFilename
    printf("%s  char*                %s->berResultFilename=[",preString,name);
    for (i=0;i<(berResult->N_berResultFilename>20?20:berResult->N_berResultFilename);i++) printf("%c",berResult->berResultFilename[i]); printf("]\n");
    printf("%s  char*                %s->lockFilename=%s\n",preString,name,berResult->lockFilename);
  } else {
    printf("%s  char*                %s->berResultFilename=NULL\n",preString,name);
    printf("%s  char*                %s->lockFilename=NULL\n",preString,name);
  }
  printf("%s---%d:%s--------\n",preString,index,name);
  free(preString);
}

// Plot function generates any plots associated with the 
// structure
void plotBerResultStruct (berResultStruct *berResult, const char *filename) {
}

// All the data from all the modules is packed into an
// array of uint8_vectors for saving. One uint8_vector per module. 
// Each uint8_vector contains a stringified version of the
// data in the struct. uint8_vectors are then written to and 
// read from disk by the saveuint8_vector and loaduint8_vector 
// functions. This function packs struct data into a uint_8_vector
void packBerResultStruct (berResultStruct *berResult, uint8_vector *cfgFile) {
  int i;
 //Fields entered by the user
  // N_N_name
  SWRC_packToUint8((uint8_t*)&berResult->N_N_name,1,sizeof(long unsigned int),cfgFile);
  // *N_name
  SWRC_packToUint8((uint8_t*)berResult->N_name,berResult->N_N_name,sizeof(long unsigned int),cfgFile);
  // **name
  for (i=0;i<berResult->N_N_name;i++) 
    SWRC_packToUint8((uint8_t*)berResult->name[i],berResult->N_name[i],sizeof(char),cfgFile);
  // N_N_type
  SWRC_packToUint8((uint8_t*)&berResult->N_N_type,1,sizeof(long unsigned int),cfgFile);
  // *N_type
  SWRC_packToUint8((uint8_t*)berResult->N_type,berResult->N_N_type,sizeof(long unsigned int),cfgFile);
  // **type
  for (i=0;i<berResult->N_N_type;i++) 
    SWRC_packToUint8((uint8_t*)berResult->type[i],berResult->N_type[i],sizeof(char),cfgFile);
  // N_N_headerFS
  SWRC_packToUint8((uint8_t*)&berResult->N_N_headerFS,1,sizeof(long unsigned int),cfgFile);
  // *N_headerFS
  SWRC_packToUint8((uint8_t*)berResult->N_headerFS,berResult->N_N_headerFS,sizeof(long unsigned int),cfgFile);
  // **headerFS
  for (i=0;i<berResult->N_N_headerFS;i++) 
    SWRC_packToUint8((uint8_t*)berResult->headerFS[i],berResult->N_headerFS[i],sizeof(char),cfgFile);
  // N_N_fieldFS
  SWRC_packToUint8((uint8_t*)&berResult->N_N_fieldFS,1,sizeof(long unsigned int),cfgFile);
  // *N_fieldFS
  SWRC_packToUint8((uint8_t*)berResult->N_fieldFS,berResult->N_N_fieldFS,sizeof(long unsigned int),cfgFile);
  // **fieldFS
  for (i=0;i<berResult->N_N_fieldFS;i++) 
    SWRC_packToUint8((uint8_t*)berResult->fieldFS[i],berResult->N_fieldFS[i],sizeof(char),cfgFile);
  // N_N_p
  SWRC_packToUint8((uint8_t*)&berResult->N_N_p,1,sizeof(long unsigned int),cfgFile);
  // *N_p
  SWRC_packToUint8((uint8_t*)berResult->N_p,berResult->N_N_p,sizeof(long unsigned int),cfgFile);
  // **p
  for (i=0;i<berResult->N_N_p;i++) 
    SWRC_packToUint8((uint8_t*)berResult->p[i],berResult->N_p[i],sizeof(void),cfgFile);
  // N_berResultFilename
  SWRC_packToUint8((uint8_t*)&berResult->N_berResultFilename,1,sizeof(long unsigned int),cfgFile);
  // *berResultFilename
  SWRC_packToUint8((uint8_t*)berResult->berResultFilename,berResult->N_berResultFilename,sizeof(char),cfgFile);
}

// After loading the data back from a .cfg file, the data is unpacked
// back into the struct with this function.
void unpackBerResultStruct (berResultStruct *berResult, uint8_vector *cfgFile) {
  int i;
  freeBerResultStruct(berResult);
// Fields entered by the user
  // N_N_name
  SWRC_unpackFromUint8((uint8_t*)&berResult->N_N_name,1,sizeof(long unsigned int),cfgFile);
  // *N_name
  if (berResult->N_N_name!=0) {
    berResult->N_name = (long unsigned int*)calloc(berResult->N_N_name,sizeof(long unsigned int));
    SWRC_unpackFromUint8((uint8_t*)berResult->N_name,berResult->N_N_name,sizeof(long unsigned int),cfgFile);
  }
  // **name
    if (berResult->N_N_name!=0) {
      berResult->name=(char**) calloc(berResult->N_N_name,sizeof(char*));
      for (i=0;i<berResult->N_N_name;i++) {
        berResult->name[i]=(char*) calloc(berResult->N_name[i],sizeof(char));
        SWRC_unpackFromUint8((uint8_t*)berResult->name[i],berResult->N_name[i],sizeof(char),cfgFile);
      }
    }
  // N_N_type
  SWRC_unpackFromUint8((uint8_t*)&berResult->N_N_type,1,sizeof(long unsigned int),cfgFile);
  // *N_type
  if (berResult->N_N_type!=0) {
    berResult->N_type = (long unsigned int*)calloc(berResult->N_N_type,sizeof(long unsigned int));
    SWRC_unpackFromUint8((uint8_t*)berResult->N_type,berResult->N_N_type,sizeof(long unsigned int),cfgFile);
  }
  // **type
    if (berResult->N_N_type!=0) {
      berResult->type=(char**) calloc(berResult->N_N_type,sizeof(char*));
      for (i=0;i<berResult->N_N_type;i++) {
        berResult->type[i]=(char*) calloc(berResult->N_type[i],sizeof(char));
        SWRC_unpackFromUint8((uint8_t*)berResult->type[i],berResult->N_type[i],sizeof(char),cfgFile);
      }
    }
  // N_N_headerFS
  SWRC_unpackFromUint8((uint8_t*)&berResult->N_N_headerFS,1,sizeof(long unsigned int),cfgFile);
  // *N_headerFS
  if (berResult->N_N_headerFS!=0) {
    berResult->N_headerFS = (long unsigned int*)calloc(berResult->N_N_headerFS,sizeof(long unsigned int));
    SWRC_unpackFromUint8((uint8_t*)berResult->N_headerFS,berResult->N_N_headerFS,sizeof(long unsigned int),cfgFile);
  }
  // **headerFS
    if (berResult->N_N_headerFS!=0) {
      berResult->headerFS=(char**) calloc(berResult->N_N_headerFS,sizeof(char*));
      for (i=0;i<berResult->N_N_headerFS;i++) {
        berResult->headerFS[i]=(char*) calloc(berResult->N_headerFS[i],sizeof(char));
        SWRC_unpackFromUint8((uint8_t*)berResult->headerFS[i],berResult->N_headerFS[i],sizeof(char),cfgFile);
      }
    }
  // N_N_fieldFS
  SWRC_unpackFromUint8((uint8_t*)&berResult->N_N_fieldFS,1,sizeof(long unsigned int),cfgFile);
  // *N_fieldFS
  if (berResult->N_N_fieldFS!=0) {
    berResult->N_fieldFS = (long unsigned int*)calloc(berResult->N_N_fieldFS,sizeof(long unsigned int));
    SWRC_unpackFromUint8((uint8_t*)berResult->N_fieldFS,berResult->N_N_fieldFS,sizeof(long unsigned int),cfgFile);
  }
  // **fieldFS
    if (berResult->N_N_fieldFS!=0) {
      berResult->fieldFS=(char**) calloc(berResult->N_N_fieldFS,sizeof(char*));
      for (i=0;i<berResult->N_N_fieldFS;i++) {
        berResult->fieldFS[i]=(char*) calloc(berResult->N_fieldFS[i],sizeof(char));
        SWRC_unpackFromUint8((uint8_t*)berResult->fieldFS[i],berResult->N_fieldFS[i],sizeof(char),cfgFile);
      }
    }
  // N_N_p
  SWRC_unpackFromUint8((uint8_t*)&berResult->N_N_p,1,sizeof(long unsigned int),cfgFile);
  // *N_p
  if (berResult->N_N_p!=0) {
    berResult->N_p = (long unsigned int*)calloc(berResult->N_N_p,sizeof(long unsigned int));
    SWRC_unpackFromUint8((uint8_t*)berResult->N_p,berResult->N_N_p,sizeof(long unsigned int),cfgFile);
  }
  // **p
    if (berResult->N_N_p!=0) {
      berResult->p=(void**) calloc(berResult->N_N_p,sizeof(void*));
      for (i=0;i<berResult->N_N_p;i++) {
        berResult->p[i]=(void*) calloc(berResult->N_p[i],sizeof(void));
        SWRC_unpackFromUint8((uint8_t*)berResult->p[i],berResult->N_p[i],sizeof(void),cfgFile);
      }
    }
  // N_berResultFilename
  SWRC_unpackFromUint8((uint8_t*)&berResult->N_berResultFilename,1,sizeof(long unsigned int),cfgFile);
  // *berResultFilename
  if (berResult->N_berResultFilename!=0) {
    berResult->berResultFilename = (char*)calloc(berResult->N_berResultFilename,sizeof(char));
    SWRC_unpackFromUint8((uint8_t*)berResult->berResultFilename,berResult->N_berResultFilename,sizeof(char),cfgFile);
  }
}

// Function for loading the struct
int loadBerResultStruct (berResultStruct *berResult, const char *filename) {
}

// Function for saving the struct
void saveBerResultStruct (berResultStruct *berResult, const char *filename) {
}

// Provides instructions on the commands that this module is able to process.
void helpCommandBerResult (int index) {
  printf("Commands recognized by %d:berResultStruct:\n",index);
  printf("  \"print();\"        : print the berResultStruct fields\n");
  printf("  \"setParm(arg);\"   : set the berResultStruct fields\n");
  printf("  \"help();\"         : display this help screen\n");
}

void pushBerResultField(berResultStruct *berResult, const char *fieldName, const char *fieldType, const char *fieldFS, void *fieldPointer) {
  int i;
  char *c;
  // Push the name field into the berResultStruct
  berResult->N_N_name++;
  berResult->N_name=(long unsigned int*)realloc(berResult->N_name,berResult->N_N_name*sizeof(long unsigned int));
  berResult->N_name[berResult->N_N_name-1]=strlen(fieldName);
  berResult->name=(char **)realloc(berResult->name,berResult->N_N_name*sizeof(char *));
  berResult->name[berResult->N_N_name-1]=(char*)calloc((strlen(fieldName)+1),sizeof(char));
  strcpy(berResult->name[berResult->N_N_name-1],fieldName);
  // Push the type field into the berResultStruct
  berResult->N_N_type++;
  berResult->N_type=(long unsigned int*)realloc(berResult->N_type,berResult->N_N_type*sizeof(long unsigned int));
  berResult->N_type[berResult->N_N_type-1]=strlen(fieldType);
  berResult->type=(char **)realloc(berResult->type,berResult->N_N_type*sizeof(char *));
  berResult->type[berResult->N_N_type-1]=(char*)calloc((strlen(fieldType)+1),sizeof(char));
  strcpy(berResult->type[berResult->N_N_type-1],fieldType);
  // Push the fieldFS field into the berResultStruct
  berResult->N_N_fieldFS++;
  berResult->N_fieldFS=(long unsigned int*)realloc(berResult->N_fieldFS,berResult->N_N_fieldFS*sizeof(long unsigned int));
  berResult->N_fieldFS[berResult->N_N_fieldFS-1]=strlen(fieldFS);
  berResult->fieldFS=(char **)realloc(berResult->fieldFS,berResult->N_N_fieldFS*sizeof(char *));
  berResult->fieldFS[berResult->N_N_fieldFS-1]=(char*)calloc((strlen(fieldFS)+1),sizeof(char));
  strcpy(berResult->fieldFS[berResult->N_N_type-1],fieldFS);
  // Copy the headerFS into headerFS
  berResult->N_N_headerFS++;
  berResult->N_headerFS=(long unsigned int*)realloc(berResult->N_headerFS,berResult->N_N_headerFS*sizeof(long unsigned int));
  berResult->N_headerFS[berResult->N_N_headerFS-1]=strlen(fieldFS);
  berResult->headerFS=(char **)realloc(berResult->headerFS,berResult->N_N_headerFS*sizeof(char *));
  berResult->headerFS[berResult->N_N_headerFS-1]=(char*)calloc((strlen(fieldFS)+1),sizeof(char));
  strcpy(berResult->headerFS[berResult->N_N_type-1],fieldFS);
  // convert the fieldFS into a headerFS
  c=berResult->headerFS[berResult->N_N_headerFS-1];
  for (i=0;i<berResult->N_headerFS[berResult->N_N_headerFS-1];i++) {
    if ((c[i]>='a' && c[i]<='z')||c[i]=='.') { // The a-z character denotes the end of the length 
                              // and beginning of the type of the format string.
                              // we're going to force this equal to s to print a string.
      c[i]='s';c[i+1]='\0';
      break;
    }
  }

  // Save the pointer to the berResultStruct
  berResult->N_N_p++;
  berResult->p=(void**)realloc(berResult->p,berResult->N_N_p*sizeof(void*));
  berResult->p[berResult->N_N_p-1] = fieldPointer;
}

// save result to the berResult file
// if the simulation is complete, it will try indefinitely until
// it is able to get the lock file and write its result.
// if the simulation is not complete, it makes an attempt to get
// the lockfile. If successful it writes the berResult and returns 0. 
// If not successful it just returns -1 to indicate failure to write.
// dumpEvery is a number in seconds. The result will dump only if the
// last dump occurred more than dumpEvery seconds ago.
int saveBerResultFile(berResultStruct *berResult,time_t *startTime, time_t *endTime, time_t *runTime, int dumpEvery) {
  int i,fd;
  char string[BERRESULTLINELENGTH];
  time_t now;

  //printBerResultStruct(berResult,"berResult",0,0);
  time(&now);
  //printf("now=%lu, endTime=%lu, now-endTime=%lu\n",now,*endTime,now-*endTime);
  if (now-*endTime<dumpEvery) {
    //printf("Not time for a dump yet, now-endTime=%d\n",now-*endTime);
    return(-1); // Don't update unless last dump was more than dumpEvery seconds ago.
  }
  *endTime=now;                 // Update the endTime
  *runTime=*endTime-*startTime; // and the runTime fields

  // open the lockfile.
  //printf("Getting lockfile\n");
  while ((fd=open(berResult->lockFilename, O_CREAT | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR))<0) {
    //failed to open lockfile.
    if (dumpEvery>0) { //dumpEvery==0 means compulsory saving of berResult
      printf("Unable to get lockfile in function saveBerResultFile, returning\n");
      return(-1);
    }
    printf("Trying to get lockfile %s again in 1 second\n",berResult->lockFilename);
    sleep(1); 
  }
  // got the lockfile. Can proceed to access the berResult file.
  close(fd);
  //printf("Got lockfile\n");
  // Try to create the berResult file, write the header.
  //if ((fd=open(berResult->berResultFilename, O_CREAT | O_WRONLY | O_EXCL, S_IRUSR | S_IWUSR))>0) { // This line created a berResult file with 0600 permissions.
  if ((fd=open(berResult->berResultFilename, O_CREAT | O_WRONLY | O_EXCL, 0644))>0) {
    // managed to create and open the file. Meaning it did not exist before. 
    // Fill in the string.
    printf("Created %s\n",berResult->berResultFilename);
    strcpy(string,"# ");
    getHeaderString(berResult,string);
    write(fd,string,strlen(string));
    close(fd);
  } else {
    //printf("Unable to create %s\n",berResult->berResultFilename);
  }
  
  // Append our result to the berResult file
  if ((fd=open(berResult->berResultFilename, O_WRONLY | O_APPEND))>0) {
    // opened the file for writing
    // Fill in the string.
    printf("Appending to %s\n",berResult->berResultFilename);
    strcpy(string,"  ");
    getValueString(berResult,string);
    write(fd,string,strlen(string));
    close(fd);
  } else {
    printf("Unable to append to %s\n",berResult->berResultFilename);
  }
  //printf("Freeing lockFile\n");
  // remove the lock file 
  unlink(berResult->lockFilename);
  return(0);
}

void getHeaderString(berResultStruct *br, char *header) {
  int i;
  char *field;
  for (i=0;i<br->N_N_name;i++) {
    asprintf(&field,br->headerFS[i],br->name[i]);
    strcat(header,field);strcat(header," ");
    free(field);field=0;
  }
  strcat(header,"\n");
}
void getValueString(berResultStruct *br, char *line) {
  int i;
  char *field;
  for (i=0;i<br->N_N_name;i++) {
    if (strcmp(br->type[i],"uint8_t")==0)    asprintf(&field,br->fieldFS[i],*(uint8_t*)(br->p[i]));
    if (strcmp(br->type[i],"int")==0)        asprintf(&field,br->fieldFS[i],*(int*)(br->p[i]));
    if (strcmp(br->type[i],"char*")==0)      asprintf(&field,br->fieldFS[i],(char*)(br->p[i]));
    if (strcmp(br->type[i],"string")==0)     asprintf(&field,br->fieldFS[i],(char*)(br->p[i]));
    if (strcmp(br->type[i],"double")==0)     asprintf(&field,br->fieldFS[i],*(double*)(br->p[i]));
    if (strcmp(br->type[i],"float")==0)      asprintf(&field,br->fieldFS[i],*(float*)(br->p[i]));
    if (strcmp(br->type[i],"unsigned int")==0) asprintf(&field,br->fieldFS[i],*(unsigned int*)(br->p[i]));
    if (strcmp(br->type[i],"long int")==0)   asprintf(&field,br->fieldFS[i],*(long int*)(br->p[i]));
    if (strcmp(br->type[i],"long unsigned int")==0) asprintf(&field,br->fieldFS[i],*(long unsigned int*)(br->p[i]));
    if (strcmp(br->type[i],"time_t")==0)            asprintf(&field,br->fieldFS[i],*(time_t*)(br->p[i]));
    if (strcmp(br->type[i],"long long unsigned int")==0) asprintf(&field,br->fieldFS[i],*(long long unsigned int*)(br->p[i]));
    //printf("%2d: name = %20s, formatString=%7s, field=%s\n",i,br->name[i],br->fieldFS[i],field);
    strcat(line,field);strcat(line," ");
    free(field);field=0;
  }
  strcat(line,"\n");
}
