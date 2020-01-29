#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INT 2147483647

int SIZE = 1024;

<<<<<<< HEAD
char** ParseByNewlineSemiColon(char*);
char** ParseBySpace(char*);
=======
char** ParseBatch(char*);
>>>>>>> 3d9a8d75850db0703ae8b0e375ff7a2b7b0dceff

int main (int argc, char* argv[]){
  
  //execvp(NULL, h);
  if(argc == 2){
    
    FILE *fptr = NULL;
    char** commandArr;
    char* commandStr = (char*) malloc(SIZE*sizeof(char));
    char** args;
<<<<<<< HEAD
    char tmp[SIZE];
=======
    char tmp[SIZE];// Don't like doing this so probably optimize later.

>>>>>>> 3d9a8d75850db0703ae8b0e375ff7a2b7b0dceff
    
    fptr = fopen(argv[1], "r");

    if(fptr != NULL){

<<<<<<< HEAD
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
=======
      fgets(tmp, MAX_INT, fptr);
      commandStr[0] = tmp;

      int i = 0;
      while(fgets(tmp, MAX_INT, fptr) != NULL){

	i+=1;
	commandStr[i] = tmp;
      }
      char character[2] = "\n";
      char* token = strtok((char*) commandStr[0], character);
     
      commandStr[0] = token;
      i = 1;
      while(token != NULL){
	token = strtok(NULL, character);
	commandStr[i] = token;
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
      

>>>>>>> 3d9a8d75850db0703ae8b0e375ff7a2b7b0dceff
    }
    fclose(fptr);
    free(args);
    free(commandArr);
    free(commandStr);
    free(command);
  }
<<<<<<< HEAD
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
    
=======
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
>>>>>>> 3d9a8d75850db0703ae8b0e375ff7a2b7b0dceff
  free(token);
  
  return(args);

}
