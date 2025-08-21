static char arr[4][4]= {{0x06, 0x5B, 0x4F,0x77},
                    {0x66, 0x6D, 0x7C, 0x40},
                    {0x07, 0x7F, 0x67, 0x80},
                    {0x00, 0x3F, 0x00, 0xBF}};

static char decoder[4][4] = {{1,2,3,10},
                        {4,5,6,11},
                        {7,8,9,12},
                        {14,0,15,13}};

static char numbers[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67};

int keypad_scanner(int *row, int *col);

int form_digit(char four_digit[], int digits);

int input(char four_digit[], char four_digit_decoded[], int n);

void display_digits(char four_digit[]);

void calculate(char four_digit_decoded_1[], int count1, char four_digit_decoded_2[], 
              int count2, char operator_decoded[], char answer[]);

int keypad_scanner(int *row, int *col){
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

int form_digit(char four_digit[], int digits){
  if(digits==1){
    return four_digit[0];
  }
  else if(digits==2){
    return four_digit[0]*10 + four_digit[1];
  }
  else if(digits==3){
    return four_digit[0]*100 + four_digit[1]*10 + four_digit[2];
  }
  else if(digits==4){
    return four_digit[0]*1000 + four_digit[1]*100 + four_digit[2]*10 + four_digit[3];
  }
}

int input(char four_digit[], char four_digit_decoded[], int n){
  volatile int row, col,i,k;
  volatile int count=0;
  for(i=0;i<n;i++){ // gets the first value
    while (!keypad_scanner(&row, &col));  

    four_digit[i] = arr[row][col];
    four_digit_decoded[i] = decoder[row][col];

    if(four_digit_decoded[i]==14){ // if * pressed, stop
      break;
    }
    count++;
    while(keypad_scanner(&row, &col));

    for(k=0;k<2000;k++);
  }

  return count;
}

void display_digits(char four_digit[]){
  volatile long i,k;

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

void calculate(char four_digit_decoded_1[], int count1, char four_digit_decoded_2[], 
              int count2, char operator_decoded[], char answer[]){
          
          
    int first = form_digit(four_digit_decoded_1, count1); 
    int second = form_digit(four_digit_decoded_2, count2);   
    int ans, i, negative = 0;  //flag to check if value is negative
    int flag = 0;   // flag to check if value exceeds 9999

    if(operator_decoded[0]==10){ //addition
      ans = first + second;
    }
    else if(operator_decoded[0]==11){ //subtraction
      if(second>first){
        ans = second - first;
        negative = 1;
      }
      else{
        ans = first - second;
      }
    }
    else if(operator_decoded[0]==12){ //multiplication
      ans = first * second;
    }
    else if(operator_decoded[0]==13){ //division
      if(second==0){ //error
        flag = 1;
      }
      else{
        ans = first/second;
      }
    }

    if(ans>9999){
      flag = 1;
    }



  if(flag==1){
    for(i=0;i<4;i++){
      answer[i] = 0x79;
    }
  }
  else{
    if(negative){
      answer[0] = 0x40;
    }else{
      answer[0] = (ans>=1000)? numbers[ans/1000] : 0x00;
    }
    answer[3] = numbers[ans%10];
    answer[2] = (ans>=10)? numbers[(ans/10)%10] : 0x00;
    answer[1] = (ans>=100)? numbers[(ans/100)%10] : 0x00;
  }


            
}