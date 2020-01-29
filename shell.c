#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INT 2147483647

int SIZE = 1024;

char** ParseByNewlineSemiColon(char*);
char** ParseBySpace(char*);

int main (int argc, char* argv[]){
  
  if(argc == 2){
    
    FILE *fptr = NULL;
    char** commandArr;
    char* commandStr = (char*) malloc(SIZE*sizeof(char));
    char** args;
    char tmp[SIZE];
    
    fptr = fopen(argv[1], "r");

    if(fptr != NULL){

      fgets(commandStr, SIZE, fptr);

      commandArr = ParseByNewlineSemiColon(commandStr);

      int err = 0;
      args = ParseBySpace(commandArr[0]);
      
      int i = 1;
      
      while(args[0] != NULL){      

	if(fork() == 0){
	  err = execvp(args[0], args);
	}
	else
	  wait(NULL);
	if(err == -1){
	  printf("execution failed\n");
	}

	  args = ParseBySpace(commandArr[i]);
	  
	  i += 1;
      }
    }
    fclose(fptr);
    free(args);
    free(commandArr);
    free(commandStr);
  }
  else{
    //char check[2] = "";
    char** args;
    char* userInput = (char*) malloc(SIZE*sizeof(char));
    char** commandList;
    int err = 0;
    int cont = 0;

    printf("INPUT:");

    while(cont == 0){
      
      fgets(userInput, SIZE, stdin);

      if(strcmp(userInput, "quit\n") == 0 || strcmp(userInput, "Quit\n") == 0
	 || strcmp(userInput, "q\n") == 0 || strcmp(userInput, "Q\n") == 0){
	
	exit(0);
      }
      
      commandList = ParseByNewlineSemiColon(userInput);

      for(int x = 0; x < SIZE; x++){
	args = ParseBySpace(commandList[x]);
	
	if(args[0] != NULL){
	  if(fork() == 0){
	    
	    err = execvp(args[0], args);
	  }
	  else{
	    wait(NULL);
	  }
	  
	  if(err != 0){
	    printf("Error in command execution %d\n", err);
	  }
	}
      }
      printf("INPUT:");
    }
    free(args);
  }
   
  exit(0);
}

char** ParseByNewlineSemiColon(char* commands){
  char* token;
  char character[2] = "\n";
  char** args = (char**) malloc(SIZE*SIZE*sizeof(char));
  char** commandList = (char**) malloc(SIZE*SIZE*sizeof(char));
  
  token = strtok(commands, character);
  commandList[0] = token;

  int i = 1;
  while(token != NULL){

    token = strtok(NULL, character);
    commandList[i] = token;
    i += 1;
  }

  character[0] = ';';
  
  int count = 0;
  for(int x = 0; x < SIZE; x++){

    token = strtok(commandList[x], character);
    args[count] = token;
    count += 1;
    
    while(token != NULL){

      token = strtok(NULL, character);
      args[count] = token;
      count += 1;
    }
  }
  free(commandList);
  free(token);

  return(args);
}
char** ParseBySpace(char* commands){

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
    
  free(token);
  
  return(args);
}
