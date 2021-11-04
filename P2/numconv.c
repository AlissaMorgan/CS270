/**
 *  @Alissa Morgan
 */

#include <stdio.h>

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
char int_to_char (int value, int radix) {
	if(value >= radix || value < 0){
		return '?';	
	}else if (value >= 0 && value <= 9){
		return value + '0';	
	}else{
		value += 7;
		return value + '0';	
	}

}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int char_to_int (char digit, int radix) {
	int dig = (int) digit;
	if(digit >= '0' && digit <= '9'){
		dig -= '0';
	}else if(digit >= 'A' && digit <= 'Z'){
		dig = dig - 'A' + 10;
	}else if(digit >= 'a' && digit <= 'z'){
		dig = dig - 'a' + 10;
	}else{ return -1;}

	if(dig >= radix || dig < 0){
		return -1;
	}
	return dig;
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void div_rem (int numerator, int divisor, int* remainder, int* quotient) {
	int r = numerator % divisor;
	*remainder = r;
	int q = numerator / divisor;
	*quotient = q;
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int ascii_to_int (int valueOfPrefix, int radix) {
	char c = getchar();
	int x = char_to_int(c, radix);
	if(c == '\n'){ return valueOfPrefix;}
	valueOfPrefix = radix * valueOfPrefix + x;
	return ascii_to_int (valueOfPrefix, radix);
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void int_to_ascii (int value, int radix) {
	int r, q;
	div_rem(value, radix, &r, &q);
	char c = int_to_char(r, radix);
	//printf("r: %i, q: %i, char is: %c", r, q, c);
	if(q != 0){
		int_to_ascii(q, radix);
	}
	printf("%c", c);	
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
double frac_to_double (int radix) {
  return -1.0;
}

