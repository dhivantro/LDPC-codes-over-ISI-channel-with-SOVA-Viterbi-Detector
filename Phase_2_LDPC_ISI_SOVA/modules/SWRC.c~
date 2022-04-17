#include "SWRC.h"
#include<time.h>
//////////////////////////////
// uint8_vector functions
//////////////////////////////
void SWRC_init_uint8_vector(uint8_vector *x) {
  x->N=0;
  x->offset=0;
  x->x=NULL;
}
void SWRC_print_uint8_vector(uint8_vector *x,char *name) {
  int i;
  printf("%s->N=%d\n",name,x->N);
  printf("%s->offset=%lu\n",name,x->offset);
  for (i=0;i<x->N;i++) {
    printf("%3d %d\n",i,x->x[i]);
  }
}
void SWRC_free_uint8_vector(uint8_vector *x) {
  if (x->N>0) free(x->x);
  x->N=0;
}
////////////////////////////////////////////////////////
// Functions for packing and unpacking generic
// structures into uint8_t vectors
////////////////////////////////////////////////////////
// pack a struct into a uint8_vector.
// cast the structure as a pointer to uint8_t when calling this function
// N is the size of the source structure to be copied
// Output is stored in *cfgFile. Previous contents of cfgFile are overwritten
int SWRC_packStruct(uint8_t *sourceStruct, int N, uint8_vector *cfgFile) {
  int i;
  if (N>0) { // Only allocate memory if N>0
    cfgFile->x = (uint8_t*)realloc(cfgFile->x,cfgFile->N+N);
    for (i=0;i<N;i++) {
      cfgFile->x[i+cfgFile->N]=sourceStruct[i];
    }
    cfgFile->N+=N;
  }
  return(N);
}
// unpack a uint8_vector back into its host struct.
// cast the destStruct as a uint8_t when calling.
// N is the size of the destination structure
// the N in the cfgFile is not used, as it may have several items packed in it
// and N may not reflect the correct size.
int SWRC_unpackStruct(uint8_t *destStruct, int N, uint8_vector *cfgFile) {
  int i;
  for (i=0;i<N;i++) {
    destStruct[i]=cfgFile->x[i];
  }
  return(N);
}
// pack a vector vect (cast as uint8_t*) into cfgFile.
// vect has N elements, each of size unitSize.
int SWRC_packVect(uint8_t *vect, int N, int unitSize, uint8_vector *cfgFile) {
  // printf("In function SWRC.c:packVect\n");
  int i;
  if (N>0) { // Only proceed if N>0
    cfgFile->x = (uint8_t*)realloc(cfgFile->x,cfgFile->N+N*unitSize);
    for (i=0;i<N*unitSize;i++) {
      cfgFile->x[cfgFile->N+i]=vect[i];
    }
    cfgFile->N+=N*unitSize;
  }
  return(N*unitSize);
}
// unpack a vector vect (cast as uint8_t*) from cfgFile.
// vect has N elements, each of size unitSize.
int SWRC_unpackVect(uint8_t *vect, int N, int unitSize, uint8_t *cfgFile) {
  //printf("In function SWRC.c:unpackVect\n");
  int i;
  for (i=0;i<N*unitSize;i++) {
    vect[i]=cfgFile[i];
  }
  return(N*unitSize);
}
// pack a vector vect (cast as uint8_t*) into cfgFile.
// vect has N elements, each of size unitSize.
int SWRC_packToUint8(uint8_t *vect, int N, int unitSize, uint8_vector *cfgFile) {
  // printf("In function SWRC.c:packVect\n");
  int i;
  if (N>0) { // Only proceed if N>0
    cfgFile->x = (uint8_t*)realloc(cfgFile->x,cfgFile->N+N*unitSize);
    for (i=0;i<N*unitSize;i++) {
      cfgFile->x[cfgFile->N+i]=vect[i];
    }
    cfgFile->N+=N*unitSize;
  }
  return(N*unitSize);
}
// unpack from cfgFile into output (cast as uint8_t*)
// output has N elements, each of size unitSize.
int SWRC_unpackFromUint8(uint8_t *output, int N, int unitSize, uint8_vector *cfgFile) {
  //printf("In function SWRC.c:unpackVect\n");
  int i;
  for (i=0;i<N*unitSize;i++) {
    output[i]=cfgFile->x[cfgFile->offset+i];
  }
  cfgFile->offset+=N*unitSize;
  return(N*unitSize);
}
// This function first (re)allocates memory and then unpacks it from the cfgFile vector.
int SWRC_allocateMemAndUnpackFromUint8(uint8_t **output, int N, int unitSize, uint8_vector *cfgFile) {
  int i;
  *output=(uint8_t*)realloc(*output,N*unitSize);
  for (i=0;i<N*unitSize;i++) {
    output[0][i]=cfgFile->x[cfgFile->offset+i];
  }
  cfgFile->offset+=N*unitSize;
  return(N*unitSize);
}
// pack a string (cast as a uint8_t*) into cfgFile
int SWRC_packStringToUint8(char **string, uint8_vector *cfgFile) {
  unsigned int N;
  if (*string!=NULL)  N = strlen(*string)+1;
  else N=0;
  SWRC_packToUint8((uint8_t*)&N,1,sizeof(unsigned int),cfgFile); // pack the length of the string
  if (N!=0) SWRC_packToUint8((uint8_t*)*string,N,sizeof(char),cfgFile);  // pack the string itself, including the '\0'
  return(N);
}
int SWRC_unpackStringFromUint8(char **string, uint8_vector *cfgFile) {
  unsigned int N;
  SWRC_unpackFromUint8((uint8_t*)&N,1,sizeof(unsigned int),cfgFile); // unpack the size of the string. The size includes the terminating character '\0'
  if (N!=0){
    *string = (char*)realloc(*string,N*sizeof(char));
    SWRC_unpackFromUint8(*string,N,sizeof(char),cfgFile);
  }
  return(N);
}
// pack an array of Ns strings each one NULL terminated.
int SWRC_packStringArrayToUint8(char ***string, int *Ns, uint8_vector *cfgFile) {
  int i;
  SWRC_packToUint8((uint8_t*)Ns,1,sizeof(unsigned int),cfgFile); // pack the length of the array
  for (i=0;i<*Ns;i++) { // pack each string one by one.
    SWRC_packStringToUint8(&string[0][i],cfgFile);  // pack the i'th string.
    //printf("SWRC_packStringArrayToUint8: packed %s to uint8_vector\n",string[0][i]);
  }
  return(*Ns);
}
int SWRC_unpackStringArrayFromUint8(char ***string, int *Ns, uint8_vector *cfgFile) {
  int i;
  SWRC_unpackFromUint8((uint8_t*)Ns,1,sizeof(unsigned int),cfgFile); // unpack the length of the array Ns
  *string=(char**)realloc(*string,*Ns*sizeof(char*)); // allocate memory for Ns strings.
  //*string=(char**)calloc(*Ns,sizeof(char*)); // allocate memory for Ns strings.
  for (i=0;i<*Ns;i++) { // pack each string one by one.
    string[0][i]=NULL;
    SWRC_unpackStringFromUint8(&string[0][i],cfgFile);  // unpack the i'th string.
    //printf("SWRC_unpackStringArrayFromUint8: unpacked %s from uint8_vector\n",string[0][i]);
  }
  return(*Ns);
}
// Check whether a vector is NULL if it is not NULL, return "OK" to proceed.
// If it is NULL, then it checks whether the supplied default value is "OK"
// It does this by passing it to int *OKFunc
// every element of the vector and return "OK". Otherwise, return "not OK".

int SWRC_checkVectorWithDefault(uint8_t **vect, int N, uint8_t *defaul, int unitSize,int (*IsOK)(uint8_t *x)) {
  int i,j;
  printf("In function checkVectorWithDefault. N=%d,\n",N);
  if (*vect!=NULL) {
    return(0); // vector is already defined, can proceed.
  }
  if (IsOK(defaul)) { // default value is acceptable
    *vect = (uint8_t*)malloc(N*unitSize); // alocate the memory
    for (i=0;i<N;i++) {       // assign the default value to each element of the memory.
      for (j=0;j<unitSize;j++) {
	vect[0][i*unitSize+j]=defaul[j];
      }
    }
    return(0);
  } else {//printf("default value is not OK.\n");
    return(1);
  }
}
///////////////////////////////////////////
// This function is used by printStruct functions
// to extend the name of the structure being 
// printed for substructures. The extension
// takes the name of the substructure.
///////////////////////////////////////////
void SWRC_extendPrintStructName(char *output, const char *input, const char *ext) {
  //strcpy(output,"   ");
  strcpy(output,input);
  strcat(output,"->");
  strcat(output,ext);
}

///////////////////////////////////////////
// Functions to load and save uint8_vectors
///////////////////////////////////////////
void SWRC_saveuint8_vector(uint8_vector *x,int N, char *filename,time_t startTime) {
  printf("Saving uint8_vector: %s\n",filename);
  FILE *f;
  int i,j;
  if ((f=fopen(filename,"w"))==NULL) {
    printf("Warning: Could open %s for writing\n",filename);
    return;
  }
  fwrite(&N,sizeof(int),1,f); // Write the number of uint8_vectors
  //printf("   N=%d\n",N);
  for (i=0;i<N;i++) {
    fwrite(&x[i].N,sizeof(int),1,f); // Write the size of the i'th uint8_vector
    //printf("   x[%d].N=%d\n",i,x[i].N);
    for (j=0;j<x[i].N;j++) {  // Write the i'th uint8_vector
      fputc(x[i].x[j],f);
      //printf("   x[%d].x[%d]=%d\n",i,j,x[i].x[j]);
    }
    fwrite(&startTime,sizeof(time_t),1,f); // Write the start time.
  }
  //printf("   startTime=%lu\n",startTime);
  if (fclose(f)!=0) {
    printf("Warning: Cannot close file: %s\n",filename);
  }
}
// Loads a previously saved uint8_vector.
// returns the startTime in the swrc struct,
// or 1234 if the file is corrupted in someway
long int SWRC_loaduint8_vector(uint8_vector *x, int N, char *filename) {
  //printf("Trying to load cfg file: %s\n",filename);
  FILE *f;
  time_t startTime[50];// There must be less than 50 modules in the simulation
  int i,j;
  int N2,corruptedCfgFile=0;
  if ((f=fopen(filename,"r"))==NULL) {
    printf("Warning: Could not open %s for reading\n",filename);
    return(1);
  }
  fread(&N2,sizeof(int),1,f); // Read the number of uint8_vectors in the array.
  if (N2!=N) { // the supplied number N does not equal the saved number
    printf("Corrupted cfg file %s: Number of saved modules=%d,expected number of modules=%d\n",filename,N2,N);
    return(1234);
  }
  //printf("   N=%d,N2=%d\n",N,N2);
  for (i=0;i<N;i++) { // sequentially read each uint8_vector
    fread(&x[i].N,sizeof(int),1,f); // Read the size of the i'th uint8_vector
    //printf("   x[%d].N=%d\n",i,x[i].N);
    if (x[i].N>0) { // If we allocate when x[i].N=0, causes problems when free'ing.
      x[i].x=(uint8_t*)realloc(x[i].x,x[i].N*sizeof(uint8_t)); // allocate memory for i'th uint8_vector.
      for (j=0;j<x[i].N;j++) { // read each element of the i'th uint8_vector
	x[i].x[j]=fgetc(f);    // read in the elements of the uint8_t vector.
	//printf("   x[%d].x[%d]=%d\n",i,j,x[i].x[j]);
	if (x[i].x[j]==EOF) {
	  printf("Corrupted cfg file %s: premature ending of file.",filename);
	  return(1234);
	} // End if checking EOF
      } // End reading each element of the i'th uint_8
    } // End if checking x[i].N>0
    fread(&startTime[i],sizeof(time_t),1,f); // Read the start time.
    if (i>0 && startTime[i]!=startTime[i-1]) { // uint8_t vectors are delineated by startTime. Any mismatch in size of the uint8_t vector means a corrupt .cfg file.
      // Make sure all startTime's are equal. 
      printf("Corrupted cfg file %s: startTime's in file don't match.",filename);
      return(1234);
    }
    //printf("   startTime[%d]=%lu\n",i,startTime[i]);
  } // End for over each uint8_vector
  fclose(f);
  printf("Loaded cfg file: %s\n",filename);
  return(startTime[0]);
}
// Given an input filename as a string this function breaks it apart into
// a dirname, filename filenum and fileExtension
// memory is calloc'd for these character arrays in this function.
// printf("%s/%s_%s.%s",dirname,filename,filenum,fileExt) should return inputFilename.
// The / should be part of the dirname
// The _ should be part of the filenum
// The . should be part of the fileext
// Any of the above can be empty: ""
// Then printf("%s%s%s%s",dirname,filename,filenum,fileext) should return inputFilename.
void SWRC_getDirnameFilenameFilenumFileext(char *ifn, char **dirname,char **filename,char **filenum, char **fileext) {
  int i;
  int N = strlen(ifn); // ifn is abbreviation for: inputFilename
  int lastSlash=-1; // position of the last /
  int lastUnder=-1; // position of the last _
  int lastDot=-1;   // position of the last .
  while(ifn[N-1]=='/') N--; // move backwards from end of string, in case user has put a '/' at the end of the filename.
  // Parse the ifn
  for (i=0;i<N;i++) {
    if (ifn[i]=='/' && ifn[i+1]!='\0') lastSlash=i;
    if (ifn[i]=='_' && ifn[i+1]>='0' && ifn[i+1]<='9') lastUnder=i;
    if (ifn[i]=='.' && ifn[i+1]>='a' && ifn[i+1]<='z') lastDot=i;
  }
  if (lastSlash>lastDot) lastDot=-1; // This addresses the situation where the filename starts with ../xyz 
  //printf("N=%d, lastSlash=%d, lastUnder=%d, lastDot=%d\n",N,lastSlash,lastUnder,lastDot);
  if (lastDot>0) { // Process the file extension if a dot is found.
    *fileext=(char*)realloc(*fileext,(N-lastDot+1)*sizeof(char));fileext[0][N-lastDot]='\0';
    strncpy(*fileext,&ifn[lastDot],N-lastDot);
    //printf("fileExt=%s\n",*fileext);
    N=lastDot;
  } else {*fileext=(char*)realloc(*fileext,sizeof(char));fileext[0][0]='\0';}
  if (lastUnder>0) { // Process the file number if _ is found.
    *filenum = (char*)realloc(*filenum,(N-lastUnder+1)*sizeof(char));filenum[0][N-lastUnder]='\0';
    strncpy(*filenum,&ifn[lastUnder],N-lastUnder);
    //printf("fileNum=%s\n",*filenum);
    N=lastUnder;
  } else {*filenum=(char*)realloc(*filenum,sizeof(char));filenum[0][0]='\0';}
  // Process the filename
  *filename = (char*)realloc(*filename,(N-lastSlash)*sizeof(char));filename[0][N-lastSlash-1]='\0';
  strncpy(*filename,&ifn[lastSlash+1],N-lastSlash-1);
  //printf("filename=%s\n",*filename);
  if (lastSlash>0) { // Process the dirname if / is found.
    *dirname=(char*)realloc(*dirname,(lastSlash+2)*sizeof(char));dirname[0][lastSlash+1]='\0';
    strncpy(*dirname,ifn,lastSlash+1);
    //printf("dirname=%s\n",*dirname);
  } else {*dirname=(char*)realloc(*dirname,sizeof(char));dirname[0][0]='\0';}
}
// given a filename, which can be of the form:
// JVDD_N13_M5_K8_X13_Y5_noCycle4_0012 or
// JVDD_N13_M5_K8_X13_Y5_noCycle4/JVDD_N13_M5_K8_X13_Y5_noCycle4_0012 or
// /home/kheong/Dropbox/swrc_C/makeCode/JVDD_N13_M5_K8_X13_Y5_noCycle4/JVDD_N13_M5_K8_X13_Y5_noCycle4_0012
// This function checks for the existence of a relevant .cfg file and if it exists, 
// loads it in which is an array of uint8_vector's of length N. 
// the .cfg file should have been saved as a uint8_vector of length N.
// returns 1 on success or 0 on failure.
long int SWRC_loadcfgFile(uint8_vector *cfgFile, int N,char *filename) {
  char *myDirname=NULL;
  char *myFilename=NULL;
  char *myFilenum=NULL;
  char *myFileext=NULL;
  char *trialfn=NULL;
  long int y;
  SWRC_getDirnameFilenameFilenumFileext(filename,&myDirname,&myFilename,&myFilenum,&myFileext);
//  printf("SWRC_loadcfgFile:%s%s%s%s\n",myDirname,myFilename,myFilenum,myFileext);

// printf("myDirname=%s\n",myDirname);
// printf("myFilename=%s\n",myFilename);
// printf("myFilenum=%s\n",myFilenum);
// printf("myFileext=%s\n",myFileext);

  asprintf(&trialfn,"%s%s%s.cfg",myDirname,myFilename,myFilenum); // The original name with .cfg extension
  if (access(trialfn,F_OK)!=-1) {
    printf("Trialfn: Loading file %s\n",trialfn);
    y=SWRC_loaduint8_vector(cfgFile,N,trialfn);
    free(trialfn);free(myDirname);free(myFilename);free(myFilenum);free(myFileext);return(y);
  } else printf("Trialfn: %s couldn't load\n",trialfn);

  free(trialfn); asprintf(&trialfn,"%s%s/%s%s.cfg",myDirname,myFilename,myFilename,myFilenum); // Try one directory down.
  if (access(trialfn,F_OK)!=-1) {
    printf("Trialfn: Loading file %s\n",trialfn);
    y=SWRC_loaduint8_vector(cfgFile,N,trialfn);
    free(trialfn);free(myDirname);free(myFilename);free(myFilenum);free(myFileext);return(y);
  } else printf("Trialfn: %s couldn't load\n",trialfn);

  free(trialfn); asprintf(&trialfn,"%s%s%s/%s%s.cfg",myDirname,myFilename,myFilenum,myFilename,myFilenum); // Try one directory down, with filenum appended to directory
  if (access(trialfn,F_OK)!=-1) {
    printf("Trialfn: Loading file %s\n",trialfn);
    y=SWRC_loaduint8_vector(cfgFile,N,trialfn);
    free(trialfn);free(myDirname);free(myFilename);free(myFilenum);free(myFileext);return(y);
  } else printf("Trialfn: %s couldn't load\n",trialfn);

  free(trialfn); asprintf(&trialfn,"%s%s/%s%s.cfg",myDirname,myFilename,myFilename,"_0001"); // Try one directory down, with filenum='0001'
  if (access(trialfn,F_OK)!=-1) {
    printf("Trialfn: Loading file %s\n",trialfn);
    y=SWRC_loaduint8_vector(cfgFile,N,trialfn);
    free(trialfn);free(myDirname);free(myFilename);free(myFilenum);free(myFileext);return(y);
  } else printf("Trialfn: %s couldn't load\n",trialfn);

  free(trialfn); asprintf(&trialfn,"%s%s/%s%s/%s%s.cfg",myDirname,myFilename,myFilename,myFilenum,myFilename,myFilenum); // Try 2 directories down
  if (access(trialfn,F_OK)!=-1) {
    printf("Trialfn: Loading file %s\n",trialfn);
    y=SWRC_loaduint8_vector(cfgFile,N,trialfn);
    free(trialfn);free(myDirname);free(myFilename);free(myFilenum);free(myFileext);return(y);
  } else printf("Trialfn: %s couldn't load\n",trialfn);

  free(trialfn); asprintf(&trialfn,"%s%s/%s%s/%s%s.cfg",myDirname,myFilename,myFilename,"_0001",myFilename,"_0001"); // Try 2 directories down with a default filenum=0001
  if (access(trialfn,F_OK)!=-1) {
    printf("Trialfn: Loading file %s\n",trialfn);
    y=SWRC_loaduint8_vector(cfgFile,N,trialfn);
    free(trialfn);free(myDirname);free(myFilename);free(myFilenum);free(myFileext);return(y);
  } else printf("Trialfn: %s couldn't load\n",trialfn);
  printf("Failed to load %s\n",filename);

  free(myDirname);
  free(myFilename);
  free(myFilenum);
  free(myFileext);
  exit(0);
}

