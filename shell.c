#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INT 2147483647

void ParseString(char*, char*);

int main (int argc, char* argv[]){
  printf("%d", argc);
  if(fork() == 0)
    printf("child running\n");
  else
    printf("main running\n");
  if(argc == 1){
    
    FILE *fptr = NULL;
    char* commandStr;
    char* command = (char*) malloc(15 * 15 * sizeof(char));
    fptr = fopen(argv[1], "r");
  
    if(fptr != NULL){

      //fgets(commandStr, MAX_INT, fptr);
      //ParseString(commandStr, command);
    }
    fclose(fptr);
    //free(command);
  }
  /*else{
    
    int check = 0;
    int err = 0;
    char *command = (char*) malloc(MAX_INT*sizeof(char));
    while(check == 0){
      
      printf("INPUT: ");
      fgets(command, MAX_INT, stdin);

      if(strcmp(command, "quit") == 0){
	check = 1;
      }
      else{
	//err = system(command);
	if(err = -1){
	  check = 1;
	}
      }
    }
    }*/

  return(0);
}

void ParseString(char* commands, char* command){

  int i = 0;
  int x = 0;
  while(commands[i] != 0){

    //command[x][i] = commands[i];
    if(commands[i] == ';'){

      x+=1;
    }
    i+=1;
  }
}
