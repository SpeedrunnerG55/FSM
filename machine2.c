#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//container for machine
struct FSM{
  //tells what state to go to, when you look up the current state and the input
  int** Table;    //[states][strlen(alphabet)] so i know how to free the memory

  char* alphabet; //library of posible inputs
  int states;     //number of states
  int *output;    //the output depending on the state
};

//exacute the finite state machine and return last output from the string
_Bool FSM(struct FSM machine,char* input){
  int state = 0;
  char *outputStr = malloc(strlen(input) + 1);
  printf("%-20s |%s \n","input string",input);
  printf("%-20s%i|","current state",state);
  outputStr[0] = machine.output[state] + '0';
  for(unsigned int i = 0; i < strlen(input); i++){
    for(unsigned int j = 0; j < strlen(machine.alphabet); j++){
      if(machine.alphabet[j] == input[i]){
        state = machine.Table[state][j];
        outputStr[i+1] = machine.output[state] + '0';
        printf("%i",state);
      }
    }
  }
  printf("\n%-20s%c|%s\n","output string",outputStr[0],outputStr+1);
  return (machine.output[state]);
}

void show_FSM(struct FSM endPattern){
  unsigned int alphabetLength = strlen(endPattern.alphabet);
  printf("states inputs ");
  for(unsigned int j = 2; j < alphabetLength; j++){
    printf("   ");
  }
  printf("outputs\n");
  printf("%6s|",""); //7 spaces
  for(unsigned int j = 0; j < alphabetLength; j++){
    printf("%3c",endPattern.alphabet[j]);
  }
  printf("|\n");
  printf("------+");
  for(unsigned int j = 0; j < alphabetLength; j++){
    printf("---");
  }
  printf("+------\n");
  for(int i = 0; i < endPattern.states; i++){
    printf("%3s%-3i|","S",i);
    for(unsigned int j = 0; j < alphabetLength; j++){
      printf("%3i",endPattern.Table[i][j]);
    }
    printf("| %i \n",(i == endPattern.states - 1));
  }
}

char* getAlphabet(char* input){
  char* alphabet = NULL;
  int count = 0;

  for(unsigned int i = 0; i < strlen(input); i++){
    _Bool same = 0;
    for(unsigned int j = i; j < strlen(input); j++){
      if(j > i){
        same |= (input[i] == input[j]);
      }
    }
    if(!same){
      count++;
      alphabet = realloc(alphabet,count);
      alphabet[count - 1] = input[i];
    }
  }
  return alphabet;
}


struct FSM create_pattern_FSM(char* pattern){

  //get alphabet from the input pattern
  char* alphabet = getAlphabet(pattern);
  // char* alphabet = {"01"};//literal alphabet so ignore characters outside the alphabet

  printf("generating FSM table...\n");
  int states = strlen(pattern) + 1; //number of states
  int alphabetLength = strlen(alphabet); //number of characters to look through
  //Table says if i am at state [x] and i recieve a [y] input then go to my return value
  int** Table = malloc(states * sizeof(int*));
  int *output = malloc(states * sizeof(int));
  for(int i = 0; i < states; i++){
    output[i] = i == states - 1; //if the currest state is the end state output 1 for an recignised pattern
    Table[i] = malloc(alphabetLength * sizeof(int));
    for(int j = 0; j < alphabetLength; j++){ //only look through the alphabet for a match and ignore everything els
      printf("state %3i ... ",i);
      //last state loops back to itself every time because pattern is found
      if(i == states - 1){
        Table[i][j] = states - 1;
        printf("stays at %i via %c\n",i,alphabet[j]);
      }
      //if the place in the pattern is the same as the index for the alphabet
      //that means that to get to the next state the input needs to be that character
      //and the return value needs to be the next state
      else if(pattern[i] == alphabet[j]){
        Table[i][j] = i + 1;
        printf("goes to %i via %c\n",i+1,alphabet[j]);
      }
      else{
        for(int k = 0; k < i; k++){
          Table[i][j] = 0; //default go back to unless it finds a matching section of the sequence
          //compare the current sequence with progresivly smaller slices of the beginig of the sequence
          // uncomment to see comparison [slice|last byte]
          // for(int l = 0; l < i-k-1; l++){
          //   printf("%c",pattern[l+k+1]);
          // }
          // printf("|%c",pattern[i-k-1]);
          // printf(" vs ");
          // for(int l = 0; l < i-k-1; l++){s
          //   printf("%c",pattern[l]);
          // }
          // printf("|%c\n",alphabet[j]);
          if(strncmp(pattern,pattern + k + 1,i-k-1) == 0 && pattern[i-k-1] == alphabet[j]){
            Table[i][j] = i-k;
            printf("goes back to %i via %c b/c ",i-k,alphabet[j]);
            for(int l = 0; l < i-k-1; l++){
              printf("%c",pattern[l+k+1]);
            }
            printf("%c ",alphabet[j]);
            printf("is a start of a new sequence\n");
            break;
          }
        }
        if(Table[i][j] == 0){
          printf("goes all the way back to 0 via %c\n",alphabet[j]);
        }
      }
    }
  }

  //pack up output into struct for output
  struct FSM machine;
  machine.output = output;
  machine.alphabet = alphabet;
  machine.states = states;
  machine.Table = Table;
  return machine;
}

void freeMachine(struct FSM machine){
  for(int i = 0; i < machine.states; i++){
    free(machine.Table[i]); //[states][strlen(alphabet)] so i know how to free the memory
  }
  free(machine.Table);
  printf("done!");
}

int main(){
  //uncomment 2 and comment 1 for live behavior

  //pattern to look for
  char* pattern = "1101";

  //input character to get
  char input[20]; //20 character input buffer 1

  //build machine :D
  struct FSM machine = create_pattern_FSM(pattern);

  //show the machine table
  show_FSM(machine);

  //run loop
  do{
    //get input 1
    printf("input a string enter or \'q\' to quit\n");
    if(scanf("%s",input) == 0){
      printf("read error\n");
      exit(1);
    }

    if(!strcmp(input,"q"))
    break;//exit condition

    //get output of FSM
    if(FSM(machine,input)){
      printf(" ACCEPTED\n");
    }
    else{
      printf(" REJECTED\n");
    }
    //quite whan q
  }while(1);

  printf("Quitting...\n");

  //free memory
  freeMachine(machine);

  return 0;
}