/////////////////////////////////////////
// Functions for handling command strings and argument strings
/////////////////////////////////////////
int SWRC_copyStringUptoNextDelimiter(char *output,int N_output, const char *command) {
  int i;
  int noParen=0;
  for (i=0;i<N_output;i++) {
    if (command[i]==')' && noParen==0) {
      //printf("Found closing paren at postion %d\n",i);
      output[i]='\0'; // found closing paren. Append 
      return(i+3);
    }
    output[i]=command[i];
    //printf("i=%3d, output[i]=%c, command[i]=%c\n",i,output[i],command[i]);
    if(command[i]=='(') noParen++;
    if(command[i]==')') noParen--;
  }
  output[N_output-1]='\0'; // maximum string length reached.
  return(N_output);
}

// takes a command given in *command
// and a pattern to match in *toMatch.
// *index is an index into *command at which the current 
//        command is being executed. 
// *commandParameters is an output. command parameters
//        of the command are copied into here.
int SWRC_matchCommand(const char *command, const char *toMatch, int *index,char *commandParameter,int N_cp) {
  int N=strlen(toMatch);
  int index_start=*index;
  int i;
  //printf("command=\"%s\"\n*index=%d\ncommand[%d]=%s\ntoMatch=\"%s\"\nN=%d\n",command,*index,*index,&command[*index],toMatch,N);
  if (strncmp(&command[*index],toMatch,N)==0 && (command[*index+N]==' ' || command[*index+N]=='(')) {
    *index+=SWRC_copyStringUptoNextDelimiter(commandParameter,N_cp,&command[*index+N+1])+N;
    while(command[*index]==' ') (*index)++;
    //printf("CommandMatch     : ");for(i=index_start;i<(*index);i++) printf("%c",command[i]);printf("\n");
    //printf("CommandParameter : %s\n",commandParameter);
    //printf("*index=%d, index_start=%d\n",*index,index_start);
    //printf("command[*index]=%s\n",&command[*index]);
    return(1);
  } else return(0);
}

// takes a string holding a comma-separated list of assignments like:
// "M=3, N=12, f=1.23"
// an *index pointing to the next argument to be processed in the string 
// *argName is the name (string) of an argument to search for.
// a pointer to  uint8_t
// and is of the given type 
// type can take values:
// 's': string array
// 'i': integer
// 'f': float
// 'd': double
int SWRC_getNextArgument(const char *CSV_parm,int *index,int *nextEqualSign, const char *argName) {
  int i,j;
  int nextComma;
  *nextEqualSign=0;
  //printf("  *index=%d\n",*index);
  //printf("  strlen(CSV_parm)=%lu\n",strlen(CSV_parm));
  for (j=0,i=*index;i<strlen(CSV_parm);i++){
    if (CSV_parm[i]==',') break;
    if (CSV_parm[i]=='=') *nextEqualSign=i;
  }
  //printf("  i=%d\n",i);
  //printf("  argName="); for (j=*index;j<(*nextEqualSign);j++) printf("%c",CSV_parm[j]); printf("\n");
  //printf("  Found argument: ");for (j=*index;j<i;j++) printf("%c",CSV_parm[j]); printf("\n");
  //printf("  equal sign at %d\n",*nextEqualSign);
  if (strncmp(&CSV_parm[*index],argName,strlen(argName))==0) {
    (*index)=(i+1);
    return(1);
  }
  (*index)=(i+1);
  return(0);
}

// Remove unneeded whitespace from a string 
void SWRC_removeSpaces(char *string) {
  int i,j;
  int parenCount=0;
  //printf("string=%s\n",string);
  for (i=0;i<strlen(string);i++) {
    if(string[i]=='"') parenCount=1-parenCount;
    //printf("i=%d, string[%d]=%c, parenCount=%d\n",i,i,string[i],parenCount);
    if(string[i]==' ' && parenCount==0) {
      for (j=i+1;j<=strlen(string);j++) {
	string[j-1]=string[j];
      }
      i--;
    }
  }
}

// Delete the argument pointed to by index from the string
// in *arg. 
// i is the index of the start of argument to be deleted
// j is a point inside the argument. The function will
// search forward to the next ; or , and delete from that 
// character to the beginning of the argument.
void SWRC_deleteArgumentFromString(char *arg, int i, int j) {
  // delete the parameter we've found from the arg string.
  //printf("arg=%s\n",arg);
  //printf("i=%d,j=%d,openBracket=%d,closeBracket=%d\n",i,j,openBracket,closeBracket);
  for(;arg[j]!=';'&&arg[j]!=','&&arg[j]!='\0';j++); // advance to the  next ; or ,
  if (arg[j]==';' || arg[j]==',') j++;
  for(;arg[j]!='\0';j++) arg[i++]=arg[j]; // shift the text at the end of the parm down.
  arg[i]='\0';
}
// read a single argument from an input string
// inputs: *arg the input string containing a comma delimited list of the arguments
//         eg: *M=24,*N=15,*parm=1.25,*alpha=-12.2
//         *stringName the name of the string to be searched
//         eg: parm
//         *output. The read output will be stored here.
//         *formatString: formatted according to this format string.
int SWRC_readSingleArgumentFromString(char *arg, const char *stringName, void *output, const char *formatString) {
  int i;
  char searchString[100]="*";
  char controlString[100]="*";
  strcat(searchString,stringName);
  strcat(searchString,"=");
  //printf("searchString=%s\n",searchString);
  strcat(controlString,stringName);
  strcat(controlString,"=");
  strcat(controlString,formatString);
  //printf("controlString=%s\n",controlString);
  //printf("arg=%s\n",arg);
  for (i=0;i<strlen(arg);i++) {
    if (strncmp(searchString,&arg[i],strlen(searchString))==0) {
      // printf("%s\n",&arg[i+strlen(searchString)]);
      // printf("%s\n",&arg[i]);
      if (sscanf(&arg[i],controlString,output)==1) {
	SWRC_deleteArgumentFromString(arg,i,i);
	return(1);
      } else {
	return(0);
      }
    }
  }
  return(0);
}

// This is a private function, only used by readMultipleArgumentsFromString
// below. It goes into the comma-delimited string and reads each value
// according to formatString. 
// it returns the number of elements read. 
int SWRC_readVectorFromString(const char *string, void **output, int N, const char *formatString, int unitSize) {
  int i,j,count=0;
  double *x;
  //printf("N=%d, unitSize=%d,formatString=%s\n",N,unitSize,formatString);
  *output=(void*)calloc(N,unitSize);
  for (i=0,j=1;i<N;i++) {
    //printf("i=%d,j=%d, string[j]=%s\n",i,j,&string[j]);
    if (sscanf(&string[j],formatString,*output+i*unitSize)==0){printf("Unable to read [vector]\n");return(count);}
    count++;
    //if (sscanf(&string[j],formatString,&x)==0){printf("Unable to read [vector]\n");}
    while(string[j]!=',' && string[j]!=']') j++; j++;
    //x=*output+i*unitSize;
    //printf("i=%d, j=%d output=%lf\n",i,j,*x);
  }
  return(count);
}

// Analogous to the readSingleArgumentFromString function
// but reads a vector from the string.
// *arg holds the string with the input arguments in it.
// *stringName is the name of the string that we want returned.
// *output is a pointer to memory to be filled by this function.
//   since we are going to allocate memory and need to assign a value 
//   to *output, we need a pointer to *output to be able to manipulate
//   it's contents. ie: we need **output. It is cast as a void so any
//   type can be accommodated with this function.
//   This function will allocate memory for the read in values and
//   assign it to *output. It will then fill the contents of *output.
// *N is the number of elements read. It will be modified by the function
//   to hold the number of elements in *output.
// *formatString is the format string to read 1 element of the array.
// The array is comma-delimited and each element headed by an *
// eg: *M=24,*N=15,*alpha=-12.2,*h=[1.2,2.4,1.3] 
int SWRC_readMultipleArgumentsFromString(char *arg, const char *stringName, void **output, long unsigned int *N,int unitSize, const char *formatString) {
  int i,j,k,openBracket,closeBracket,numberOfReadNumbers;
  char searchString[100]="*";
  //char controlString[100]="*";
  int M=0; // a temporary variable holding the number of elements being read.
  strcat(searchString,stringName);  strcat(searchString,"=");
  //strcat(controlString,stringName); strcat(controlString,"="); strcat(controlString,formatString);
  for (i=0;i<strlen(arg);i++) {
    if (strncmp(searchString,&arg[i],strlen(searchString))==0) { // found the search string.
      for (openBracket=closeBracket=0,j=i;j<strlen(arg);j++) { // search for the open and close braces.
	if (arg[j]=='[') openBracket=j;
	if (arg[j]==',') M++;
	if (arg[j]==']') {closeBracket=j;break;}
      }
      if (closeBracket==0||openBracket==0) {
	printf("Cannot find [vector] in %s\n",&arg[i]);
	return(0);
      }
      if (*N!=0 && output!=NULL) free(*output); // *output already allocated. Free previously allocated
      *N=M;                     // and reset *N to its new value equal to M.
      numberOfReadNumbers=SWRC_readVectorFromString(&arg[openBracket],output,++(*N),formatString,unitSize);
      SWRC_deleteArgumentFromString(arg,i,j);
      //printf("arg after extraction=%s\n",arg);
      return(numberOfReadNumbers);
    }
  }
  return(0);
}

int SWRC_readStringArgumentFromString(char *arg, const char *stringName, void **output, long unsigned int *N, const char *formatString) {
  int i,j,k,openBracket,closeBracket,numberOfReadNumbers;
  char searchString[100]="*";
  //char controlString[100]="*";
  strcat(searchString,stringName);  strcat(searchString,"=");
  //strcat(controlString,stringName); strcat(controlString,"="); strcat(controlString,formatString);
  for (i=0;i<strlen(arg);i++) { //iterate over arg searching for searchString.
    if (strncmp(searchString,&arg[i],strlen(searchString))==0) { // found the search string.
      for (openBracket=closeBracket=-1,j=i;j<strlen(arg);j++) { // search for the open and close braces.
	if (arg[j]=='[') openBracket=j;                       // string delimited by [ ]
	if (arg[j]==']') {closeBracket=j;break;}
      }
      if (closeBracket==-1||openBracket==-1) {
	printf("Found %s, but cannot find [string] in %s\n",searchString,arg);
	return(0);
      }
     //if (*N!=0 && *output!=NULL) free(*output); // *output already allocated. Free previously allocated
     if (*output!=NULL) free(*output); // *output already allocated. Free previously allocated
     *N=closeBracket-openBracket;
     *output=(void*)calloc(*N,sizeof(char));
     strncpy(*output,&arg[openBracket+1],closeBracket-openBracket-1);
     SWRC_deleteArgumentFromString(arg,i,j);
     return(1);
    }
  }
  return(0);
}
void SWRC_readIntFromStringBackwards(char *arg,int pos,int *output) {
  int i;
  *output=0;
  for(i=1;arg[pos]>='0' && arg[pos]<='9';i*=10,pos--) {
    *output+=i*(arg[pos]-'0');
  }
}

