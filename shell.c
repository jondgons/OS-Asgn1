#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_INT 2147483647

int SIZE = 150;

char** ParseBatch(char*);
/*TODO: Have to add null character to strings*/
int main (int argc, char* argv[]){
  
  //execvp(NULL, h);
  if(argc == 2){
    
    FILE *fptr = NULL;
    char** commandArr = (char**) malloc(SIZE*SIZE*sizeof(char));
    char** commandStr = (char**) malloc(SIZE*SIZE*sizeof(char));
    char** args;
    char tmp[SIZE];// Don't like doing this so probably optimize later.
    int err = 0;
    char** command = malloc(SIZE*SIZE*sizeof(char));
    
    fptr = fopen(argv[1], "r");

    if(fptr != NULL){
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
      
      character[0] = ';';
      token = strtok((char*) commandStr[0], character);
      commandStr[0] = token;
      i = 1;
      while(token != NULL){
        token = strtok(NULL, character);
        commandStr[i] = token;//printf("command %s\n\n", commandStr[i]);
	i += 1;
      }
    
      int iterator = 0;
      for(int k = 0; k < SIZE; k++){//args may literally be NULL at some points
	//printf("num %s\n",commandStr[k]);
	if(commandStr[k] != NULL){
	  args = ParseBatch(commandStr[k]);
	  printf("not null %s\n", args[0]);
	}
	
	//printf("parsed\n");
	//for(i = 0; i < SIZE; i++)
	//printf("command %s %d\n", args[i], i);
      }
    
      printf("exit");
    }
    fclose(fptr);
    free(args);
    free(commandArr);
    free(commandStr);
    free(command);
  }
  else
    printf("file pointer null\n");
  return(0);
}

char** ParseBatch(char* commands){printf("enters\n");
  //printf("check %d\n",strcmp(commands, ""));
  if(commands != NULL){printf("parsing because true\n");//strcmp(commands, "") != 0){
    //char ** args = (char**) malloc(SIZE*SIZE*sizeof(char));
    char tmp[2] = "\n";
    char* token;
    char** commandSplitting = (char**) malloc(SIZE*SIZE*sizeof(char));
    
    tmp[0] = ' ';
    int count = 0;
    
    int i = 1;
    token = strtok((char*) commands, tmp);
    commandSplitting[0] = token;
    while(token != NULL){
      
      token = strtok(NULL, tmp);
      commandSplitting[i] = token;
      i++;
    }
    return(commandSplitting);
  }
  return(NULL);
}
