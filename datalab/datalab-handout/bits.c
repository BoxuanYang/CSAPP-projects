/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  int x1 = ~x & y;
  int x2 = x & ~y;

  int result = ~x1 & ~x2;
  result = ~result;
  return result;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  int minimum = 1;

  minimum = minimum << 31;
  return minimum;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */

 /*
 x is Tmax:
 x = 01...1
 <-> x+x = 1...10 AND (x != 1...1, -1)
 <-> x+x+1 = 1...1 AND (x != 1...1, -1)
 <-> (x+x+1+1 == 0) AND (x != 1...1, -1)

2's complement: +x -> ~x -> ~x + 1(-x)

-1 -> 1...1(binary)
 */
int isTmax(int x) {
  /*
  if((x+1)){ // make sure x != -1, x+1 != 0
    if(!(~x^(x+1))){
      return 1;
    }
  }*/
  

  // x+1 != 0 AND (~x^(x+1)) == 0
  // ! ( (x+1 == 0) | (~x^(x+1)) != 0 )

  return !(  !(x+1) |   (~x^(x+1)) );



  
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */


 /*
 0xA = 0b1010
 */
int allOddBits(int x) {
  int mask = 0xAA;

  mask = mask + (mask << 8); // mask = 0xAAAA
  mask = mask + (mask << 16); // mask = 0xAAAAAAAA = 0b1010...1010

  // y has to be equal to mask
  return !((x&mask)^mask);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */

 /*
                    ~     +1
 2's complement: +x -> ~x -> -x
 */
int negate(int x) {
  return ~x+1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */

 /*
 0x30: 00000000000000000000000000110000
 0x39: 00000000000000000000000000111001

Allowed:
0000
0001
0010
0011
0100
0101
0110
0111
1000
1001

In summary, the 4 least signigicant bits are either: 0XXXX or 100X
 */
int isAsciiDigit(int x) {
  // checks whether it follows 0...0(26 digits) 11 XXXX format,
  // flag1 = 1 if x is of format 0...0(26 digits)11XXXX
  int flag1 = !((x>>4)^3);
  
  
  // checks whether the 3rd digit is 0. 
  // flag2 = 1 if 3rd digit is 0.
  int flag2 = !((x >> 3) & 1);
  

  // checks whether the 1st-3rd digits are 100
  // flag3 = 1 if 1st-3rd digits are 100.
  int flag3 = !(((x>>1)&7)^4);

  return flag1 & (flag2 | flag3);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /*
  if x!= 0, return y; else return z;
  */

  x = !!x; // x == 1 if x != 0 and 0 otherwise
  x = ~x + 1; // x == 1...1 if x ===1 and 0...0 otherwise.

  return (x&y) | (~x & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /*
  First, get diff = y - x , if >= 0 return 1 otherwise 0
  */
  int diff = y + (~x + 1); // diff = y - x

  // flag1 = 1 if 31th digit of diff is 1, 0 otherwise.
  int flag1 = !((diff>>31)&1);
  return flag1;
}

/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  /*
  if x == 0 return 1, otherwise return 0.

  if x == 0:
     ~x+1 == 0
  else if x != 0:
     ~x+1 == -x
  */

  
  // is_negative = 1 if x < 0, 0 otherwise
  int is_negative = (x>>31)&1;
  // is_positive = 1 if x > 0, 0 otherwise
  int is_positive = ((~x+1)>>31)&1;

  // is_zero = 1 if x == 0, 0 otherwise
  int is_non_zero = is_negative | is_positive;
  int is_zero = is_non_zero^1;


  return is_zero;
  
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  // is_positive = 1 if x > 0, 0 otherwise
  int sign=x>>31;
  x = (sign&~x)|(~sign&x);

  

  int b16 = !!(x>>16) << 4;
  x = x>>b16;

  int b8 = !!(x>>8) << 3;
  x = x>>b8;

  int b4 = !!(x>>4) << 2;
  x = x>>b4;

  int b2 = !!(x>>2) << 1;
  x = x>>b2;

  int b1 = !!(x>>1);
  x = x>>b1;

  int b0 = x;



  return b16 + b8 + b4 + b2 + b1 + b0 + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */

 /*
 To solve this, exponent += 1(23-30), Mantissa不变(0-22).

Special values: 
NaN: X11111111X...X

 */
unsigned floatScale2(unsigned uf) {
  // 0x7F800000 = Binary: 01...1(8)0...0(23)
  int exponent = (0x7F800000 & uf) >> 23;
  //int sign = uf&(1<<31);

  

  if(exponent == 255){ // if uf is NaN
    return uf;
  }

  if(exponent == 0) return uf<<1|(uf&(1<<31));

  
  
  

  exponent++;
  if(exponent == 255){
    return 0x7F800000 | (uf&(1<<31));
  }


 // 0x7F800000 = Binary: 01...1(8)0...0(23)

 // uf = X0...0(8)X...X(23)
  uf = uf & ~(0x7F800000);
  uf = uf | (exponent << 23);
  return uf;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
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
    int bit = (uf >> (22 - i)) & 1;
    num += bit * (1 << (exp - 1 - i));
  }

  if(sign == 0)
    return num;
  

  else
    return ~num + 1;
  

}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  // 2^8 - 1 = 255, hence [0, 255] - 127 = [-127, 128]
  int INF = 0xff<<23;


  if(x >= 0){
    if(x > 128)
      return INF;
    

    int exp = (x + 127) & 0xFF;
    return exp << 23;
  }

  // x < 0
  if(x < -127){
    return 0;
  }

  int exp = x + 127;
  return exp<<23;
}