void SWRC_readIntFromStringForwards(char *arg,int pos,int *output) {
  *output=0;
  for(;arg[pos]>='0' && arg[pos]<='9';pos++) {
    (*output)*=10;
    (*output)+=(arg[pos]-'0');
  }
}
// Read a date argument from a string of the form:
// 2019/07/16 or 
// 07/16   in year/month/date format. 
// current year is returned if no year is provided.
int SWRC_readDateArgumentFromString(char *arg, const char *stringName, struct tm *output) {
  //printf("In function SWRC_readDateArgumentFromString, arg=%s,stringName=%s\n",arg,stringName);
  int i,j,k,slash1,slash2,semicolon;
  char searchString[100]="*";
  time_t t=time(NULL);                // used to get the current time om seconds since epoch.
  struct tm *localTime=localtime(&t); // convert this into broken-down time in the struct tm structure.     
  strcat(searchString,stringName);  strcat(searchString,"=");
  for (i=0;i<strlen(arg);i++) {
    if (strncmp(searchString,&arg[i],strlen(searchString))==0) { // found the search string.
      for (slash1=slash2=semicolon=-1,j=i;j<strlen(arg);j++) { // search for the two slashes and the semicolon markers that delineate a date.
	if (arg[j]=='/') {                   // found a slash that demarcates the year/month/day
	  if (slash1==-1) slash1=j;          // if it's the first slash, store it in slash1 
	  else slash2=j;                     // otherwise store it in slash2.
	}
	if (arg[j]==';') {semicolon=j;break;} // found the terminating semicolon
      }
      if (semicolon!=-1) { // a successful parse only if we found the semicolon
	if (slash2==-1) {  // Only 2 numbers given, like 7/5. They are presumed to be month and day. Year is 
	  output->tm_year=localTime->tm_year; // take the year from the current time.
	  SWRC_readIntFromStringBackwards(arg,slash1-1,&output->tm_mon);output->tm_mon--;
	  SWRC_readIntFromStringForwards(arg,slash1+1,&output->tm_mday);
	} else { // Assumed that 3 numbers given like: 2019/7/7
	  SWRC_readIntFromStringBackwards(arg,slash1-1,&output->tm_year);
	  if (output->tm_year<100)output->tm_year+=100;
	  if (output->tm_year>2000)output->tm_year-=1900;
	  SWRC_readIntFromStringBackwards(arg,slash2-1,&output->tm_mon);output->tm_mon--;
	  SWRC_readIntFromStringForwards(arg,slash2+1,&output->tm_mday);
	}
	return(1);
      } else { // didn't find the terminating semicolon.
	printf("Syntax Error: No semicolon termination in the line: arg=%s\n",arg);
	return(0);
      }
    }
  }
}

// Read a time argument from a string of the form:
// hh:mm
int SWRC_readTimeArgumentFromString(char *arg, const char *stringName, struct tm *output) {
  //printf("In function SWRC_readTimeArgumentFromString, arg=%s,stringName=%s\n",arg,stringName);
  int i,j,k,colon,semicolon; // position of the colon/semicolon in the string.
  char searchString[100]="*";
  strcat(searchString,stringName);  strcat(searchString,"=");
  for (i=0;i<strlen(arg);i++) {
    if (strncmp(searchString,&arg[i],strlen(searchString))==0) { // found the search string.
      for (semicolon=colon=-1,j=i;j<strlen(arg);j++) { // search for the two slashes and the semicolon markers that delineate a date.
	if (arg[j]==':') colon=j;
	if (arg[j]==';') {semicolon=j; break;}
      }
      if (colon!=-1 && semicolon!=-1) { // a successful parse only if we found the semicolon
	SWRC_readIntFromStringBackwards(arg,colon-1,&output->tm_hour);
	SWRC_readIntFromStringForwards(arg,colon+1,&output->tm_min);
	output->tm_sec=0;
	return(1);
      } else { // didn't find the terminating semicolon.
	printf("Syntax Error: No semicolon termination in the line: arg=%s\n",arg);
	return(0);
      }
    }
  }
}

// search through the string *s
// for char c in it. If any of the characters in *s
// equals c, returns true
// otherwise returns false
bool SWRC_ifAnyChar(char *s, char c) {
  int i;
  for (i=0;i<strlen(s);i++) {
    if (s[i]==c) return(true);
  }
  return(false);
}

char *SWRC_appendExtToString(char *basename, char *ext) {
  int N;
  int i;
  int N_ext;
  char *output;
  N=strlen(basename);
  N_ext=strlen(ext);
  output=(char*)calloc(N+N_ext+1,sizeof(char));
  strcpy(output,basename);
  //for (i=0;i<25;i++) printf("%2d %c\n",i,output[i]);
  strcat(output,ext);
  //for (i=0;i<25;i++) printf("%2d %c\n",i,output[i]);
  return(output);
}
/////////////////////////////////////////
// Functions for random number generation
/////////////////////////////////////////
void SWRC_randomize(int *idum) {
  /*time_t t1;
  clock_t t2;
  time(&t1);
  t2 = clock();
  *idum=t1;
  *idum+=t2;
  *idum*=-1;*/
  struct timeval t1;
  gettimeofday(&t1, NULL);
  *idum = t1.tv_usec * t1.tv_sec;
  SWRC_ran2(idum);
  //SWRC_ran2(idum);
  //SWRC_ran2(idum);
  //printf("random number seed %d\n",*idum);
}

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
//#define EPS 1.2e-13
#define EPS 1.2e-7
#define RNMX (1.0-EPS)
float SWRC_ran0(int *idum){
  long k;
  float ans;

  *idum^=123459876;
  k=(*idum)/IQ;
  *idum=IA*(*idum-k*IQ)-IR*k;
  if (*idum<0) *idum+=IM;
  ans=AM*(*idum);
  *idum^=123459876;
  return(ans);
}

// ran1 is an improved version of ran0, but slightly more complex.
float SWRC_ran1(int *idum){
  int j;
  long k;
  static int iy=0;
  static int iv[NTAB];
  float temp;

  if (*idum<=0 || !iy) {
    if (-(*idum) <1) *idum=1;
    else *idum=-(*idum);
    for (j=NTAB+7;j>=0;j--) {
      k=(*idum)/IQ;
      *idum=IA*(*idum-k*IQ)-IR*k;
      if (*idum<0) *idum += IM;
      if (j<NTAB) iv[j] = *idum;
    }
    iy = iv[0];
  }
  k = (*idum)/IQ;
  *idum=IA*(*idum-k*IQ)-IR*k;
  if(*idum<0) *idum+=IM;
  j=iy/NDIV;
  iy=iv[j];
  iv[j]=*idum;
  if ((temp=AM*iy)>RNMX) return RNMX;
  else return temp;
}

#define IM1 2147483563
#define IM2 2147483399
#define AM1 (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NDIV1 (1+IMM1/NTAB)
//ran2 is a RNG with longer period (>2e18) of L'Ecuyer with Bays-Durham shuffle
// and added safeguards. Returns a uniform random deviate between 0.0 and 1.0
// (exclusive of endpoint values). Call with idum a negative integer to          
// initialize; thereafter do not alter idum between successive calls to the          
// function. RNMX should approximate the largest floating value that is less
// than 1.ran2 is about twice as complex as ran0.
double SWRC_ran2(int *idum) {
  int j;
  long k;
  static int idum2 = 123456789;
  static int iy=0;
  static int iv[NTAB];
  double temp;
  if (*idum<=0) {
    if (-(*idum) < 1) *idum = 1;
    else *idum = -(*idum);
    idum2 = (*idum);
    for (j=NTAB+7;j>=0;j--) {
      k=(*idum)/IQ1;
      *idum=IA1*(*idum-k*IQ1)-IR1*k;
      if (*idum<0) *idum += IM1;
      if (j<NTAB) iv[j] = *idum;
    }
    iy = iv[0];
  }
  k = (*idum)/IQ1;
  *idum = IA1*(*idum-k*IQ1) - k*IR1;
  if (*idum<0) *idum+=IM1;
  k=idum2/IQ2;
  idum2=IA2*(idum2-k*IQ2)-k*IR2;
  if (idum2<0) idum2+=IM2;
  j=iy/NDIV1;
  iy = iv[j]-idum2;
  iv[j] = *idum;
  if (iy<1) iy+=IMM1;
  if((temp=AM1*iy)>RNMX) return RNMX;
  else return temp;
}

//generate a normally distributed random variable
float SWRC_randn(int *idum) {
  static int iset=0;
  static float gset;
  float fac,rsq,v1,v2;

  if (iset==0) {
    do {
      v1=2.0*SWRC_ran2(idum)-1.0;
      v2=2.0*SWRC_ran2(idum)-1.0;
      rsq=v1*v1+v2*v2;
    } while(rsq>=1.0 || rsq==0.0);
    fac = sqrt(-2.0*log(rsq)/rsq);
    gset = v1*fac;
    iset=1;
    return(v2*fac);
  } else {
    iset=0;
    return(gset);
  }
}
// returns the largest power of 2 in N
int SWRC_log2(int N)  {
  int i,n;
  for (n=0,i=N;i>1;i>>=1,n++);
  return(n);
}
// write an instance of a normalized random variable to *output
// with given mean and standard deviation as a percentage of the mean
float SWRC_normalDist(float mean, float sigma_percent, int *idum) {
  float sd = sigma_percent*mean;
  //printf("in function normalDist, sd=%f,mean=%f\n",sd,mean);
  return(mean+sd*SWRC_randn(idum));
}
// It was found that polynomial of length 18 was insufficient for Roger
// So I re-read NRC and decided on polynomial of length 31: (31,3,0) 
// which can take up to 4 trillion bits before it repeats.
#define IB1 1		   //Powers of 2.
#define	IB2 2
#define	IB3 4              // added for polynomial (31,3,0)
#define	IB5 16
#define	IB18 131072	  
#define	IB31 2147483648
//#define MASK (IB1+IB2+IB5)
#define MASK (IB3)   // modified for polynomial (31,3,0)
// Returns as an integer a random bit, based on the 
// 18 low-significance bits in iseed (which is modified 
// for the next call).
int SWRC_irbit2(unsigned long *iseed) {
  //if (*iseed & IB18) { // Change all masked bits, shift, and put 1 into bit 1.
  if (*iseed & IB31) { // Modified for polynomial (31,3,0)
    *iseed=((*iseed ^ MASK) << 1) | IB1;
    return 1;
  } else { // Shift and put 0 into bit 1.
    *iseed <<= 1;
    return 0;
  }
}
/////////////////////////////////////////
// Functions for double arrays
/////////////////////////////////////////
void SWRC_pushNewEntryToDoubleArray(void ***x, long unsigned int **N, long unsigned int *N_N, char *type,void *input, int N_input) {
  int i;
  (*N_N)++;
  (*N)=(long unsigned int*)realloc((*N),(*N_N)*sizeof(long unsigned int));
  *N[(*N_N)-1]=N_input;
  //if (strcmp(type,"char")==0) {
    printf("N_N=%lu\n",(*N_N)-1);
    //printf("*Before: x=%p, (*N_N)*sizeof(char*)=%d\n",*x,(*N_N)*sizeof(char*));
    (*x)=realloc((*x),((*N_N)+5)*sizeof(char *));
    //printf("*After: x=%p, N_input=%d\n",*x,N_input);
    *x[(*N_N)-1]=calloc(N_input,sizeof(char));
    *x[(*N_N)]=calloc(N_input,sizeof(char));
    for (i=0;i<N_input;i++) {(*(char***)x)[(*N_N)-1][i]=((char*)input)[i];}
    for (i=0;i<N_input;i++) {(*(char***)x)[(*N_N)][i]=((char*)input)[i];}
    //}

  // The original code on which the above generalization was derived is here:
  //berResult->N_N_name++;
  //berResult->N_name=(long unsigned int*)realloc(berResult->N_name,berResult->N_N_name*sizeof(long unsigned int));
  //berResult->N_name[berResult->N_N_name-1]=strlen(fieldName);
  //berResult->name=(char **)realloc(berResult->name,berResult->N_N_name*sizeof(char *));
  //berResult->name[berResult->N_N_name-1]=(char*)calloc((strlen(fieldName)+1),sizeof(char));
  //strcpy(berResult->name[berResult->N_N_name-1],fieldName);
}
long int SWRC_getArraySizeFromNdims(int nDims,int N0, int N1, int N2, int N3) {
  long int size=1;
  if (nDims<0 || nDims>4) {
    printf("Invalid value for nDims=%d in getSizeFromNdims\n",nDims);
    exit(-1);
  }
  if (nDims==0) return(0);
  size*=N0;
  if (nDims==1) return(size);
  size*=N1;
  if (nDims==2) return(size);
  size*=N2;
  if (nDims==3) return(size);
  size*=N3;
  return(size);
}

/////////////////////////////////////////
// Functions for running the simulation
/////////////////////////////////////////
void SWRC_printHeader(char *moduleName){
  printf("*************************************\n** %s\n*************************************\n",moduleName);
}


