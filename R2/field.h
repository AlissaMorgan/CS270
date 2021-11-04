#ifndef __FIELD_H__
#define __FIELD_H__

/*
 * field.h - simple field manipulation functions to get students working
 *           with masking. This will be used in the simulator to extract
 *           information when executing an LC3 instruction. It may also be
 *           used in the assembler to "create" the 16 bit LC3 instructions.
 *           If an assignment involving floating point manipulation (e.g.
 *           16 bit floating point addition), this file can be used to
 *           provide support routines for extracting/setting the sign,
 *           exponent, and mantissa fields.
 *
 * "Copyright (c) 2013 by Fritz Sieker."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written
 * agreement is hereby granted, provided that the above copyright notice
 * and the following two paragraphs appear in all copies of this software,
 * that the files COPYING and NO_WARRANTY are included verbatim with
 * any distribution, and that the contents of the file README are included
 * verbatim as part of a file named README with any distribution.
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

/** @file field.h
 *  @brief Defines interface of field.c functions (do not modify)
 *  @details This file defines the interface to a C file field.c that
 *  you will complete.  You will learn how to
 *  use the C language operators for binary <b>and</b> (<b>&amp;</b>),
 *  binary <b>or</b> (<b>|</b>), and binary <b>not</b> (<b>~</b>). You will also use the
 *  C language <b>bit shift</b> operators (<b>&lt;&lt;</b> and <b>&gt;&gt;</b>).
 *  @author Fritz Sieker
 */
#include <stdbool.h>
/** Get the specified bit from a value.
 *  @param value the source value or bit pattern
 *  @param position the bit position to get (0..31)
 *  @return 1 when the bit is set, and 0 otherwise.
 */
int getBit (int value, int position);

/** Set the specified bit in a value (make it equal to 1).
 *  @param value the source value or bit pattern
 *  @param position the bit position to be set (0..31)
 *  @return An integer value that is the original value with the specified bit
 *  set.
 */
int setBit (int value, int position);

/** Clear the specified bit in a value (make it equal to 0).
 *  @param value the source value or bit pattern
 *  @param position the bit position to be set (0..31)
 *  @return An integer value that is the original value with the specified bit
 *  cleared.
 */
int clearBit (int value, int position);

/** Extract the field between bits hi and lo (inclusive) and adjust it for the
 *  sign. This means that if sign = 1 (negative), you should return the 2's
 *  complement of the field. If sign = 0 (positive), you should return the field
 *  as-is. See the examples in the main instructions. This function will be
 *  very useful in P3 when you need to extract different parts of an IEEE
 *  number.
 *  @param value  the source value or bit pattern
 *  @param hi the bit position of the high end of the field. This parameter is
 *  guaranteed to be greater than or equal to lo.
 *  @param lo the bit position of the low end of the field. This parameter is
 *  guaranteed to be less than or equal to hi.
 *  @param sign 0 (positive) means we want the field as-is. 1 (negative) means
 *  we want the 2's complement of the field.
 *  @return The value of the field adjusted for the sign. See the examples in
 *  the main instructions.
 */
int getField (int value, int hi, int lo, bool isSigned);

#endif

