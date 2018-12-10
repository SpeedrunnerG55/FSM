#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct machineInput{
  _Bool* bits;
  int length;
};

//option 1 interperate non bits as false
struct machineInput load(char* input){
  _Bool* bits = malloc(strlen(input) * sizeof(_Bool));
  for(unsigned int i = 0; i < strlen(input); i++){
    bits[i] = input[i] == '1'; //only read 1 as true and everything els is false
  }
  struct machineInput ret;
  ret.bits = bits;
  ret.length = strlen(input);
  return ret; //return the bits
}

//option 2 interperate non bits as true
struct machineInput load2(char* input){
  _Bool* bits = malloc(strlen(input) * sizeof(_Bool));
  for(unsigned int i = 0; i < strlen(input); i++){
    bits[i] = !(input[i] == '0'); //only read 0 as false and everything els is true
  }
  struct machineInput ret;
  ret.bits = bits;
  ret.length = strlen(input);
  return ret; //return the bits
}

//option 3 ignore non bits
struct machineInput load3(char* input){
  _Bool* bits = malloc(strlen(input) * sizeof(_Bool));
  int count = 0;
  for(unsigned int i = 0; i < strlen(input); i++){
    if(input[i] == '0' || input[i] == '1'){ //filter out non bits
      bits[count] = input[i] == '1'; //read bit
      count++;
    }
  }
  struct machineInput ret;
  ret.bits = bits;
  ret.length = count; //set return count to count b/c the output stream may not be the same length as input stream
  return ret; //return the bits
}

//the machine
_Bool FSM(struct machineInput input){
  short pattern = 0xD; //1101 in hex
  short patterlength = 4;
  _Bool lastStateReached = 0; //true when last state is reached
  for(int i = 0; i < input.length - (patterlength - 1); i++){ //each clock pulse move input across readhead and ignore bitstreams that are less
    short state = 0;
    for(int j = 0; j < patterlength; j++){
      _Bool jthBit = pattern >> (4 - (1+j)) & 1;
      state += (input.bits[j+i] == jthBit);//shift pattern by j bits to read the jth bit and compare it to the i + jth input steam bit then incriment the state if found
    }
    // printf("%i\n",state);
    lastStateReached |= state == patterlength; //or the result to keep it true after the state has been reached
  }
  free (input.bits);
  return lastStateReached;
}

//the machine a little more simplified
_Bool FSM2(struct machineInput input){
  _Bool lastStateReached = 0;
  for(int i = 0; i < input.length - 3; i++) //move input across readhead and ignore bitstreams that are less
  lastStateReached |= (input.bits[i] && input.bits[i+1] && !input.bits[i+2] && input.bits[i+3]);
  free (input.bits);
  return lastStateReached;
}

int main(){

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

    if(FSM(load3(input))) //ignore characters not in alphabet {0,1}
    printf("String is ACCEPTED\n");
    else
    printf("String is NOT ACCEPTED\n");

    //quite whan q
  }while(1);

  printf("safe to close\n");
  return 0;
}
