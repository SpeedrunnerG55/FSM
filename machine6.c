#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
  //pattern to look for
  char* pattern = "1101";
  //settup
  char input[50]; //50 character input buffer
  //run loop
  do{
    //get input
    printf("input a string enter or \'q\' to quit: ");
    if(!scanf("%s",input)){ //error handeling
      printf("read error\n");
      exit(1);
    }
    if(!strcmp(input,"q"))
    break;//exit condition

    if(strstr(input,pattern) != NULL) //does not ignore characters not in alphabet {0,1}
    printf("String is ACCEPTED\n");
    else
    printf("String is NOT ACCEPTED\n");

    //quite whan q
  }while(1);
  return 0;
}
