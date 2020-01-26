#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_INT 2147483647

int SIZE = 150;

char** ParseBatch(char**, char**);

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
      
      args = ParseBatch(commandArr, commandStr);
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
    free(args);
    free(commandArr);
    free(commandStr);
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

char** ParseBatch(char** commandList, char** commands){

  char ** args = (char**) malloc(SIZE*SIZE*sizeof(char));
  char tmp[2] = "\n";
  char* token;
  char** commandSplitting = (char**) malloc(SIZE*SIZE*sizeof(char));

  token = strtok((char*) commands[0], tmp);
  commandList[0] = token;
  //printf("split by endline %s\n", commandList[0]);
  int i = 0;
  while(token != NULL){
    i++;
    token = strtok(NULL, tmp);
    commandList[i] = token + '\0';
    //printf("split by endline %s\n", commandList[i]);
  }
  tmp[0] = ';';
  token = strtok((char*) commandList[0], tmp);
  commandSplitting[0] = token;
  //printf("\nSplitting by ; %s\n", commandSplitting[0]);
  i = 0;
  while(token != NULL){

    i+=1;
    token = strtok(NULL, tmp);
    commandSplitting[i] = token;
    //printf("Splitting by ; %s\n", commandSplitting[i]);
  }
  
  tmp[0] = ' ';
  int elemCount = i;
  int count = 0;
  //printf("\n\ncommandSplitting %s\n", commandSplitting[0]);
  i = 0;
  //printf("elemCount %d\n", elemCount);
  for(int x = 0; x < elemCount; x++){
    token = strtok(commandSplitting[x], tmp);
    args[count] = token;
    //printf("token %s\n", token);
    //printf("count %d\n",count);
    //printf("\nSplitting by <space> %s\n", args[count]);
    count += 1;
    while(token != NULL){
      
      i+=1;
      token = strtok(NULL, tmp);
      //printf("token %s\n",token);
      args[count] = token;
      count += 1;
      //printf("Splitting by <space> %s\n", args[count]);
    }
  }
  /*for(int j = 0; j < 10; j++)
    printf("args %s\n", args[j]);*/
  //printf("congrats! Left\n");
  free(token);
  free(commandSplitting);
 
  return(args);
}
