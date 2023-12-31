#include <stdio.h>

typedef union {
    float f;
    unsigned u;
} FloatToUInt32;

int floatFloat2Int(unsigned uf) {
  unsigned ux = uf;

  unsigned frac = uf&0x7FFFFF;
  unsigned sign = (uf >> 31) & 1;
  
  // 0x7F800000 = Binary: 01...1(8)0...0(23)
  int exp = (uf >> 23) & 0xFF;

  if(exp == 0xFF)
    return 0x80000000u;  
  

  exp = exp - 127; // 8 bits in total

  if(exp < 0)
    return 0;

  if(exp >= 31)
    return 0x80000000;
  

  // Iterate the first exp(left to right) bits of mantissa
  // to get the absolute value of the integer number
  int num = (1 << exp);

  for(int i = 0; i < exp; i++){
    // bit index: 22 - i
    if(i >= 23){
      break;
    }

    int bit = (uf >> (22 - i)) & 1;
    num += bit * (1 << (exp - 1 - i));
  }

  if(sign == 0)
    return num;
  

  else
    return ~num + 1;
}

int main(){
    FloatToUInt32 converter;
    
    //float x = 10.5;
    //while(x >=  -10000000000.5){
      //converter.f = x;
      //unsigned z = converter.u;

      //int y = floatFloat2Int(z);

      //if(y != (int) x){
        //printf("Wrong! x is: %f , but floatFloat2Int(x) is: %d \n", x, y);
        //break;
      //}

      //else{
        //printf("Correct! x is: %f , and floatFloat2Int(x) is: %d \n", x, y);
      //}

      //x -= 100000.5;
    //}

    //printf("All sucess!\n");

    
    
    printf("Hello worzld\n");

  
    return 0;
}