/*
 * testConv.c - simple driver to test methods of numconv.h.
 *
 * "Copyright (c) 2013-2016 by Fritz Sieker."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written
 * agreement is hereby granted, provided that the above copyright notice
 * and the following two paragraphs appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE TO ANY PARTY FOR DIRECT,
 * INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE AUTHOR
 * HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE AUTHOR SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS"
 * BASIS, AND THE AUTHOR NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT,
 * UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "numconv.h"

/** @mainpage Number Conversion in C
 *  \htmlinclude "P2.html"
 */

/** @file: testConv.c
 *  @brief Driver to test functions of numConv.c (do not modify)
 *
 * @details This is a driver program to test the functions
 * defined in numConv.h and implemented in numConv.c. The program takes up to 
 * three command line parameters and calls one of the methods, then
 * prints the results. To see how to use the program, execute
 * <code>./testConv</code> in a terminal window. This will print a usage
 * statement defining how to run the program. The 1st parameter of the
 * program is always a key defining which function to run.
 * The options are:
 * <ul>
 * <li><b>i2c</b> convert a number to a character digit (tests
 *   <code>int_to_char()</code>)</li>
 * <li><b>c2i</b> convert a character digit to its integer value (tests
 *   <code>char_to_int()</code>)</li>
 * <li><b>dnr</b> test the <code>div_rem()</code> function</li>
 * <li><b>a2i</b> convert a string of characters to a number (tests
 *   <code>ascii_to_int()</code>)</li>
 * <li><b>i2a</b> print the digit(s) of a number specified by a string (tests
 *   <code>int_to_ascii()</code>)</li>
 * <li><b>f2d</b> convert a string representing a fraction into a double (tests
 *   <code>frac_to_double()</code>)</li>
 * </ul>
 * <p>
 * The 2nd parameter is always the radix you work in (2..36). The 3rd
 * parameter depends on the function.
 * <p>
 * A sample execution might be: <code>testConv c2i 16 A</code>
 * <p>
 * All numbers are unsigned.
 * <p>
 * @author Fritz Sieker
 */

/** Print a usage statement, then exit the program returning a non zero
 * value, the Linux convention indicating an error
 */
static void usage() {
  puts("Usage: testConv i2c radix number");
  puts("       testConv c2i radix digit");
  puts("       testConv dnr numerator divisor");
  puts("       testConv a2i radix (the string is entered through the standard input)");
  puts("       testConv i2a radix number");
  puts("       testConv f2d radix (the string is entered through the standard input)");
  puts("The radix and number parameters are always base 10 numbers.");
  exit(1);
}

/** Entry point of the program
 * @param argc count of arguments, will always be at least 1
 * @param argv array of parameters to program argv[0] is the name of
 * the program, so additional parameters will begin at index 1.
 * @return 0 the Linux convention for success.
 */
int main (int argc, char* argv[]) {
  if (argc < 3)
    usage();
  
  char* op    = argv[1];
  int   radix = atoi(argv[2]);

  if (strcmp(op, "c2i") == 0) {
    if (argc != 4)
      usage();
  
    char c = argv[3][0];
    printf("char_to_int('%c', %d) returns %d", c, radix, char_to_int(c, radix));
  }

  else if (strcmp(op, "i2c") == 0) {
    if (argc != 4)
      usage();
    
    int n = atoi(argv[3]);
    printf("int_to_char(%d, %d) returns '%c'", n, radix, int_to_char(n, radix));
  }

  else if (strcmp(op, "dnr") == 0) {
    if (argc != 4)
      usage();
    
    int num   = atoi(argv[2]);
    int denom = atoi(argv[3]);
    int quotient, remainder;

    printf("div_rem(%d, %d) ", num, denom);
    div_rem(num, denom, &remainder, &quotient);
    printf("quotient: %d remainder: %d", quotient, remainder);
  }

  else if (strcmp(op, "a2i") == 0) {
    if (argc != 3)
      usage();
    
    printf("ascii_to_int(0, %d) returns %d", radix, ascii_to_int(0, radix));
  }

  else if (strcmp(op, "i2a") == 0) {
    if (argc != 4)
      usage();
    
    int n = atoi(argv[3]);
    printf("int_to_ascii(%d, %d) returns \"", n, radix);
    int_to_ascii(atoi(argv[3]), radix);
    printf("\"");
  }

  else if (strcmp(op, "f2d") == 0) {
    if (argc != 3)
      usage();
    
    // Read the "0."
    getchar();
    getchar();
    printf("frac_to_double(%d) returns %f", radix, frac_to_double(radix));
  }
  
  else
    usage();
  
  printf("\n");
  return 0;
}

