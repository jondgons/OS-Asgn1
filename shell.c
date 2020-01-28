#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_INT 2147483647

int SIZE = 150;

char** ParseBatch(char*);

int main (int argc, char* argv[]){
  
  if(argc == 2){
    
    FILE *fptr = NULL;
    char** commandArr = (char**) malloc(SIZE*SIZE*sizeof(char));
    char** commandStr = (char**) malloc(SIZE*SIZE*sizeof(char));
    char** args;
    char tmp[SIZE];// Don't like doing this so probably optimize later.
    
    fptr = fopen(argv[1], "r");

    if(fptr != NULL){

      fgets(tmp, MAX_INT, fptr);
      commandStr[0] = tmp;

      int i = 0;
      while(fgets(tmp, MAX_INT, fptr) != NULL){

	i+=1;
	commandStr[i] = tmp;
      }
      
      char* token;
      char character[2] = "\n";
      
      //printf("splitting by newline %s\n", commandStr[0]);

      token = strtok(commandStr[0], character);
      commandStr[0] = token;
      
      i = 0;
      while(token != NULL){

	i += 1;
	token = strtok(NULL, tmp);
	commandStr[i] = token;
      }

      //printf("finished splitting by newline\n");

      character[0] = ';';
      token = strtok(commandStr[0], character);
      commandArr[0] = token;

      i = 0;
      while(token != NULL){

	i += 1;
	token = strtok(NULL, tmp);
	commandArr[i] = token;
      }
      
      //printf("started parsing %s\n", commandArr[0]);
      args = ParseBatch(commandArr[0]);
      //printf("finished parsing %s\n", commandArr[0]);

      int err = 0;
      if(fork() == 0){
	char CHAR[][];
	printf("forking\n");
	err = execvp(args[0], args);
	
      }
      if(err != 0){
	printf("execution failed");
      }
      i = 0;
      while(token != NULL){
	
	token = strtok(NULL, character);
	commandArr[i] = token;

	if(commandArr[i] != NULL)
	  args = ParseBatch(commandArr[i]);

	if(fork() == 0){
	  //printf("forking\n");
	  //printf("args %s %s\n", args[0], args[1]);
	}
	i += 1;
      }
      
    }
    fclose(fptr);
    free(args);
    free(commandArr);
    free(commandStr);
  }
  else
    printf("file pointer null\n");
  return(0);
}

char** ParseBatch(char* commands){

  char ** args = (char**) malloc(SIZE*SIZE*sizeof(char));
  char tmp[2];
  char* token;
  
  tmp[0] = ' ';
  token = strtok(commands, tmp);
  args[0] = token;

  int i = 0;
  while(token != NULL){

    i += 1;
    token = strtok(NULL, tmp);
    args[i] = token;
  }
  args[i+1] = NULL;
  //printf("check %s\n", args[i+1]);  
  free(token);
  
  return(args);
}
