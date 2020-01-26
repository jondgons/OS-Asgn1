#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_INT 2147483647

char* ParseBatch(char*, char**);

int main (int argc, char* argv[]){
  
  if(argc == 2){
    
    FILE *fptr = NULL;
    //char commandStr[];
    char* commandStr = (char*) malloc(150*sizeof(char*));
    char** commandArr = (char**) malloc(15*150*sizeof(char));
    fptr = fopen(argv[1], "r");
  
    if(fptr != NULL){

      fgets(commandStr, MAX_INT, fptr);
      
      ParseBatch(commandStr, commandArr);
      
      /*for(int i = 0; commandArr[i] != EOF; i++){
	if(fork() == 0){
	  execvp(commandArr[i]);
	}
	else{
	  wait();
	}
	}*/
    }
    fclose(fptr);
    free(commandArr);
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
  else
    printf("file pointer null\n");
  return(0);
}

char* ParseBatch(char* commands, char** commandList){

  char tmp[2] = ";";
  char* token = (char*) malloc(150*sizeof(char));

  token = strtok(commands, tmp);
  commandList[0] = token;
  
  int i = 0;
  while(token != NULL){
    i++;
    token = strtok(NULL, tmp);
    commandList[i] = token;
  }
  commandList[i+1] = "\0";
  char tmp2[2];
  int len;/*Current problem: Outer for loop runs too long.*/
  for(int x = 0; commandList[x][0] != '\0'; x+=1){
    printf("x %d\n", x);
    len = strlen(commandList[x]);
    for(int y = 0; y < len && y+1 < len && len >= 2; y+=2){
      tmp[0] = commandList[x][y];
      tmp[1] = commandList[x][y+1];
      if(strcmp(tmp, "./") == 0){
	printf("found exe\n");
      }printf("y %d\n", y);
    }printf("next it\n");
  }printf("congrats! Left\n");
  free(token);
}
