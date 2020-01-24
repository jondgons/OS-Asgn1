#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INT 2147483647

void ParseString(char*, char*);

int main (int argc, char* argv[]){
  
  if(argc == 1){
    
    FILE *fptr;
    char* commandStr;
    char* command;
    fptr = fopen(argv[1], r);

    if(fptr != NULL){

      commandStr = fgets(commandStr, MAX_INT, fptr);
      ParseString(commandStr, command);
    }
    fclose(fptr);
  }
  else{
    
    int check = 0;
    int err = 0;
    char *command = (char*) malloc(INT_MAX*sizeof(char));
    while(check == 0){
      
      printf("INPUT: ");
      fgets(command, INT_MAX, stdin);

      if(strcmp(command, "quit") == 0){
	check = 1;
      }
      else{
	err = system(command);
	if(err = -1){
	  check = 1;
	}
      }
    }
  }

  return(0);
}

void ParseString(char* commands, char* command){

}
