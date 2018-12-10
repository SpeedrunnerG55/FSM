#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

_Bool FSM(char* input){
  regex_t regex;
  int reti;
  char* pattern = "1101"; //any pattern can go here

  /* Compile regular expression */
  reti = regcomp(&regex, pattern, 0);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    exit(1);
  }

  /* Execute regular expression */
  reti = regexec(&regex, input, 0, NULL, 0);
  if (!reti) {
    return 1;
  }
  else if (reti == REG_NOMATCH) {
    return 0;
  }
  else {
    //print error message to stantard error stream
    regerror(reti, &regex, input, sizeof(input));
    fprintf(stderr, "Regex match failed: %s\n", input);
    exit(1);
  }
  /* Free memory allocated to the pattern buffer by regcomp() */
  regfree(&regex);
}

int main(){

  //input character
  char input[20];

  //print initial state
  do{
    //get input
    printf("input a string enter or \'q\' to quit\n");
    if(scanf("%s",input) == 0){
      printf("read error\n");
      exit(1);
    }

    if(!strcmp(input,"q"))
    break;//exit condition

    //get output of FSM
    if(FSM(input)){
      printf("ACCEPTED\n");
    }
    else{
      printf("REJECTED\n");
    }
    //quite whan q
  }while(1);

  printf("Quitting...\n");
  return 0;
}
