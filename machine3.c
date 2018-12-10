#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//exacute the finite state machine and return last output from the string
_Bool FSM(char* input){

  //input alphabet
  char* alphabet = "01";

  //output table
  int output[] = {
    0,
    0,
    0,
    0,
    1 //accept final state
  };

  //state table [num_states][alphabetLength]
  // if i am at state [state] and input is [input] then next state is return value
  int Table[][2] = {
    {0,1},
    {0,2},
    {3,2},
    {0,4},
    {4,4} //if end is reached stay at end
  };

  int state = 0;//initial state
  for(unsigned int i = 0; i < strlen(input); i++){
    //only search through and accept state changes if the input is in the input alphabet
    for(unsigned int j = 0; j < strlen(alphabet); j++){ //search through alphabet for input
      if(alphabet[j] == input[i]){ //if the input matches the alphabet, go to the state at that index
        state = Table[state][j]; //go to next state
      }
    }
  }
  return (output[state]);
}


int main(){
  //input character to get
  char input[40]; //20 character input buffer

  //run time loop
  do{
    //get input 1
    printf("input a string enter or \'q\' to quit: ");
    if(!scanf("%s",input)){ //error handeling
      printf("read error\n");
      exit(1);
    }

    if(!strcmp(input,"q"))
    break;//exit condition

    //get output of FSM
    if(FSM(input))
    printf("string is ACCEPTED\n");
    else
    printf("string is NOT ACCEPTED\n");
  }while(1);

  //end message
  printf("Quitting...\n");

  return 0;
}
