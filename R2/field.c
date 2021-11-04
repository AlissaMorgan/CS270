#include "field.h"
#include <stdio.h>


/** @file field.c
 *  @brief You will modify this file and implement five functions
 *  @details Your implementation of the functions defined in field.h.
 *  You may add other function if you find it helpful. 
 * <p>
 * @author <b>Alissa Morgan</b>
 */

/** @todo Implement in field.c based on documentation contained in field.h */
int getBit (int value, int position) {
	int mask = 1 << position;
	//printf("mask: %i /n", mask);
	if(value & mask){return 1;}
	return 0;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int setBit (int value, int position) {
	int mask = 1 << position;
	return mask | value;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int clearBit (int value, int position) {
	int mask = 1 << position;
	int nmask = ~mask;
	//printf("mask: %x /n", nmask);
	return value & nmask;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int getField (int value, int hi, int lo, bool isSigned) {
	int segment = 0, shift = 0, isNeg = getBit(value, hi);
	for(int i = lo; i <= hi; i++){
		int placement = getBit(value, i);
		segment += placement << shift;
		shift++;
	}
	if(isSigned && isNeg){return segment * -1;}
	//printf("segment: %x", segment);
	return segment;
}