////////////////////////////////////////////////
// Some mathematical functions needed by media.c
// that are generic enough to go into SWRC.c
////////////////////////////////////////////////
int SWRC_mod(double x, int lim) {
  int i;
  i = x+0.5;            // convert double to int.
  while (i<0) {i+=lim;} // ensure greater than 0
  i%=lim;               // bring into correct range
  return(i);
}
double SWRC_gaussian2D(double y, double x, double sigmaY, double sigmaX) {
  return(exp(-x*x/2/(sigmaX*sigmaX)-y*y/2/(sigmaY*sigmaY)));
}
////////////////////////////////////////
// Functions for getting the time/date//
////////////////////////////////////////
char *SWRC_getTimeString() {
  char *tt;
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  asprintf(&tt,"%04d/%02d/%02d %02d:%02d:%02d",tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  return(tt);
}
void SWRC_printTimet(time_t *t,char *timeName) {
  printf("%10s:%12ld %s",timeName,*t,ctime(t));
}

////////////////////////////////////////
// Functions for manipulating filenames for the codes
////////////////////////////////////////
// check to see whether dirname exists and is a directory
// if so, it is a code directory with the relevant .pchk, .gen, .alist, .pbm files
// inside. The filename should be the same as the dirname.
// *filename will be allocated memory and the updated filename
// (assumed to be the same as the dirName) is copied there.
// If dirname does not exist as a directory, then dirname
// is just copied as-is to *filename.
void SWRC_checkCodeDirExistenceAndCopyName(const char *dirname, char **filename) {
  DIR *dir;
  const char *filename2;
  int i;
  for (i=0;i<strlen(dirname);i++) {
    if (dirname[i]=='/') filename2=&dirname[i+1];
  }
  if ((dir=opendir(dirname))!=NULL) {
    // directory exists
    //printf("%s is a directory\n",dirname);
    closedir(dir);
    asprintf(filename,"%s/%s",dirname,filename2);
  } else  {
    //printf("%s is a assumed to be a filename root\n",dirname);
    // directory does not exist
    asprintf(filename,"%s",dirname);
  }
}
int SWRC_countFileLines(char *filename) {
  int i;
  FILE *f;
  char tmp[5000];
  if ((f=fopen(filename,"r"))!=NULL) {
    for(i=0;fgets(tmp,5000,f)!=NULL; i++) {
      //printf("%d %s",i,tmp);
    }
    fclose(f);
  } else {
    printf("Cannot open %s for reading\n",filename);
  }
  return(i);
}
////////////////////////////////////////
// Functions for drawing latex docs to a file
////////////////////////////////////////
void SWRC_fwriteLatexFileHeader(FILE *f) {
  char *tt = SWRC_getTimeString();
  fprintf(f,"%%%% Latex code created by SWRC on %s\n%%%% Author: Kheong Sann Chan.\n\\documentclass{beamer}\n\\usepackage{tikz}\n\\usetikzlibrary{datavisualization.formats.functions,plotmarks,calc,decorations.pathreplacing}\n\\usepackage{ifthen}\n\\setbeamertemplate{navigation symbols}{}\n\\setbeamertemplate{footline} {}\n",tt);
  free(tt);
}
void SWRC_fwriteLatexFileHeaderArticle(FILE *f) {
  char *tt = SWRC_getTimeString();
  fprintf(f,"%%%% Latex code created by SWRC on %s\n%%%% Author: Kheong Sann Chan.\n\\documentclass{article}\n\\usepackage{tikz}\n\\usetikzlibrary{datavisualization.formats.functions,plotmarks,calc,decorations.pathreplacing}\n\\usepackage{ifthen}\n\\usepackage{verbatim}\n\\pagestyle{empty}\n",tt);
  free(tt);
}
void SWRC_fwriteLatexBeginDocument(FILE *f) {
  fprintf(f,"\\begin{document}\n");
}
void SWRC_fwriteLatexEndDocument(FILE *f) {
  fprintf(f,"\\end{document}\n");
}
void SWRC_fwriteLatexBeginFrame(FILE *f,char *frameTitle,char *options) {
  fprintf(f,"\\begin{frame}%s{%s}\n",options,frameTitle);
}
void SWRC_fwriteLatexEndFrame(FILE *f) {
  fprintf(f,"\\end{frame}\n");
}
void SWRC_fwriteLatexBeginTikzPicture(FILE *f,const char *options) {
  fprintf(f,"    \\begin{tikzpicture}%s\n",options);
}
void SWRC_fwriteLatexBoundingBox(FILE *f,float xmin,float ymin,float xmax,float ymax) {
  fprintf(f,"    \\path[use as bounding box,draw](%.2f,%.2f) rectangle (%.2f,%.2f);\n",xmin,ymin,xmax,ymax);
}
void SWRC_fwriteLatexEndTikzPicture(FILE *f) {
  fprintf(f,"    \\end{tikzpicture}\n");
}
void SWRC_typesetTexFile(char *filename) {
  char *command;
  asprintf(&command,"pdflatex %s.tex && pdflatex %s.tex && rm -f %s.aux %s.log %s.nav %s.out %s.snm %s.toc\n",filename,filename,filename,filename,filename,filename,filename,filename);
  printf("%s",command);
  system(command);
  free(command);
}
////////////////////////////////////////
// Functions for coordInt
////////////////////////////////////////

////////////////////////////////////////
// Functions for handling memory
////////////////////////////////////////
// Zero out N bytes at memory location p.
// The memory must be allocated before calling.
void SWRC_zeroOutMem(uint8_t *p, long unsigned int N) {
  int i;
  for (i=0;i<N;i++) p[i]=0;
}

////////////////////////////////////////
// Sorting routines
////////////////////////////////////////
#define SWAP(a,b) itemp=(a);(a)=(b);(b)=itemp;
#define NSTACK 50
// Implementation of the quicksort algorithm from NRC
// Indexes an array of integers arr[0..n-1] , i.e., outputs the array indx[0..n-1] such that arr[indx[j]] is
// in ascending order for j = 0, 1, . . . , N-1 . The input quantities n and arr are not changed.
void SWRC_getIntegerPermutation(unsigned long int n, int *arr, unsigned int *indx) {
  int i,indxt,ir=n-1,itemp,j,k,l=0;
  int jstack=0,*istack;
  int a;
  istack=(int*)calloc(NSTACK+1,sizeof(int));
  for (;;) {
    //printf("getSurvivorIndexTable:[%2d:%2d]\n",l,ir);
    if (ir-l < 7) { // small subarray length. Do the straight insertion
      for (j=l+1;j<=ir;j++) {
	indxt=indx[j];
	a=arr[indxt];
	for (i=j-1;i>=l;i--) {
	  //printf("  i=%d, j=%d, l=%d\n",i,j,l);
	  if (arr[indx[i]] <= a) {break;}
	  indx[i+1]=indx[i];
	}
	indx[i+1]=indxt;
      }
      if (jstack == 0) break; // Nothing left to do. Exit.
      ir=istack[jstack--];    // pop stack and begin a new
      l=istack[jstack--];     // round of paritioning
    } else {                  // quicksort partitioning.
      k=(l+ir) >> 1;          // k = average of l and ir
      SWAP(indx[k],indx[l+1]);// Choose a paritioning element k
      // force metrics into the order: a[l]<a[l+1]<a[ir] 
      if (arr[indx[l]] > arr[indx[ir]])   {SWAP(indx[l],indx[ir])}
      if (arr[indx[l+1]] > arr[indx[ir]]) {SWAP(indx[l+1],indx[ir])}
      if (arr[indx[l]] > arr[indx[l+1]])  {SWAP(indx[l],indx[l+1])}
      i=l+1;                  // Initialize pointers
      j=ir;                   // for paritioning
      indxt=indx[l+1];        // partitioning element index
      a=arr[indxt];   // partitioning element
      for (;;) {              // The innermost loop
	do {i++;} while (arr[indx[i]] < a); // scan up to find element > a
	do {j--;} while (arr[indx[j]] > a); // scan down to find element < a
	if (j < i) break;     // pointers crossed, partitioning complete 
	SWAP(indx[i],indx[j])}// exchange elements, end inner loop
      indx[l+1]=indx[j];      // insert partitioning element
      indx[j]=indxt;          // into correct location in the list
      jstack += 2;
      // Push pointers to larger subarray onto stack. 
      // process the smaller subarray immediately.
      if (jstack > NSTACK) printf("NSTACK too small in indexx.");
      if (ir-i+1 >= j-l) {
	istack[jstack]=ir;
	istack[jstack-1]=i;
	ir=j-1;
      } else {
	istack[jstack]=j-1;
	istack[jstack-1]=l;
	l=i;
      }
    }
  }
  free(istack);
}
// calculate the Hamming distance between 2 sequences.
int SWRC_HammingDistance(uint8_t *s1, uint8_t *s2, int N) {
  int i,d;
  for (i=0,d=0;i<N;i++) {
    if (s1[i]!=s2[i]) d++;
  }
  return(d);
}

////////////////////////////////////////
// matrix routines
////////////////////////////////////////
// allocate memory for a double matrix
void SWRC_allocDoubleMatrix(doubleMatrix *C, int Nrow, int Ncol) {
  int i,j;
  if (C->x!=NULL) {
    SWRC_freeDoubleMatrix(C);
  }
  C->x=(double**)calloc(Nrow,sizeof(double*));
  C->Nrow=Nrow;
  C->Ncol=Ncol;
  for (i=0;i<Nrow;i++) {
    C->x[i]=(double*)calloc(Ncol,sizeof(double));
    for (j=0;j<Ncol;j++) C->x[i][j]=0.0;
  }
}
void SWRC_printDoubleMatrix(doubleMatrix *C,char *format) {
  int i,j;
  for (i=0;i<C->Nrow;i++) {
    printf(" [ ");
    for (j=0;j<C->Ncol;j++) printf(format,C->x[i][j]);
    printf(" ]\n");
  }
}
void SWRC_printDoubleMatrixSquared(doubleMatrix *C,char *format) {
  int i,j;
  doubleMatrix S;
  S.x=NULL;
  SWRC_allocDoubleMatrix(&S,3,3);
  SWRC_copyDoubleMatrix(&S,C);
  SWRC_matMult_inplace(&S,C,-1);
  SWRC_printDoubleMatrix(&S,"%7.4lf");
  SWRC_freeDoubleMatrix(&S);
}
// Copy matrix A into B, freeing and overwriting whatever was previously in B.
void SWRC_copyDoubleMatrix( doubleMatrix *B,doubleMatrix *A) {
  int i,j;
  SWRC_freeDoubleMatrix(B);
  SWRC_allocDoubleMatrix(B,A->Nrow,A->Ncol);
  for (i=0;i<A->Nrow;i++) {
    for (j=0;j<A->Ncol;j++) B->x[i][j]=A->x[i][j];
  }
}
// Computes C=A*B and copy it back into A (inplace).
// if flag>0 overwrite B
// if flag<0 overwrite A
void SWRC_matMult_inplace(doubleMatrix *A, doubleMatrix *B, int flag) {
  doubleMatrix C;
  C.x=NULL;
  int i,j,k;
  if (A->Ncol!=B->Nrow) {
    printf("Incompatible matrix dimensions A: %dx%d, B:%dx%d in function SWRC_matMult\n",A->Nrow,A->Ncol,B->Nrow,B->Ncol);
    exit(-1);
  }
  SWRC_allocDoubleMatrix(&C,A->Nrow,B->Ncol);
  for (i=0;i<A->Nrow;i++) {
    for (j=0;j<B->Ncol;j++) {
      for (k=0;k<A->Ncol;k++) C.x[i][j]+=A->x[i][k]*B->x[k][j];
    }
  }
  // printf("-------------In function SWRC_matMult_inplace\n");
  // printf("A=\n");SWRC_printDoubleMatrix(A,"%7.3lf");
  // printf("B=\n");SWRC_printDoubleMatrix(B,"%7.3lf");
  // printf("C=\n");SWRC_printDoubleMatrix(&C,"%7.3lf");
  // printf("------------\n");
  if (flag<0)    SWRC_copyDoubleMatrix(A,&C);
  else if(flag>0)SWRC_copyDoubleMatrix(B,&C);
  SWRC_freeDoubleMatrix(&C);
}
void SWRC_matAdd_inplace(doubleMatrix *A, doubleMatrix *B) {
  int i,j;
  for (i=0;i<A->Ncol;i++) for (j=0;j<A->Nrow;j++) 
			    A->x[i][j]+=B->x[i][j];
}

// Multiply matrix A by a constant.
void SWRC_matMultConst_inplace(doubleMatrix *A, double B) {
  int i,j;
  for (i=0;i<A->Nrow;i++) {
    for (j=0;j<A->Ncol;j++) A->x[i][j]*=B;
  }
}
void SWRC_addIdent_inplace(doubleMatrix *A, double b) {
  int i;
  for (i=0;i<A->Nrow;i++) A->x[i][i]+=b;
}
void SWRC_matTranspose_inplace(doubleMatrix *A) {
  doubleMatrix AT;
  AT.x=NULL;
  int i,j;
  SWRC_allocDoubleMatrix(&AT,A->Ncol,A->Nrow);
  for (i=0;i<A->Nrow;i++) {
    for (j=0;j<A->Ncol;j++) AT.x[j][i]=A->x[i][j];
  }
  SWRC_copyDoubleMatrix(A,&AT);
  SWRC_freeDoubleMatrix(&AT);
}
void SWRC_normalizeCols_inplace(doubleMatrix *A) {
  int i,j;
  double a;
  for (i=0;i<A->Ncol;i++) {
    a = A->x[i][i];
    for (j=0;j<A->Nrow;j++) {
      A->x[j][i]/=a;
    }
  }
}
// diagonalize a correlation matrix. Correlation matrix has the form:
// A = [ 1 c1 c2 ]
//     [ c1 1 c1 ]
//     [ c2 c1 1 ]
// so only c1 and c2 need to be specified.
// V is a 3x3 matrix holding the eigenvectors of A in the columns
// L is a 3x3 diagonal matrix holding the eigenvalues of A along the diagonal.
void SWRC_diagonalizeCorrMatrix(double c1, double c2, doubleMatrix *V, doubleMatrix *L) {
  int i,j;
  double c3,c4,c5;
  // compute some needed intermediate variables.
  c3 = sqrt(8*c1*c1+c2*c2);
  c4 = sqrt((c3+c2)*(c3+c2)+8*c1*c1);
  c5 = sqrt((c3-c2)*(c3-c2)+8*c1*c1);
  printf("c3=%lf, c4=%lf, c5=%lf\n",c3,c4,c5);
  // zero out the L matrix
  for (i=0;i<3;i++) for (j=0;j<3;j++) {
      L->x[i][j]=0.0;
    }
  // fill the diagonal L matrix.
  L->x[0][0]=-(c3-c2-2)/2;
  L->x[1][1]=(c3+c2+2)/2;
  L->x[2][2]=1-c2;
  // fill out the V matrix
  V->x[0][0] = 2*c1/c4;       V->x[0][1] = 2*c1/c5;    V->x[0][2] = 1/sqrt(2);
  V->x[1][0] = (-c3-c2)/c4; V->x[1][1] = (c3-c2)/c5;
  V->x[2][0] = 2*c1/c4;       V->x[2][1] = 2*c1/c5;    V->x[2][2] = -1/sqrt(2);
}
void SWRC_ludcmp(double **A, int n, int *indx, float *d)
/*Rewritten to be 0 offset instead of unity offset. Given a matrix a[0..n-1][0..n-1], 
this routine replaces it by the LU decomposition of a rowwise
permutation of itself. a and n are input. a is output, arranged as in equation (2.3.14) above;
indx[0..n-1] is an output vector that records the row permutation elected by the partial
pivoting; d is output as \pm 1 depending on whether the number of row interchanges was even
or odd, respectively. This routine is used in combination with SWRC_lubksb to solve linear equations
or invert a matrix.*/
{
  int i,imax,j,k;
  double big,dum,sum,temp;
  double *vv; //vv stores the implicit scaling of each row.
  double tiny_t;
  tiny_t=1e-20;
  vv=(double *) malloc(n * sizeof(double));
  
  *d=1.0; //No row interchanges yet.
  for (i=0;i<n;i++) { //Loop over rows to get the implicit scaling information.
    big=0.0; 
    for (j=0;j<n;j++)
      if ((temp=fabs(A[i][j])) > big) big=temp;
    if (big == 0.0) printf("Singular matrix in routine SWRC_ludcmp\n");
    //No nonzero largest element.
    vv[i]=1.0/big; //Save the scaling.
  }
  
  for (j=0;j<n;j++) { //This is the loop over columns of Crout's method.
    for (i=0;i<j;i++) { //This is equation (2.3.12) except for i = j.
      sum=A[i][j];
      for (k=0;k<i;k++) sum -= A[i][k]*A[k][j];
      A[i][j]=sum;
    }
    big=0.0; //Initialize for the search for largest pivot element.
    for (i=j;i<n;i++) { //This is i = j of equation (2.3.12) and i = j+1 : ::N
      sum=A[i][j]; //of equation (2.3.13).
      for (k=0;k<j;k++)
	sum -= A[i][k]*A[k][j];
      A[i][j]=sum;
      if ( (dum=vv[i]*fabs(sum)) >= big) {
	//Is the figure of merit for the pivot better than the best so far?
	big=dum;
	imax=i;
      }
    }
    if (j != imax) { //Do we need to interchange rows?
      for (k=0;k<n;k++) { //Yes, do so...
	dum=A[imax][k];
	A[imax][k]=A[j][k];
	A[j][k]=dum;
      }
      *d = -(*d); //...and change the parity of d.
      vv[imax]=vv[j]; //Also interchange the scale factor.
    }
    indx[j]=imax;
    if (A[j][j] == 0.0) A[j][j]=(float)(tiny_t);
    //If the pivot element is zero the matrix is singular (at least to the precision of the
    //algorithm). For some applications on singular matrices, it is desirable to substitute	TINY for zero.
    if (j != n-1) { //Now, finally, divide by the pivot element.
      dum=1.0/(A[j][j]);
      for (i=j+1;i<n;i++) A[i][j] *= dum;
    }
  } //Go back for the next column in the reduction.
  //free_vector(vv,1,n);	
  free(vv);
}
void SWRC_LUDcmpDoubleMatrix(doubleMatrix *A, int *indx) {
  float d=0;
  // printf("In function SWRC_LUDcmpDoubleMatrix\n");
  // printf("before SWRC_ludcmp\n");
  // SWRC_printDoubleMatrix(A,"%6.2lf");
  SWRC_ludcmp(A->x,A->Nrow,indx,&d);
  // printf("after SWRC_ludcmp\n");
  // SWRC_printDoubleMatrix(A,"%6.2lf");
}
void SWRC_lubksb(double **A, int n, int *indx, double *b)
/*Solves the set of n linear equations A.X = B. Here a[0..n-1][0..n-1] is input, not as the matrix
  A but rather as its LU decomposition, determined by the routine SWRC_ludcmp. indx[0..n-1] is input
  as the permutation vector returned by SWRC_ludcmp. b[0..n-1] is input as the right-hand side vector
  B, and returns with the solution vector X. a, n, and indx are not modified by this routine
  and can be left in place for successive calls with different right-hand sides b. This routine takes
  into account the possibility that b will begin with many zero elements, so it is efficient for use
  in matrix inversion.*/
{
  int i,ii=-1,ip,j;
  float sum;
  for (i=0;i<n;i++) { //When ii is set to a positive value, it will become the
    //index of the first nonvanishing element of b. We now
    //do the forward substitution, equation (2.3.6). The
    //only new wrinkle is to unscramble the permutation
    //as we go.
    ip=indx[i];
    sum=b[ip];
    b[ip]=b[i];
    if (ii!=-1)
      for (j=ii;j<i;j++) sum -= A[i][j]*b[j];
    else if (sum) ii=i; //A nonzero element was encountered, so from now on we
    b[i]=sum;	//will have to do the sums in the loop above.
  }
  for (i=n-1;i>=0;i--) { //Now we do the backsubstitution, equation (2.3.7).
    sum=b[i];
    for (j=i+1;j<n;j++) sum -= A[i][j]*b[j];
    b[i]=sum/A[i][i]; //Store a component of the solution vector X.
  } //All done!
}
void SWRC_LUBksbDoubleMatrix(doubleMatrix *A, doubleMatrix *b, int *indx) {
  // printf("In function SWRC_LUBksbDoubleMatrix\n");
  // printf("before SWRC_lubksb\n");
  // SWRC_printDoubleMatrix(b," %6.2lf");
  SWRC_lubksb(A->x, A->Nrow, indx,b->x[0]);
  // printf("after SWRC_lubksb\n");
  // SWRC_printDoubleMatrix(b," %6.2lf");
}
// pack a doubleMatrix to the uint8_t config file
int SWRC_packDoubleMatrixToUint8(doubleMatrix *A, uint8_vector *cfgFile) {
  int i;
  if (A->x!=NULL) {
    SWRC_packToUint8((uint8_t*)&A->Nrow,1,sizeof(int),cfgFile);
    SWRC_packToUint8((uint8_t*)&A->Ncol,1,sizeof(int),cfgFile);
    for (i=0;i<A->Nrow;i++) 
      SWRC_packToUint8((uint8_t*)A->x[i],A->Ncol,sizeof(double),cfgFile);
    return(A->Nrow*A->Ncol*sizeof(double));
  } else {
    i=0; // pack zeros for the size of the matrix
    SWRC_packToUint8((uint8_t*)&i,1,sizeof(int),cfgFile);
    SWRC_packToUint8((uint8_t*)&i,1,sizeof(int),cfgFile);
    return(0);
  }
}
int SWRC_unpackDoubleMatrixFromUint8(doubleMatrix *A, uint8_vector *cfgFile) {
  int i;
  SWRC_freeDoubleMatrix(A);
  SWRC_unpackFromUint8((uint8_t*)&A->Nrow,1,sizeof(int),cfgFile);
  SWRC_unpackFromUint8((uint8_t*)&A->Ncol,1,sizeof(int),cfgFile);
  A->x=(double**)realloc(A->x,A->Nrow*sizeof(double*));
  for (i=0;i<A->Nrow;i++) {
    A->x[i]=(double*)calloc(A->Ncol,sizeof(double));
    SWRC_unpackFromUint8((uint8_t*)A->x[i],A->Ncol,sizeof(double),cfgFile);
  }
}
void SWRC_freeDoubleMatrix(doubleMatrix *C) {
  int i;
  if (C->x!=NULL) {
    for (i=0;i<C->Nrow;i++) free(C->x[i]);
    free(C->x);
    C->x=NULL;
  }
  C->Nrow=0;
  C->Ncol=0;
}

/////////////////////////////////////////////////
// functions for handling .out, .bit files etc...
/////////////////////////////////////////////////
// Read an out file from the basename (with .out appended)
// and store it in the signal struct. 
void SWRC_readOutFile(char *basename, char *dir, signalStruct *signal) {
  char *filename; // The filename to be read
  FILE *f;        // The file handle to open the filename
  double *x;      // A pointer to the waveform stream in signal being written to.
  int N;          // length of the bit stream.
  int i;
  if (dir[0]=='\0') asprintf(&filename,"%s.out",basename);
  else asprintf(&filename,"%s/%s.out",dir,basename);  
  printf("Reading .out file:%s\n",filename);
  if ((f=fopen(filename,"r"))!=NULL) {
    fscanf(f,"%d %d",&N,&i); printf("N=%d\n",N);
    // allocate memory for N uint8_t's
    x = (double*)incrementByOneSignal(signal,N,6,filename); // 6 is type double.
    for (i=0;i<N;i++) {
      fscanf(f,"%lf",&x[i]);
    }
    fclose(f);
  } else printf("Unable to open %s for reading\n",filename);
  
  free(filename);
}
void SWRC_readSOutFile(char *basename, char *dir, signalStruct *signal) {
  char *filename; // The filename to be read
  FILE *f;        // The file handle to open the filename
  double *x;      // A pointer to the waveform stream in signal being written to.
  int N;          // length of the bit stream.
  int i;
  if (dir[0]=='\0') asprintf(&filename,"%s.sout",basename);
  else asprintf(&filename,"%s/%s.sout",dir,basename);  
  printf("Reading .out file:%s\n",filename);
  if ((f=fopen(filename,"r"))!=NULL) {
    fscanf(f,"%d %d",&N,&i); printf("N=%d\n",N);
    // allocate memory for N uint8_t's
    x = (double*)incrementByOneSignal(signal,N,6,filename); // 6 is type double.
    for (i=0;i<N;i++) {
      fscanf(f,"%lf",&x[i]);
    }
    fclose(f);
  } else printf("Unable to open %s for reading\n",filename);
  
  free(filename);
}
// Read a bit file from the basename (with .bit appended)
// and store it in the signal struct. 
void SWRC_readBitFile(char *basename, char *dir, signalStruct *signal) {
  char *filename; // The filename to be read
  FILE *f;        // The file handle to open the filename
  uint8_t *a;     // A pointer to the bit stream in signal being written to.
  int N;          // length of the bit stream.
  int i;
  int t;
  if (dir[0]=='\0') asprintf(&filename,"%s.bit",basename);
  else asprintf(&filename,"%s/%s.bit",dir,basename);  
  printf("Reading .bit file: %s\n",filename);
  if ((f=fopen(filename,"r"))!=NULL) {
    fscanf(f,"%d %d",&N,&t); printf("N=%d\n",N);
    // allocate memory for N uint8_t's
    a = incrementByOneSignal(signal,N,0,filename);
    for (i=0;i<N;i++) {
      fscanf(f,"%d",&t);
      signal->x[signal->N_N-1][i]=(t==1?1:0);
    }
    fclose(f);
  } else printf("Unable to open %s for reading\n",filename);
  
  free(filename);
}
void SWRC_saveSoutFile(char *basename, char *dir, signalStruct *signal,int sigIndex,int delay) {
  char *filename; // The filename to be read
  FILE *f;        // The file handle to open the filename
  double *s;      // A pointer to the bit stream in signal being written to.
  int N;          // length of the bit stream.
  int i;
  N = signal->N[sigIndex];
  s = (double*)signal->x[sigIndex];

  if (dir[0]=='\0') asprintf(&filename,"%s.sout",basename);
  else asprintf(&filename,"%s/%s.sout",dir,basename);  

  printf("Writing .sout file: %s\n",filename);
  if ((f=fopen(filename,"w"))!=NULL) {
    fprintf(f,"%d 1\n",N-delay);
    for (i=delay;i<N;i++) {
      fprintf(f,"%lf\n",s[i]);
    }
    fclose(f);
  } else printf("Unable to open %s for writing\n",filename);
  free(filename);
}
// Plot the .out and .sout files by creating an octave scrpit.
void SWRC_octavePlotOutSout(char *basename) {
  char *Mfilename; // The filename to be written
  FILE *f;
  printf("In function SWRC_octavePlotOutSout\n");
  asprintf(&Mfilename,"%s.m","plotOutSout");
  if ((f=fopen(Mfilename,"w"))!=NULL) {
    fprintf(f,"dlmread('%s.out'); out=ans(2:end,1); # Read the .out file\n",basename);
    fprintf(f,"dlmread('%s.sout');sout=ans(2:end,1);# Read the .sout file\n",basename);
    fprintf(f,"plot(out,'b-');\n");
    fprintf(f,"hold on;\n");
    fprintf(f,"plot(sout,'r-');\n");
    fprintf(f,"\n");
    fclose(f);
  }
  free(Mfilename);
}
void SWRC_saveDetBitFile(char *basename, char *dir, signalStruct *signal,int sigIndex,int delay) {
  char *filename; // The filename to be read
  FILE *f;        // The file handle to open the filename
  uint8_t *s;     // A pointer to the bit stream in signal being written to.
  int N;          // length of the bit stream.
  int i;
  N = signal->N[sigIndex];
  s = (uint8_t*)signal->x[sigIndex];

  if (dir[0]=='\0') asprintf(&filename,"%s.detBit",basename);
  else asprintf(&filename,"%s/%s.detBit",dir,basename);  

  printf("Writing .detBit file: %s\n",filename);
  if ((f=fopen(filename,"w"))!=NULL) {
    fprintf(f,"%d 1\n",N-delay);
    for (i=delay;i<N;i++) {
      fprintf(f,"%2d\n",(s[i]==1?1:-1));
    }
    fclose(f);
  } else printf("Unable to open %s for writing\n",filename);
  free(filename);
}
// Compute an SNR and save it to basename.snr
// rIndex is the index of the signal containing the r signal (noisy)
// sIndex is the index of the signal containing the s signal (noise-free).
// delay is the delay between r signal and s signal.
void SWRC_saveSNRFile(char *basename, char *dir, signalStruct *signal,int rIndex, int sIndex,int delay) {
  char *filename; // The filename to be read
  FILE *f;        // The file handle to open the filename
  double *s;      // pointer to the s signal
  double *r;      // pointer to the r signal
  double S;       // signal power
  double N;       // noise power.
  double SNR;
  int Ns;         // length of the s signal
  int Nr;         // length of the r signal
  int i;
  Ns = signal->N[sIndex];
  s  = (double*)signal->x[sIndex];
  Nr = signal->N[rIndex];
  r  = (double*)signal->x[rIndex];
  printf("delay=%d, Ns=%d, Nr=%d\n",delay,Ns,Nr);
  for (S=0.0,N=0.0,i=delay;i<Ns && i-delay<Nr;i++) {
    S+=s[i]*s[i];
    N+=(s[i]-r[i-delay])*(s[i]-r[i-delay]);
  }
  SNR = 10*log10(S/N);
  printf("S=%lf, N=%lf, S/N=%lf, SNR=%lf\n",S,N,S/N,SNR);
  if (dir[0]=='\0') asprintf(&filename,"%s.snr",basename);
  else asprintf(&filename,"%s/%s.snr",dir,basename);  
  printf("Writing .snr file: %s\n",filename);
  if ((f=fopen(filename,"w"))!=NULL) {
    fprintf(f,"%lf\n",SNR);
    fclose(f);
  } else printf("Unable to open %s for writing\n",filename);
  free(filename);
}
void SWRC_saveHFile(char *basename, char *dir,double *h, long unsigned int Nh, int hInd) {
  char *filename; // The filename to be read
  FILE *f;        // The file handle to open the filename
  int i;
  if (dir[0]=='\0') asprintf(&filename,"%s.h%d",basename,hInd);
  else asprintf(&filename,"%s/%s.h%d",dir,basename,hInd);

  printf("Writing .h%d file: %s\n",hInd,filename);
  if ((f=fopen(filename,"w"))!=NULL) {
    fprintf(f,"%lu 1\n",Nh);
    for (i=0;i<Nh;i++) fprintf(f,"%lf\n",h[i]);
    fclose(f);
  } else printf("Unable to open %s for writing\n",filename);
  free(filename);
}
void SWRC_loadHFile(char *filename, char *dir, double **h, long unsigned int *Nh) {
  int i;
  printf("In function loadH_SWRC_2L3T3R, reading file:%s in directory %s\n",filename,dir);
  FILE *f;        // The file handle to open the filename
  char cwd[500];
  if (getcwd(cwd, sizeof(cwd)) != NULL) { // get the current working directory
    if (chdir(dir)!=-1) {
      if ((f=fopen(filename,"r"))!=NULL) {
	fscanf(f,"%lu %d",Nh,&i); printf("Nh=%lu\n",*Nh);
	// allocate memory for N uint8_t's
	*h = (double*)realloc(*h,*Nh*sizeof(double));
	for (i=0;i<*Nh;i++) {
	  fscanf(f,"%lf",&h[0][i]);
	  printf("%2d %lf\n",i,h[0][i]);
	}
	fclose(f);
      } else printf("Unable to open %s for reading\n",filename);  
      chdir(cwd); // return to the current working dir before exiting.
    } else printf("Unable to change to dir %s\n",dir);
  }
}
/////////////////////////////////////////////////
// mkchdir and unmkchdir functions
/////////////////////////////////////////////////
// save the current working directory in *cwd (allocating memory)
// check for the existence of dirName in the cwd. If it exists
// just cd to it. If it doesn't exist mkdir(dirName) and then cd to it.
// the counterpart function unmkchdir undoes the effects for this function
// ssd is a flag, it stands for: save subdir 
// if =0, then it doesn't change directory, all files are saved in current directory
// if =1, then it changes 1 directory deep.
// if =2, then it changes 2 directories deep.
int SWRC_mkchdir_obsolete(char *dirName, int dirNum, char *ext, char **cwd, uint8_t ssd) {
  char *dirName2;
  //printf("In function mkchdir, dirName=%s\n",dirName);
  *cwd=getcwd(NULL,0); // this will allocate sufficient memory to get the cwd. free it later with unmkchdir
  if (ssd>0) {
    mkdir(dirName,0700);
    chdir(dirName);
  }
  if (ssd>1) {
    SWRC_getSubDirName2(&dirName2,dirName,dirNum);
    mkdir(dirName2,0700);
    chdir(dirName2);
    free(dirName2);
  }
}
// The dirname is stored  in the first N chars of *dirname.
// replaced by the function below when I changed from baseName/N_basename to basename/basename2 paradigm
int SWRC_mkchdir_obsolete2(char *baseName, int N, char *subDirName, char **cwd, uint8_t ssd) {
  char dirName2[N+1]; // memory allocated for the root dirname, taken as the first N characters of dirname
  int i;
  for (i=0;i<N;i++) dirName2[i]=baseName[i];dirName2[N]='\0';
  *cwd=getcwd(NULL,0); // this will allocate sufficient memory to get the cwd. free it later with unmkchdir
  if (ssd>0 && baseName!=NULL && N>0) {
    mkdir(dirName2,0700);
    chdir(dirName2);
    if (ssd>1 && subDirName!=NULL && *subDirName!='\0') {
      mkdir(subDirName,0700);
      chdir(subDirName);
    }
  }
}
int SWRC_mkchdir(char *baseName, char *subDirName, char **cwd, uint8_t ssd) {
  int i;
  *cwd=getcwd(NULL,0); // this will allocate sufficient memory to get the cwd. free it later with unmkchdir
  if (ssd>0 && baseName!=NULL && *baseName!='\0') {
    mkdir(baseName,0700);
    chdir(baseName);
    if (ssd>1 && subDirName!=NULL && *subDirName!='\0') {
      mkdir(subDirName,0700);
      chdir(subDirName);
    }
  }
}
//void SWRC_getSubDirName2(char **dirName2, char *dirName, int dirNum, char *ext) {
void SWRC_getSubDirName2(char **dirName2, char *dirName, int dirNum) {
  asprintf(dirName2,"%s_%04d",dirName,dirNum);
}
// perform the inverse of mkchdir, chdir to cwd and 
// free the memory allocated for it.
void SWRC_unmkchdir(char **cwd) {
  //printf("In function unmkchdir, cwd=%s\n",*cwd);
  chdir(*cwd);
  free(*cwd); // this memory was allocated in mkchdir above.
}
// given a string in filename of the form dirname/basename_num, 
// extract dirname, basename and num into the respective variables
// and return 1
// if it cannot find basename and num, returns 0.
// This function is obsoleted by SWRC_loadcfgfile
int SWRC_getBasenameNum(char *filename, char **basename, char **dirname, int *num) {
  int i;
  int N=strlen(filename);
  int lastSlash=-1;
  for (i=0;i<N;i++) if (filename[i]=='/') lastSlash=i;
  if (lastSlash>0) {
    *dirname=(char*)realloc(*dirname,(lastSlash+1)*sizeof(char));dirname[0][lastSlash]='\0';
    strncpy(*dirname,filename,lastSlash);
  }
  // printf("N=%d\n",N);
  // printf("%c %c %c %c %c\n",filename[N-5],filename[N-4],filename[N-3],filename[N-2],filename[N-1]);
  // check for a _0012 num at the end of filename
  if (filename[N-5]=='_' && filename[N-4]>='0' && filename[N-4]<='9' && filename[N-3]>='0' && filename[N-3]<='9' && filename[N-2]>='0' && filename[N-2]<='9' && filename[N-1]>='0' && filename[N-1]<='9') {
    *num = (filename[N-4]-'0')*1000+(filename[N-3]-'0')*100+(filename[N-2]-'0')*10+(filename[N-1]-'0');
    *basename=(char*)realloc(*basename,(N-lastSlash-5)*sizeof(char));
    strncpy(*basename,&filename[lastSlash+1],N-lastSlash-5);
    basename[0][N-lastSlash-6]='\0';
    return(1);
  } else {
    return(0);
  }
}
// given a basename as a directory, go inside this directory. Search among all the files 
// inside basename. The files should be of the form:
// basename_0000 basename_0001 etc...
// extract the number of the last basename subdirectory and return it.
int SWRC_getSubDirNum(char *basename) {
  struct dirent *de;
  DIR *dr;
  char *t; // temporary string pointer.
  int num=0,output=0;
  if ((dr=opendir(basename))!=NULL) {
    while((de=readdir(dr))!=NULL) {
      if (strncmp(basename,de->d_name,strlen(basename))==0) { // found a filename matching basename.
	if (sscanf(&de->d_name[strlen(basename)],"_%d",&num)==1) { // found a matching number in the string.
	  if (num>output)output=num;
	} else {
	  printf("Could not find a directory subnumber within %s\n",de->d_name);
	}
      }
    }
    closedir(dr);
  } else {
    printf("Could not open directory %s in function getCodeNum\n",basename);
  }
  return(output);
}

/////////////////////////////////////////////////
// loadQ functions for polar Code
/////////////////////////////////////////////////
// load the reliability sequence from a .mat file
void SWRC_loadQ(int **Q,int N,char *rsFilename)  {
  FILE *f;
  char c[500];
  int i,j,n;
  if ((f=fopen(rsFilename,"r"))!=NULL) {
    fgets(c,500,f); // Read/discard the first line 
    fgets(c,500,f); // Read/discard the first line 
    fgets(c,500,f); // Read/discard the first line 
    fgets(c,500,f); // Read/discard the fourth line 
    //fscanf(f,"# rows: %d\n",&N); // Read the number of rows in the matrix
    fgets(c,500,f); // Read/discard the fifth line 
    *Q=(int*)realloc(*Q,N*sizeof(int));
    // Read in the elements of reliability sequence equal or below polarEncoder->N
    for (i=0,j=0;j<N;i++) {
      fscanf(f,"%d\n",&n);
      if (n<N) {
	Q[0][j++]=n;
	printf("%3d %d\n",j-1,Q[0][j-1]);
      }
    }
    fclose(f);
  } else {
    printf("Unable to load file: %s\n",rsFilename);
    exit(-1);
  }
}
// This function also returns a reliability sequence, but does so from
// internally rather than loading from an external file.
void SWRC_getRS(int **Q, int N) {
  if (N>1024) {
    printf("Maximum reliabiliyt sequence size=1024. Aborting.\n");
    exit(-1);
  }
  int i,j;
  int rs[]={0,1,2,4,8,16,32,3,5,64,9,6,17,10,18,128,12,33,65,20,256,34,24,36,7,129,66,512,11,40,68,130,19,13,48,14,72,257,21,132,35,258,26,513,80,37,25,22,136,260,264,38,514,96,67,41,144,28,69,42,516,49,74,272,160,520,288,528,192,544,70,44,131,81,50,73,15,320,133,52,23,134,384,76,137,82,56,27,97,39,259,84,138,145,261,29,43,98,515,88,140,30,146,71,262,265,161,576,45,100,640,51,148,46,75,266,273,517,104,162,53,193,152,77,164,768,268,274,518,54,83,57,521,112,135,78,289,194,85,276,522,58,168,139,99,86,60,280,89,290,529,524,196,141,101,147,176,142,530,321,31,200,90,545,292,322,532,263,149,102,105,304,296,163,92,47,267,385,546,324,208,386,150,153,165,106,55,328,536,577,548,113,154,79,269,108,578,224,166,519,552,195,270,641,523,275,580,291,59,169,560,114,277,156,87,197,116,170,61,531,525,642,281,278,526,177,293,388,91,584,769,198,172,120,201,336,62,282,143,103,178,294,93,644,202,592,323,392,297,770,107,180,151,209,284,648,94,204,298,400,608,352,325,533,155,210,305,547,300,109,184,534,537,115,167,225,326,306,772,157,656,329,110,117,212,171,776,330,226,549,538,387,308,216,416,271,279,158,337,550,672,118,332,579,540,389,173,121,553,199,784,179,228,338,312,704,390,174,554,581,393,283,122,448,353,561,203,63,340,394,527,582,556,181,295,285,232,124,205,182,643,562,286,585,299,354,211,401,185,396,344,586,645,593,535,240,206,95,327,564,800,402,356,307,301,417,213,568,832,588,186,646,404,227,896,594,418,302,649,771,360,539,111,331,214,309,188,449,217,408,609,596,551,650,229,159,420,310,541,773,610,657,333,119,600,339,218,368,652,230,391,313,450,542,334,233,555,774,175,123,658,612,341,777,220,314,424,395,673,583,355,287,183,234,125,557,660,616,342,316,241,778,563,345,452,397,403,207,674,558,785,432,357,187,236,664,624,587,780,705,126,242,565,398,346,456,358,405,303,569,244,595,189,566,676,361,706,589,215,786,647,348,419,406,464,680,801,362,590,409,570,788,597,572,219,311,708,598,601,651,421,792,802,611,602,410,231,688,653,248,369,190,364,654,659,335,480,315,221,370,613,422,425,451,614,543,235,412,343,372,775,317,222,426,453,237,559,833,804,712,834,661,808,779,617,604,433,720,816,836,347,897,243,662,454,318,675,618,898,781,376,428,665,736,567,840,625,238,359,457,399,787,591,678,434,677,349,245,458,666,620,363,127,191,782,407,436,626,571,465,681,246,707,350,599,668,790,460,249,682,573,411,803,789,709,365,440,628,689,374,423,466,793,250,371,481,574,413,603,366,468,655,900,805,615,684,710,429,794,252,373,605,848,690,713,632,482,806,427,904,414,223,663,692,835,619,472,455,796,809,714,721,837,716,864,810,606,912,722,696,377,435,817,319,621,812,484,430,838,667,488,239,378,459,622,627,437,380,818,461,496,669,679,724,841,629,351,467,438,737,251,462,442,441,469,247,683,842,738,899,670,783,849,820,728,928,791,367,901,630,685,844,633,711,253,691,824,902,686,740,850,375,444,470,483,415,485,905,795,473,634,744,852,960,865,693,797,906,715,807,474,636,694,254,717,575,913,798,811,379,697,431,607,489,866,723,486,908,718,813,476,856,839,725,698,914,752,868,819,814,439,929,490,623,671,739,916,463,843,381,497,930,821,726,961,872,492,631,729,700,443,741,845,920,382,822,851,730,498,880,742,445,471,635,932,687,903,825,500,846,745,826,732,446,962,936,475,853,867,637,907,487,695,746,828,753,854,857,504,799,255,964,909,719,477,915,638,748,944,869,491,699,754,858,478,968,383,910,815,976,870,917,727,493,873,701,931,756,860,499,731,823,922,874,918,502,933,743,760,881,494,702,921,501,876,847,992,447,733,827,934,882,937,963,747,505,855,924,734,829,965,938,884,506,749,945,966,755,859,940,830,911,871,639,888,479,946,750,969,508,861,757,970,919,875,862,758,948,977,923,972,761,877,952,495,703,935,978,883,762,503,925,878,735,993,885,939,994,980,926,764,941,967,886,831,947,507,889,984,751,942,996,971,890,509,949,973,1000,892,950,863,759,1008,510,979,953,763,974,954,879,981,982,927,995,765,956,887,985,997,986,943,891,998,766,511,988,1001,951,1002,893,975,894,1009,955,1004,1010,957,983,958,987,1012,999,1016,767,989,1003,990,1005,959,1011,1013,895,1006,1014,1017,1018,991,1020,1007,1015,1019,1021,1022,1023};
  *Q=(int*)realloc(*Q,N*sizeof(int));
  for (i=0,j=0;j<N;i++) {
    if (rs[i]<N) {
      Q[0][j++]=rs[i];
      //printf("%3d %d\n",j-1,Q[0][j-1]);
    }
  }
}
// returns 1 if index corresponds to a frozen leaf
// returns 0 otherwise. 
// A leaf is frozen depending on the reliability sequence given in Q
// and for a given N and K.
// generalized version of polarNode2_isFrozen.
int SWRC_isFrozen(int index, int *Q, int N, int N_K) {
  int i;
  for (i=0;i<N_K;i++) if (index==Q[i]) {
      return(1); // leaf is frozen
    }
  return(0);     // leaf is not frozen
}

///////////////////////////////////////////////
// Everything from signals.c is put below here.
///////////////////////////////////////////////
// Initialize the fields in the module structure
// Set pointers to NULL (so they can be called with realloc)
// Initialize the parameters to sane start-up values.
// Function called each time structure is instantiated.
void initSignalStruct (signalStruct *signal) {
// Fields entered by the user
  signal->N_N                         = 0;
  signal->N                           = NULL;
  signal->x                           = NULL;
  signal->N_N_name                    = 0;
  signal->N_name                      = NULL;
  signal->name                        = NULL;
  signal->N_type                      = 0;
  signal->type                        = NULL;
}

// Prints the contents of the structure. 
// Used for determining the status of the simulation
// as well as for debugging.
void printSignalStruct (signalStruct *signal, char *name, int index, int pre) {
  int i,j;
  char *preString;
  preString=(char*)calloc((pre+1),sizeof(char));
  for (i=0;i<pre;i++) preString[i]=' '; preString[i]='\0';
  printf("%s---%d:%s--------\n",preString,index,name);
// Fields entered by the user
  printf("%s  ---Fields entered by the user\n",preString);
  printf("%s  long unsigned int    %s->N_N=%lu\n",preString,name,signal->N_N); // Print N_N
  if (signal->N_N!=0) { // Print *N
    printf("%s  long unsigned int*   %s->N=[",preString,name);
    for (i=0;i<(signal->N_N>100?100:signal->N_N);i++) printf("%lu ",signal->N[i]); printf("]\n");
  } else {
    printf("%s  long unsigned int*   %s->N=NULL\n",preString,name);
  }
  if (signal->N_N!=0) { // Print **x
    for (i=0;i<(signal->N_N>100?100:signal->N_N);i++) {
      if (signal->type[i]==0) printf("%s  uint8_t*             ",preString);
      if (signal->type[i]==1) printf("%s  char*                ",preString);
      if (signal->type[i]==2) printf("%s  int*                 ",preString);
      if (signal->type[i]==3) printf("%s  unsigned int*        ",preString);
      if (signal->type[i]==4) printf("%s  long unsigned int*   ",preString);
      if (signal->type[i]==5) printf("%s  float*               ",preString);
      if (signal->type[i]==6) printf("%s  double*              ",preString);
      if (signal->N[i]!=0) {
	printf("%s->x[%2d]=[",name,i);
	for (j=0;j<(signal->N[i]>150?150:signal->N[i]);j++) {
	  if (signal->type[i]==0)printf("%6"SCNu8" ",signal->x[i][j]); 
	  if (signal->type[i]==1)printf("%c",  *((char*)signal->x[i]+j)); 
	  if (signal->type[i]==2)printf("%6d ", *((int*)signal->x[i]+j));
	  if (signal->type[i]==3)printf("%6u ", *((unsigned int *)signal->x[i]+j)); 
	  if (signal->type[i]==4)printf("%6lu ",*((long unsigned int *)signal->x[i]+j)); 
	  if (signal->type[i]==5)printf("%6.3f ", *((float*)signal->x[i]+j)); 
	  if (signal->type[i]==6)printf("%6.3lf ",*((double*)signal->x[i]+j)); 
	} printf("]\n");
      } else {
	printf("%s->x[%2d]=NULL\n",name,i);
      }
    }
  } else {
    printf("%s  uint8_t**            signal->x=NULL\n",preString);
  }
  printf("%s  long unsigned int    %s->N_N_name=%lu\n",preString,name,signal->N_N_name); // Print N_N_name
  if (signal->N_N_name!=0) { // Print *N_name
    printf("%s  long unsigned int*   %s->N_name=[",preString,name);
    for (i=0;i<(signal->N_N_name>100?100:signal->N_N_name);i++) printf("%lu ",signal->N_name[i]); printf("]\n");
  } else {
    printf("%s  long unsigned int*   %s->N_name=NULL\n",preString,name);
  }
  if (signal->N_N_name!=0) { // Print **name
    for (i=0;i<(signal->N_N_name>100?100:signal->N_N_name);i++) {
      if (signal->N_name[i]!=0) {
	printf("%s  char**               %s->name[%d]=\"%s\"\n",preString,name,i,signal->name[i]);
      } else {
	printf("%s  %s->x[%d]=NULL\n",preString,name,i);
      }
    }
  } else {
    printf("%s  char**               signal->name=NULL\n",preString);
  }
  printf("%s  long unsigned int    %s->N_type=%lu\n",preString,name,signal->N_type); // Print N_type
  if (signal->N_type!=0) { // Print *type
    printf("%s  uint8_t*             %s->type=[",preString,name);
    for (i=0;i<(signal->N_type>100?100:signal->N_type);i++) printf("%"SCNu8" ",signal->type[i]); printf("]\n");
  } else {
    printf("%s  uint8_t*             %s->type=NULL\n",preString,name);
  }
  printf("%s---%d:%s--------\n",preString,index,name);
  free(preString);
}
// Given a type code, return a string indicating the type
char* getStringFromType(uint8_t type) {
  switch(type) {
  case 0: // uint8_t
    return("uint8_t");
  case 1: // char
    return("char");
  case 2: // int
    return("int");
  case 3: // unsigned int 
    return("unsigned int");
  case 4: // long unsigned int 
    return("long unsigned int");
  case 5: // float
    return("float");
  case 6: // double
    return("double");
    // Default type: uint8_t
  default:
    printf("Returning default unit size\n");
    return("uint8_t");
  }
}

void printAllSignals(signalStruct *signal ) {
  int i,j;
  int maxLen=0;
  char temp[400];
  char *c;
  int *in;
  unsigned int *ui;
  long unsigned int *lui;
  float *f;
  double *d;
  printf("signal->N_N=%lu\n",signal->N_N);
  // print the length of each signal
  for (i=0;i<signal->N_N;i++) {
    printf("%d signal->N[%d]=%lu, signal->type[%d]=%d(%s), signal->name[%d]=%s\n",i,i,signal->N[i],i,signal->type[i],getStringFromType(signal->type[i]),i,signal->name[i]);
    if (signal->N[i]>maxLen) maxLen=signal->N[i];
  }
  // print the headers
  printf("    ");
  for (j=0;j<signal->N_N;j++) {
    sprintf(temp,"signal[%d]",j);
    printf("%10s ",temp);
  } printf("\n");
  // print the body
  for (i=0;i<maxLen;i++) {
   printf("%3d ",i);
   for (j=0;j<signal->N_N;j++) {
     c  =(char*)signal->x[j];
     in =(int*)signal->x[j];
     ui =(unsigned int*)signal->x[j];
     lui=(long unsigned int*)signal->x[j];
     f  =(float*)signal->x[j];
     d  =(double*)signal->x[j];
     if (i<signal->N[j]) {
       if      (signal->type[j]==0) printf("%10d ",signal->x[j][i]);
       else if (signal->type[j]==1) printf("%10c ",c[i]);
       else if (signal->type[j]==2) printf("%10d ",in[i]);
       else if (signal->type[j]==3) printf("%10u ",ui[i]);
       else if (signal->type[j]==4) printf("%10lu ",lui[i]);
       else if (signal->type[j]==5) printf("%10f ",f[i]);
       else if (signal->type[j]==6) printf("%10lf ",d[i]);
     }
     else printf("%10s ","");
   }
   printf("\n");
  }
}

void printSignalRange(signalStruct *signal,int startIndex,int stopIndex) {
  int i,j;
  int maxLen=0;
  char temp[400];
  char *c;
  int *in;
  unsigned int *ui;
  long unsigned int *lui;
  float *f;
  double *d;
  printf("signal->N_N=%lu\n",signal->N_N);
  if (startIndex>=0 && stopIndex>=0 && startIndex<=signal->N_N && stopIndex<=signal->N_N) {
    // print the length of each signal
    for (i=startIndex;i<stopIndex;i++) {
      printf("%d signal->N[%d]=%lu, signal->type[%d]=%d, signal->name[%d]=%s\n",i,i,signal->N[i],i,signal->type[i],i,signal->name[i]);
      if (signal->N[i]>maxLen) maxLen=signal->N[i];
    }
    // print the headers
    printf("    ");
    for (j=startIndex;j<stopIndex;j++) {
      sprintf(temp,"signal[%d]",j);
      printf("%10s ",temp);
    } printf("\n");
    // print the body
    for (i=0;i<maxLen;i++) {
      printf("%3d ",i);
      for (j=startIndex;j<stopIndex;j++) {
	c  =(char*)signal->x[j];
	in =(int*)signal->x[j];
	ui =(unsigned int*)signal->x[j];
	lui=(long unsigned int*)signal->x[j];
	f  =(float*)signal->x[j];
	d  =(double*)signal->x[j];
	if (i<signal->N[j]) {
	  if      (signal->type[j]==0) printf("%10d ",signal->x[j][i]);
	  else if (signal->type[j]==1) printf("%10c ",c[i]);
	  else if (signal->type[j]==2) printf("%10d ",in[i]);
	  else if (signal->type[j]==3) printf("%10u ",ui[i]);
	  else if (signal->type[j]==4) printf("%10lu ",lui[i]);
	  else if (signal->type[j]==5) printf("%10f ",f[i]);
	  else if (signal->type[j]==6) printf("%10lf ",d[i]);
	}
	else printf("%10s ","");
      }
      printf("\n");
    }
  }
}

int getMaxLUI(long unsigned int *x, int N) {
  int i;
  long unsigned int max=0;
  for (i=0;i<N;i++) {
    if (x[i]>max) max=x[i];
  }
  return(max);
}
// Plot function generates any plots associated with the 
// structure
void writeTxtFile(signalStruct *signal,const char *filename) {
  int i,j;
  char *plotFilename;
  FILE *f;
  long unsigned int maxN=getMaxLUI(signal->N,signal->N_N);
  int *I;
  double *D;
  float *F;
  asprintf(&plotFilename,"%s.txt",filename);
  //plotFilename=(char*)calloc(strlen(filename)+5,sizeof(char));
  //strcpy(plotFilename,filename); strcat(plotFilename,".txt");
  if ((f=fopen(plotFilename,"w"))==NULL) printf("Unable to open %s for writing\n",plotFilename);

  // print the headers
  fprintf(f,"# ");
  for (i=0;i<signal->N_N;i++) fprintf(f,"%36s",signal->name[i]);
  fprintf(f,"\n");
  // print the body of the signals
  for (i=0;i<maxN;i++) {
    for (j=0;j<signal->N_N;j++) {
      if (i<signal->N[j]) {
	if (signal->type[j]==0) fprintf(f,"%36"SCNu8" ",signal->x[j][i]);
	if (signal->type[j]==1) fprintf(f,"%36s ","");
	if (signal->type[j]==2) fprintf(f,"%36d ",*((int*)signal->x[j]+i));
	if (signal->type[j]==3) fprintf(f,"%36u ",*((unsigned int*)signal->x[j]+i));
	if (signal->type[j]==4) fprintf(f,"%36lu ",*((long unsigned int*)signal->x[j]+i));
	if (signal->type[j]==5) fprintf(f,"%36f ",*((float*)signal->x[j]+i));
	if (signal->type[j]==6) fprintf(f,"%36lf ",*((double*)signal->x[j]+i));
      } else fprintf(f,"%36s ","");
    } fprintf(f,"\n");
  }
  
  // close file pointer
  if (fclose(f)!=0) printf("Problem closing file %s\n",plotFilename);
  free(plotFilename);
}
void writeGPFile(signalStruct *signal,const char *filename) {

}
void plotGPFile(const char *filename) {

}
void plotSignalStruct (signalStruct *signal, char *filename) {
  printf("In plotSignalStruct\n");
  writeTxtFile(signal,filename);
  writeGPFile(signal,filename);
  plotGPFile(filename);
}
// Return the size of the different types
int sizeofType(int type){
  if (type==0) return(sizeof(uint8_t));
  if (type==1) return(sizeof(char));
  if (type==2) return(sizeof(int));
  if (type==3) return(sizeof(unsigned int));
  if (type==4) return(sizeof(long unsigned int));
  if (type==5) return(sizeof(float));
  if (type==6) return(sizeof(double));
}
// All the data from all the modules is packed into an
// array of uint8_vectors for saving. One uint8_vector per module. 
// Each uint8_vector contains a stringified version of the
// data in the struct. uint8_vectors are then written to and 
// read from disk by the saveuint8_vector and loaduint8_vector 
// functions. This function packs struct data into a uint_8_vector
void SWRC_packSignalStruct (signalStruct *signal, uint8_vector *cfgFile) {
  int i;
 //Fields entered by the user
  // N_N
  SWRC_packToUint8((uint8_t*)&signal->N_N,1,sizeof(long unsigned int),cfgFile);
  // *N
  SWRC_packToUint8((uint8_t*)signal->N,signal->N_N,sizeof(long unsigned int),cfgFile);
  // N_type
  SWRC_packToUint8((uint8_t*)&signal->N_type,1,sizeof(long unsigned int),cfgFile);
  // *type
  SWRC_packToUint8((uint8_t*)signal->type,signal->N_type,sizeof(uint8_t),cfgFile);
  // **x
  for (i=0;i<signal->N_N;i++) 
    SWRC_packToUint8((uint8_t*)signal->x[i],signal->N[i],sizeofType(signal->type[i]),cfgFile);
  // N_N_name
  SWRC_packToUint8((uint8_t*)&signal->N_N_name,1,sizeof(long unsigned int),cfgFile);
  // *N_name
  SWRC_packToUint8((uint8_t*)signal->N_name,signal->N_N_name,sizeof(long unsigned int),cfgFile);
  // **name
  for (i=0;i<signal->N_N_name;i++) 
    SWRC_packToUint8((uint8_t*)signal->name[i],signal->N_name[i],sizeof(char),cfgFile);
}

// After loading the data back from a .cfg file, the data is unpacked
// back into the struct with this function.
void SWRC_unpackSignalStruct (signalStruct *signal, uint8_vector *cfgFile) {
  int i;
  freeSignalStruct(signal);
// Fields entered by the user
  // N_N
  SWRC_unpackFromUint8((uint8_t*)&signal->N_N,1,sizeof(long unsigned int),cfgFile);
  //printf("In function unpackSignalStruct, signal->N_N=%lu\n",signal->N_N);
  // *N
  if (signal->N_N!=0) {
    signal->N = (long unsigned int*)calloc(signal->N_N,sizeof(long unsigned int));
    SWRC_unpackFromUint8((uint8_t*)signal->N,signal->N_N,sizeof(long unsigned int),cfgFile);
  }
  // N_type
  SWRC_unpackFromUint8((uint8_t*)&signal->N_type,1,sizeof(long unsigned int),cfgFile);
  // *type
  if (signal->N_type!=0) {
    signal->type = (uint8_t*)calloc(signal->N_type,sizeof(uint8_t));
    SWRC_unpackFromUint8((uint8_t*)signal->type,signal->N_type,sizeof(uint8_t),cfgFile);
  }
  // **x
    if (signal->N_N!=0) {
      signal->x=(uint8_t**) calloc(signal->N_N,sizeof(uint8_t*));
      for (i=0;i<signal->N_N;i++) {
        signal->x[i]=(uint8_t*) calloc(signal->N[i],sizeofType(signal->type[i]));
        SWRC_unpackFromUint8((uint8_t*)signal->x[i],signal->N[i],sizeofType(signal->type[i]),cfgFile);
      }
    }
  // N_N_name
  SWRC_unpackFromUint8((uint8_t*)&signal->N_N_name,1,sizeof(long unsigned int),cfgFile);
  // *N_name
  if (signal->N_N_name!=0) {
    signal->N_name = (long unsigned int*)calloc(signal->N_N_name,sizeof(long unsigned int));
    SWRC_unpackFromUint8((uint8_t*)signal->N_name,signal->N_N_name,sizeof(long unsigned int),cfgFile);
  }
  // **name
    if (signal->N_N_name!=0) {
      signal->name=(char**) calloc(signal->N_N_name,sizeof(char*));
      for (i=0;i<signal->N_N_name;i++) {
        signal->name[i]=(char*) calloc(signal->N_name[i],sizeof(char));
        SWRC_unpackFromUint8((uint8_t*)signal->name[i],signal->N_name[i],sizeof(char),cfgFile);
      }
    }
}

// Function for loading the struct
int loadSignalStruct (signalStruct *signal, const char *filename) {
}

// Function for saving the struct

void saveSignalStruct (signalStruct *signal, const char *filename,int *col,int Ncols) {
  int i,j,maxN;
  FILE *f;
  if ((f=fopen(filename,"w"))!=NULL) {
    // find the maximum value of N over all columns requested to be printed
    for (i=0,maxN=0;i<Ncols;i++){
      if (signal->N[col[i]]>maxN) maxN=signal->N[col[i]];
    }
    printf ("In function saveSignalStruct. maxN=%d. col={%d,%d}\n",maxN,col[0],col[1]);
    // print the requested columns headers
    fprintf(f,"#");
    for (i=0;i<Ncols;i++) {
      fprintf(f," signal[%d]",i);
    } fprintf(f,"\n");
    // print the requested columns themselves
    for (j=0;j<maxN;j++) {
      for (i=0;i<Ncols;i++) {
	if (j<signal->N[col[i]]) { // print the signal[j] only up to the length of that signal
	  if(signal->type[col[i]]==0) fprintf(f," %1"SCNu8"",signal->x[col[i]][j]);
	  if(signal->type[col[i]]==1) fprintf(f," %9c",*((char*)signal->x[col[i]]+j));
	  if(signal->type[col[i]]==2) fprintf(f," %9d",*((int*)signal->x[col[i]]+j));
	  if(signal->type[col[i]]==3) fprintf(f," %9u",*((unsigned int *)signal->x[col[i]]+j));
	  if(signal->type[col[i]]==4) fprintf(f," %9lu",*((long unsigned int *)signal->x[col[i]]+j));
	  if(signal->type[col[i]]==5) fprintf(f," %9.4f",*((float*)signal->x[col[i]]+j));
	  if(signal->type[col[i]]==6) fprintf(f," %7.4lf",*((double*)signal->x[col[i]]+j));
	} else {
	  fprintf(f," %1s","");
	}
      }
      fprintf(f,"\n");
    }
    fclose(f);
  } else {
    printf("Cannot open %s for writing\n",filename);
  }
}
void saveSignalBinary(signalStruct *signal, char *filename){
  uint8_vector u;
  int i;
  SWRC_init_uint8_vector(&u);
  SWRC_packSignalStruct(signal,&u);
  //printf("In function saveSignalBinary:");
  //for (i=0;i<20;i++) printf("%2d %"SCNu8"\n",i,u.x[i]);
  SWRC_saveuint8_vector(&u,1,filename,0);
  SWRC_free_uint8_vector(&u);
}

void saveSignalBinary_wrap(signalStruct *signal, char *arg) {
  char *signalFilename=NULL;
  long unsigned int N_signalFilename=0;
  printf("In function saveSignalBinary_wrap\n");
  if (SWRC_readStringArgumentFromString(arg,"signalFilename",(void**)&signalFilename,&N_signalFilename,"%s")>0) {
    printf("Saving signal to binary file: %s\n",signalFilename);
    saveSignalBinary(signal,signalFilename);
    free(signalFilename);
  } else {
    printf("Please specify signalFilename to save the signal to in command: saveSignalBinary\n");
  }
}

int loadSignalBinary(signalStruct *signal, char *filename){
  uint8_vector u;
  int i;
  SWRC_init_uint8_vector(&u);
  long int startTime=SWRC_loaduint8_vector(&u,1,filename);
  if(startTime==1) { // no cfg file found
    return(1);
  }
  //printf("In function loadSignalBinary:");
  //for (i=0;i<20;i++) printf("%2d %"SCNu8"\n",i,u.x[i]);
  SWRC_unpackSignalStruct(signal,&u);
  SWRC_free_uint8_vector(&u);
  return(0);
}

void loadSignalBinary_wrap(signalStruct *signal, char *arg) {
  char *signalFilename=NULL;
  long unsigned int N_signalFilename=0;
  printf("In function saveSignalBinary_wrap\n");
  if (SWRC_readStringArgumentFromString(arg,"signalFilename",(void**)&signalFilename,&N_signalFilename,"%s")>0) {
    printf("Loading signal from binary file: %s\n",signalFilename);
    if (loadSignalBinary(signal,signalFilename)==1) {
      // Unable to find signalFilename
      printf("Unable to find %s\n",signalFilename);exit(-1);
    }
    free(signalFilename);
  } else {
    printf("Please specify signalFilename to save the signal to in command: saveSignalBinary\n");
  }
}
// given a file of signals as displayed by the printAllSignals() function,
// this function takes this columnar output (which was previously saved to a file)
// and loads them back into the signal structure in signal.
// signal->x[i] should already be of the right type before calling this function. 
// The signal length must be correct prior to calling this function. 
// This function is intended to be used to save and restore known bit sequences,
// so the bit sequence lengths need to be correctly set. 
void loadIndividualUint8Signal(signalStruct *signal,char *filename, int signalIndex) {
  printf("In function loadIndividualUint8Signal\n");
  FILE *f;
  int i,j;
  int tmp;
  int N; // N is the number of space delimited columns (SDC) in a row.
  char row[1000]; // length of a row should be less than 1 thousand.
  if ((f=fopen(filename,"r"))!=NULL) {
    fgets(row,1000,f); // read in the header row
    for (i=0;i<signal->N[signalIndex];i++) {
      fgets(row,1000,f);
      for (N=0,j=1;j<strlen(row);j++) { // search over each space-delimited column.
	if (row[j-1]==' ' && row[j]!=' ') N++;
	if (N==signalIndex+2) {N=j;break;} // save the position of the last SDC in N.
      }
      // Scan the signalIndex+1'th column into the signal array.
      sscanf(&row[N],"%"SCNu8"",&signal->x[signalIndex][i]);
    }
    fclose(f);
  } else {
    printf("Cannot open %s for reading\n",filename);
  }
}
// save a signal to a txt file for processing outside, eg: in octave
void saveDoubleSignalTxt(signalStruct *signal, int sigIndex, char *filename) {
  int i;
  FILE *f;
  double *x=(double*)signal->x[sigIndex];
  int N    =(int) signal->N[sigIndex];
  if ((f=fopen(filename,"w"))!=NULL) {
    for (i=0;i<N;i++)
      fprintf(f,"%9.6lf\n",x[i]);
    fclose(f);
  } else {
    printf("Unable to open %s for writing\n",filename);
    exit(-1);
  }
}
// The counter part to the init function. Frees up all the memory 
// in the structure
void freeSignalStruct (signalStruct *signal) {
  int i,*j;
  if (signal==NULL) return;
  // Fields entered by the user
  for (i=0;i<signal->N_N;i++) {
    if (signal->N[i]!=0) {       free(signal->x[i]);signal->x[i]=NULL;}
  }
  if (signal->N_N!=0) {          free(signal->x);signal->x=NULL;}
  for (i=0;i<signal->N_N_name;i++) {
    if (signal->N_name[i]!=0) {   free(signal->name[i]);signal->name[i]=NULL;}
  }
  if (signal->N_N_name!=0) {     free(signal->name);signal->name=NULL;}
  if (signal->N_N!=0) {          free(signal->N);signal->N=NULL;}
  if (signal->N_N_name!=0) {     free(signal->N_name);signal->N_name=NULL;}
  if (signal->N_type!=0) {       free(signal->type);signal->type=NULL;}
  signal->N_N                   =0;
  signal->N_N_name              =0;
  signal->N_type                =0;
}

// Set parameters (fields) in the structure
// Change the values of fields in the structure
void setParmSignalStruct (signalStruct *signal, char *arg) {
  int i;
  SWRC_removeSpaces(arg);
  if (SWRC_readMultipleArgumentsFromString(arg,"N",(void**)&signal->N,&signal->N_N,sizeof(long unsigned int),"%lu")>0) {
    printf("N=[");for (i=0;i<signal->N_N;i++){printf("%lu ",signal->N[i]);}printf("]\n");
  }
  if (SWRC_readMultipleArgumentsFromString(arg,"N_name",(void**)&signal->N_name,&signal->N_N_name,sizeof(long unsigned int),"%lu")>0) {
    printf("N_name=[");for (i=0;i<signal->N_N_name;i++){printf("%lu ",signal->N_name[i]);}printf("]\n");
  }
  if (SWRC_readMultipleArgumentsFromString(arg,"type",(void**)&signal->type,&signal->N_type,sizeof(uint8_t),"%"SCNu8"")>0) {
    printf("type=[");for (i=0;i<signal->N_type;i++){printf("%"SCNu8" ",signal->type[i]);}printf("]\n");
  }
  if (*arg!='\0') {
    printf("signal module: Remaining unknown parms in arg list:%s\n",arg);
  }
}

// A command comes from the user
// This function processes the command, sets variables, 
// carries out the printing or plotting, etc...
void processCommandSignal (signalStruct *signal, const char *command) {
  char commandParameter[400];
  int i;
  printf("processCommandSignal:%s\n",command);
  for(i=0;i<400 && i<strlen(command);) {
    if (SWRC_matchCommand(command,"load",&i,commandParameter,400)==1) {
	loadSignalStruct(signal,commandParameter);
	continue;
    }

    if (SWRC_matchCommand(command,"print",&i,commandParameter,400)==1) {
	printSignalStruct(signal,"signal",0,0);
	continue;
    }

    if (SWRC_matchCommand(command,"setParm",&i,commandParameter,400)==1) {
	setParmSignalStruct(signal,commandParameter);
	continue;
    }

    if (SWRC_matchCommand(command,"help",&i,commandParameter,400)==1) {
	helpCommandSignal(0);
	continue;
    }

    if (SWRC_matchCommand(command,"run",&i,commandParameter,400)==1) {
	runSignal(signal);
	continue;
    }

    printf("processCommandSignal: Unknown command:%s\n",&command[i]);
    break;
  }
}

// Provides instructions on the commands that this module is able to process.
void helpCommandSignal (int index) {
  printf("Commands recognized by %d:signalStruct:\n",index);
  printf("  \"print();\"        : print the signalStruct fields\n");
  printf("  \"setParm(arg);\"   : set the signalStruct fields\n");
  printf("  \"help();\"         : display this help screen\n");
}

// Some modules require a precomputation phase, perhaps 
// done after the training, perhaps without training. 
// That precomputation function is done here
void precompSignal (signalStruct *signal) {
}

// Some modules have a training phase where modules before them are run
// and statistic collected so the module can run properly.
// This function performs the training for the module then 
// saved back to the .cfg file. 
void trainSignal (signalStruct *signal) {
}

// Finally when everything is in place, the module must be
// run during the actual simulation. The code for running
// the module is in this function.
void runSignal (signalStruct *signal) {
  int i;
  int *output;
  printf("In function runSignal\n");
  // Allocate memory for 1 more signal. The output of this function should go there.
  // User needs to supply the length of the output vector and sizeof()
  // the vector type eg: float, int, double etc...
  // If type is double, store the output in (double*)signal->x[signal_N_N-1]
  // memory for this vector is allocated by this function:
  incrementByOneSignal(signal,1,2,"signal"); // create a new vector of type 2 (int*)
  output = (int*) signal->x[signal->N_N-1]; // assign pointer to this new memory. Write results to *output

  // assign the name to the signal struct
  char name[] = "runSignal";
  int N_name = strlen(name);
  signal->N_name[signal->N_N_name-1]=strlen(name)+1;
  signal->name[signal->N_N_name-1]=(char*)realloc(signal->name[signal->N_N_name-1],(N_name+1)*sizeof(char));
  strcpy(signal->name[signal->N_N_name-1],name);
}

// Given a type code, return the sizeof this type
int getUnitSizeFromType(uint8_t type) {
  switch(type) {
  case 0: // uint8_t
    return(sizeof(uint8_t));
  case 1: // char
    return(sizeof(char));
  case 2: // int
    return(sizeof(int));
  case 3: // unsigned int 
    return(sizeof(unsigned int));
  case 4: // long unsigned int 
    return(sizeof(long unsigned int));
  case 5: // float
    return(sizeof(float));
  case 6: // double
    return(sizeof(double));
    // Default type: uint8_t
  default:
    printf("Returning default unit size\n");
    return(sizeof(uint8_t));
  }
}
// Increment the list of vectors signal->x by 1 vector
// of size N. Push this vector onto the end of the **vector->x list.
// *signal is the signalStruct array 
// type determines the type of the signal array
// 0 - uint8_t
// 1 - char
// 2 - int
// 3 - unsigned int
// 4 - long unsigned int
// 5 - float
// 6 - double
uint8_t* incrementByOneSignal(signalStruct *signal,int N,uint8_t type, const char *moduleName) {
  int i;
  int unitSize=getUnitSizeFromType(type);
  char formatString[10];
  int N_name = strlen(moduleName);

  // increment signal type and store.
  signal->N_type++;
  signal->type=(uint8_t*)realloc(signal->type,signal->N_type*sizeof(uint8_t));
  signal->type[signal->N_type-1]=type;
  // increment the signal portion of the struct
  signal->N_N++; //printf("signal->N_N=%lu\n",signal->N_N);
  signal->N=(long unsigned int*) realloc(signal->N,signal->N_N*sizeof(unsigned long int));
  signal->N[signal->N_N-1]=N;
  signal->x=(uint8_t**)realloc(signal->x,signal->N_N*sizeof(uint8_t*));
  if (N>0) signal->x[signal->N_N-1]=(uint8_t*)calloc(N,unitSize);
  // increment the name portion of the struct
  signal->N_N_name++;
  signal->N_name=(long unsigned int*) realloc(signal->N_name,signal->N_N_name*sizeof(unsigned long int));
  signal->N_name[signal->N_N_name-1]=N_name+1; // plus one for the end of string '\0'
  signal->name=(char**)realloc(signal->name,signal->N_N_name*sizeof(char*));
  signal->name[signal->N_N_name-1]=(char*)calloc(signal->N_name[signal->N_N_name-1],(signal->N_name[signal->N_N_name-1]+1)*sizeof(char));
  strcpy(signal->name[signal->N_N_name-1],moduleName);
  return(signal->x[signal->N_N-1]);
}

// generate a sequence of random bits for vector of type uint8_t
// in the signals array. Since the bits are only 0 or 1, they fit
// inside uint8. Length of vector is N
void generatePseudoRandomUserBitsSignal(signalStruct *signal, int N) {
  int i;
  int idum;
  long unsigned int iseed;
  incrementByOneSignal(signal,N,0,"generatePseudoRandomUserBitsSignal");
  SWRC_randomize(&idum);iseed=idum;
  // fill up the double with rand numbers.
  // equivalent to filling the uint8 array 8 at a time.
  for(i=0;i<N;i++) {
    signal->x[signal->N_N-1][i]=SWRC_irbit2(&iseed);
  }
}
// get the index'th unit signal (eg: [1,0,0,0...,0]) of length N
// and put it onto the signal stack
void SWRC_signal_getUnitVector(signalStruct *signal, int index, int N) {
  int i;
  int idum;
  long unsigned int iseed;
  // get a uint8_t signal
  incrementByOneSignal(signal,N,0,"SWRC_signal_getUnitVector");
  // fill up with zero's except the index'th position.
  for(i=0;i<N;i++) {
    signal->x[signal->N_N-1][i]=0;
  }
  signal->x[signal->N_N-1][index]=1;
}

void SWRC_signal_getRandomVector(signalStruct *signal, int N) {
  int i;
  int idum;
  long unsigned int iseed;
  SWRC_randomize(&idum);iseed=idum;
  // get a uint8_t signal
  incrementByOneSignal(signal,N,0,"SWRC_signal_getRandomVector");
  // fill up with zero's except the index'th position.
  for(i=0;i<N;i++) {
    signal->x[signal->N_N-1][i]=0;
  }
}
// create a new signal on the signal stack and copy the double array *x there.
void cpDoubleToSignal(signalStruct *signal, double *x, int N,char *descriptionString) {
  int i;
  double *y; // pointer to the new signal on the signal stack.
  y = (double*)incrementByOneSignal(signal,N,6,descriptionString);
  for (i=0;i<N;i++) y[i]=x[i];
}
// This function is a hack that enables us to store the SNR and the H
// coefficients into the signal.
// When runISIAWGN is called,  3 signals are created:
// 1) The convolution of h with the bits => noise free signal
// 2) The noise component of the signal
// 3) The sum of the noise free and the noise.
// Most often only signal[3] is ever used by the subsequent routines, the
// previous signals are there for validation or confirmation purposes.
// Some routines want the SNR and H coefficients, such as for plotting
// scatter plots. This function hacks the SNR and H coefficients into the
// signal by saving the SNR to the first position of signal[2]
// and the H coefficients to the ensuing positions of signal[2] as a double
// Since this signal[2] is almost never used, nothing is lost. But it is a hack.
// Under normal execution, this function is not called.
void appendSNRHToSignal(double SNR, int N_h, float *h, signalStruct *signal, int signalIndex) {
  double *x = (double*)signal->x[signalIndex];
  int i;
  x[0] = SNR;
  x[1] = N_h;
  for (i=0;i<N_h;i++) {
    x[i+2] = h[i];
  }
}
void extractSNRHFromSignal(double *SNR, int *N_h, float **h, signalStruct *signal, int signalIndex) {
  double *x = (double*)signal->x[signalIndex];
  int i;
  *SNR=x[0];
  *N_h=x[1];
  printf("N_h=%d\n",*N_h);
  if (*h!=NULL) free(*h);
  h[0]=(float*)calloc(*N_h,sizeof(float));
  for (i=0;i<*N_h;i++)h[0][i]=x[i+2];
}

// Upsample signal->x[index] in-place by U
// signal->N[index] is also modified by this routine.
void signal_upsample_signal_inplace(signalStruct *signal,int index,int U) {
  uint8_t *tmp;
  int i,j,k;
  int size = getUnitSizeFromType(signal->type[index]); // size of 1 unit of the signal type
  // copy the signal to temp local memory
  tmp = (uint8_t*) calloc(signal->N[index],size);
  for (i=0;i<signal->N[index];i++) for (j=0;j<size;j++) tmp[i*size+j]=signal->x[index][i*size+j];
  // increase the size of the vector
  signal->x[index]=(uint8_t*)realloc(signal->x[index],signal->N[index]*U*size); // reallocate the memory for the upsampled-in-place vector
  // copy the signal, upsampled back into the newly allocated memory.
  for (i=0;i<signal->N[index];i++)
    for (j=0;j<U;j++)
      for (k=0;k<size;k++) signal->x[index][i*size*U+j*size+k]=tmp[i*size+k];
  signal->N[index]*=U;
  free(tmp);
}
///////////////////////////////////////////////
// Routines to help create PBM/PNG files.
///////////////////////////////////////////////
void SWRC_printPBMHeader(FILE *f, int N, int M) {
  fprintf(f,"P1\n");
  fprintf(f,"%d %d\n",N,M);
}

// find and return the position of the last slash in filename.
// used to remove the path
int SWRC_findLastSlash(char *filename) {
  int i,ls;
  for (i=0,ls=0;i<strlen(filename);i++) {
    if (filename[i]=='/') ls=i;
  }
  return(ls);
}
