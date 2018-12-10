#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//dumb little sequential search
_Bool search(char* input){
  for(unsigned int i = 0; i < strlen(input); i++){
    if(!strncmp(input + i,"1101",4)){
      return 1;
    }
  }
  return 0;
}

int main(){

  //input character to get
  char input[40]; //20 character input buffer

  do{
    //get input 1
    printf("input a string enter or \'q\' to quit: ");
    if(scanf("%s",input) == 0){ //error handeling
      printf("read error\n");
      exit(1);
    }

    switch (search(input)) {
      case 0: printf("string is NOT ACCEPTED\n"); break;
      case 1: printf("string is ACCEPTED\n"); break;
    }

  }while(strcmp(input,"q"));
  return 0;
}
