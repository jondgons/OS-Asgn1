#include <stdio.h>

int main(int argc, char* argv[]){
  FILE* fptr = fopen("out.txt", "w");
  fputs("Hello World!", fptr);
  if(argc != 1)
    printf("Bye forever world.");
  else
    printf("Hello World!");
  fclose(fptr);
  return 0;
}
