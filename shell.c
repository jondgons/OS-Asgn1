#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "GlobalVars.txt"
#include "Queue.h"

char** ParseByNewlineSemiColon(int*, char*);
char** ParseBySpace(char*);

int main (int argc, char* argv[]){
  
  if(argc == 2){

    struct Queue *queue = (struct Queue*) malloc(sizeof(struct Queue));
    struct QueuePid* queuePid = (struct QueuePid*) malloc(sizeof(struct QueuePid));
    FILE *fptr = NULL;
    char** commandArr;
    char commandStr[SIZE]; //= (char*) malloc(SIZE*sizeof(char));//commandStr[SIZE]
    char** args;
    char tmp[SIZE];
    int i = 0;
    int err = 0;
    int* count = (int*) malloc(sizeof(int));
    
    fptr = fopen(argv[1], "r");

    if(fptr != NULL){
      /*PROBLEM: On bad input still prints the next command twice.*/
      while(fgets(commandStr, SIZE-1, fptr) != NULL){
	i+=1;//printf("String %s\n", commandStr);
	commandArr = ParseByNewlineSemiColon(count, commandStr);

	for(int j = 0; j < *count; j++){
	  //printf("\n\nPreparing to execute command: %s\n\n", commandArr[j]);
	  args = ParseBySpace(commandArr[j]);
	  push(queue, args);
	}
	//i = 1;
	char** arguments;
        
	pid_t* pid = (pid_t*) malloc(sizeof(pid_t));
        int stat;
	while(queue->size != 0){
	  arguments = pop(queue);
	  
	  if((*pid = fork()) == 0){
	    
	    err = execvp(arguments[0], arguments);printf("err %d\n", err);
	  }
	  if(err == -1){
	    printf("\nCommand execution failed.\n");
	    exit(0);
	  }

	  if(err == 0){
	    
	    pushPid(queuePid, pid);//printf("Pid growth %d\n", queuePid->size);
	    pid = (pid_t*) malloc(sizeof(pid_t));
	  }
	  else{
	    err = 0;
	  }
	  //i += 1;
	}
	while(queuePid->size != 0){printf("\npid dec %d\n", queuePid->size);
	  waitpid(*popPid(queuePid), &stat, 0);
	}//printf("string2 %s\n", commandStr);
      }//printf("iteration %d\n", i);
    }
    //free(pid);
    free(queuePid);
    fclose(fptr);
    free(args);
    free(commandArr);
    free(count);
    free(queue);
    //free(commandStr);
    
    exit(0);
  }

  else{

    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
    struct QueuePid* queuePid = (struct QueuePid*) malloc(sizeof(struct Queue));
    pid_t* pid = (pid_t*) malloc(sizeof(pid_t));
    char** args;
    char* userInput = (char*) malloc(SIZE*sizeof(char));
    char** commandList;
    int err = 0;
    int cont = 0;
    int* count = (int*) malloc(sizeof(int));

    printf("INPUT: ");

    while(cont == 0){
      
      fgets(userInput, SIZE-1, stdin);
      //printf("user input %s check", userInput);
      if(strcmp(userInput, "quit\n") == 0 || strcmp(userInput, "Quit\n") == 0
	 || strcmp(userInput, "q\n") == 0 || strcmp(userInput, "Q\n") == 0){
	
	exit(0);
      }
      
      commandList = ParseByNewlineSemiColon(count, userInput);

      for(int j = 0; j < *count; j++){
	printf("Preparing to execute command: %s\n", commandList[j]);
	args = ParseBySpace(commandList[j]);                             
        push(queue, args);
      }

      char** arguments;
      while(queue->size != 0){
	//printf("args  size %d\n", /*arguments[0],*/ queue->size);
	arguments = pop(queue);
        
	if(*pid = fork() == 0){
	  err = execvp(arguments[0], arguments);//printf("\n\nexited fork %d \n\n", err);
	}
	if(err == -1){
	  printf("\nCommand execution failed.\n");
	  exit(0);
	  //err = 0;
	}

	if(err == 0){
	  
	  pushPid(queuePid, pid);//printf("\npid growth %d\n",queuePid->size);
	  pid = (pid_t*) malloc(sizeof(pid_t));
	}
	else{
	  err = 0;
	}
      }
      int stat;//printf("\n\nFinicshed starting commands.\n\n");
      while(queuePid->size != 0){//printf("pid queue size %d\n", queuePid->size);
	waitpid(*popPid(queuePid), &stat, 0);
      }
      printf("\nINPUT: ");
    }
    free(args);
    free(queue);
    free(queuePid);
  }
   
  exit(0);
}

char** ParseByNewlineSemiColon(int* count, char* commands){
  
  char* token;
  char character[2] = "\n";
  char** args = (char**) malloc(SIZE*SIZE*sizeof(char));
  char** commandList = (char**) malloc(SIZE*SIZE*sizeof(char));
  
  int i = 1;

  token = strtok(commands, character);
  commandList[0] = token;
  while(token != NULL){
    token = strtok(NULL, character);
    commandList[i] = token;
    i += 1;
  }
  /*for(int x = 0; x < i; x++)
    Mark(commands);*/
  character[0] = ';';
  //token = strtok(commands, character);
  //args[0] = token;
  i = 1;
    token = strtok(commandList[0], character);
    args[0] = token;
    *count = 0;
    while(token != NULL){
      
      token = strtok(NULL, character);
      args[i] = token;
      i += 1;
      *count += 1;
    }
    //}
  
  free(commandList);
  free(token);
  //printf("cj %s\n",args[0]);
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
  //args[i+1] = NULL;
    
  free(token);
  
  return(args);
}
