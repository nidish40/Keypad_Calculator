#include "helper.h"

//A is for addition
//B is subtraction
//C is for multiplication
//D is for division
//Use * after entering numbers smaller than length of 4

void setup() {
  // put your setup code here, to run once:
  
  volatile char *f_ddr = (char*)0x30; //keypad output row

  volatile char *k_ddr = (char*)0x107; //keypad input col

  volatile char *a_ddr = (char*)0x21;

  volatile char *c_ddr = (char*)0x27;

  *a_ddr = 0xFF;
  *c_ddr = 0xFF;
  *k_ddr = 0x00; //input
  *f_ddr = 0xFF;  //output
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  volatile int row, col;
  volatile long i,j, k;
  volatile int count1, count2, count3 ;

  char four_digit_1[4] = {0,0,0,0};
  char four_digit_decoded_1[4] = {0,0,0,0};

  char four_digit_2[4] = {0,0,0,0};
  char four_digit_decoded_2[4] = {0,0,0,0};

  char operator_[4] = {0,0,0,0};
  char operator_decoded[4] = {0,0,0,0};

  char answer[4] = {0,0,0,0};


  count1 = input(four_digit_1, four_digit_decoded_1, 4);

  display_digits(four_digit_1);

  count3 = input(operator_, operator_decoded, 1);

  display_digits(operator_);

  count2 = input(four_digit_2, four_digit_decoded_2, 4);

  display_digits(four_digit_2);

  calculate(four_digit_decoded_1, count1, four_digit_decoded_2, count2, operator_decoded, answer);
    
  display_digits(answer);

  
}
