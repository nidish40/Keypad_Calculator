int keypad_scanner(int *row, int *col){  //function for scanning keypad
  volatile int i, j;

  volatile char *f_out = (char*)0x31; 
  volatile char *k_in = (char*)0x106; 
    
    for(i=0;i<4;i++){
      *f_out = 1<<i;
      
      char col_val = *k_in & 0x0F;//and with lower nibble to see if key is pressed

      if(col_val!=0){
        for(j=0;j<4;j++){
          if(col_val & (1<<j)){
            *row = i;
            *col = j;
            return 1;
          }
        }
      }
    }
    return 0;
}

void digit_init(int n, char four_digit[], char arr[4][4], 
                char four_digit_numerical[], char keypad_decoder[4][4], int *row, int *col){ //ip number function
    volatile int i,k;
    for(i=0;i<n;i++){
      while (!keypad_scanner(row, col));  

      four_digit[i] = arr[*row][*col];
      four_digit_numerical[i] = keypad_decoder[*row][*col];

      while(keypad_scanner(row, col));

      for(k=0;k<200000;k++);
    }
}


void display_number(char four_digit[]){
  volatile long m,k,i;

  volatile char *c_out = (char*)0x28; //control signal
  volatile char *a_out = (char*)0x22; //seven segment io port
  
  for(k=0;k<100;k++){
    *a_out = four_digit[0];
    *c_out = 0x0E;
    for(i=0;i<2000;i++);

    *c_out = 0x0F;
    for(i=0;i<100;i++);

    *a_out = four_digit[1];
    *c_out = 0x0D;
    for(i=0;i<2000;i++);

    *c_out = 0x0F;
    for(i=0;i<100;i++);

    *a_out = four_digit[2];
    *c_out = 0x0B;
    for(i=0;i<2000;i++);

    *c_out = 0x0F;
    for(i=0;i<100;i++);

    *a_out = four_digit[3];
    *c_out = 0x07;
    for(i=0;i<2000;i++);

    *c_out = 0x0F;
    for(i=0;i<100;i++);
  }

}

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
 volatile long i, k, m;

  char arr[4][4]= {{0x06, 0x5B, 0x4F,0x77}, //A stands for addition
                    {0x66, 0x6D, 0x7C, 0x00},
                    {0x07, 0x7F, 0x67, 0x00},
                    {0x41, 0x3F, 0x00, 0x00}}; //star is =

  char keypad_decoder[4][4] = {{1, 2, 3, 10},
                    {4, 5, 6, 11},
                    {7, 8, 9, 12},
                    {14, 0, 15, 13}};

  volatile char number[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67};

 
   volatile char four_digit1[4] = {0,0,0,0};
   volatile char four_digit_numerical1[4] = {0,0,0,0};

   volatile char four_digit2[4] = {0,0,0,0};
   volatile char four_digit_numerical2[4] = {0,0,0,0};

   digit_init(2, four_digit1, arr, four_digit_numerical1,keypad_decoder, row, col);

   display_number(four_digit1);

   

 
  

 
  /*
  char ans = four_digit_numerical[0] + four_digit_numerical[2];
  four_digit[2] = number[ans/10];
  four_digit[3] = number[ans%10];


  for(k=0;k<100;k++){
    *a_out = four_digit[2];
    *c_out = 0x0B;
    for(i=0;i<2000;i++);

    *c_out = 0x0F;
    for(i=0;i<100;i++);

    *a_out = four_digit[3];
    *c_out = 0x07;
    for(i=0;i<2000;i++);

    *c_out = 0x0F;
    for(i=0;i<100;i++);
  }

  */

 
    
}
