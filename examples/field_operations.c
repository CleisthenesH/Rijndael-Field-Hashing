// Copyright 2023 Kieran W Harvie. All rights reserved.

/* This example demonstrates, displays, and verifies the results of basic Rijndael field operations.
 *
 * After completing basic operations it verifies Frobenius's automorphism for the Rijndael field.
 */

#include <stdio.h>
#include "field_operations.h"

// Pretty print comparing candidate to ref
static void pass(uint8_t candidate, uint8_t ref)
{
	if(candidate == ref)
		printf("(Passed)\n");
	else
		printf("(Failed, should equal %02X)\n",ref);
}

void main()
{
	/* Define three operands.
	 * They correspond to GF(2)[X] polynomials:
	 * 	X^5+X+1, X^6+X, and X^2+1 
	 */
	uint8_t a = 0b00010011;
	uint8_t b = 0b01000010;
	uint8_t c = 0b00000101;

	// Display operands.
	printf("Example Operands:\n\ta=%02X\n\tb=%02X\n\tc=%02X\n",a,b,c);

	// Calculate addition.
	uint8_t add_1 = gadd(a,b);
	uint8_t add_2 = gadd(a,c);
	uint8_t add_3 = gadd(b,c);

	// Display addition.
	printf("\nExample Addition:\n");

	printf("\ta+b=%02X\t", add_1);
	pass(add_1, 0b01010001);
	printf("\ta+c=%02X\t", add_2);
	pass(add_2, 0b00010110);
	printf("\tb+c=%02X\t", add_3);
	pass(add_3, 0b01000111);

	// Calculate multiplication.
	uint8_t mul_1 = gmul(a,b);
	uint8_t mul_2 = gmul(a,c);
	uint8_t mul_3 = gmul(b,c);

	// Display multiplication.
	printf("\nExample Multiplication:\n");

	printf("\ta*b=%02X\t",mul_1);
	pass(mul_1,0x8A);
	printf("\ta*c=%02X\t",mul_2);
	pass(mul_2,0x5F);
	printf("\tb*c=%02X\t",mul_3);
	pass(mul_3,0x51);

	// Calculate inverse.
	uint8_t inv_1 = ginv(a);
	uint8_t inv_2 = ginv(b);
	uint8_t inv_3 = ginv(c);

	// Display inverse.
	printf("\nExample Inverse:\n");

	printf("\ta^(-1)=%02X\t",inv_1);
	pass(inv_1,0x4B);
	printf("\tb^(-1)=%02X\t",inv_2);
	pass(inv_2,0x37);
	printf("\tc^(-1)=%02X\t",inv_3);
	pass(inv_3,0x52);

	// Calculate index.
	uint8_t idx_1 = gindex[a];
	uint8_t idx_2 = gindex[b];
	uint8_t idx_3 = gindex[c];

	// Display index.
	printf("\nExample Index:\n");

	printf("\ta=02^(%02X)\t",idx_1);
	pass(idx_1,0x0E);
	printf("\tb=02^(%02X)\t",idx_2);
	pass(idx_2,0xDB);
	printf("\tc=02^(%02X)\t",idx_3);
	pass(idx_3,0x02);

	// Calculate powers.
	uint8_t pwr_1 = gpower[a];
	uint8_t pwr_2 = gpower[b];
	uint8_t pwr_3 = gpower[c];

	// Display powers.
	printf("\nExample Powers:\n");

	printf("\t02^a=%02X\t",pwr_1);
	pass(pwr_1,0x48);
	printf("\t02^b=%02X\t",pwr_2);
	pass(pwr_2,0x67);
	printf("\t02^c=%02X\t",pwr_3);
	pass(pwr_3,0x33);

	// Calculate Frobenius.
	uint8_t RHS = gadd(gmul(a,a),gmul(b,b));
	uint8_t LHS = gmul(gadd(a,b),gadd(a,b));

	// Display Frobenius.
	printf("\nExample Frobenius:\n");
	printf("\ta^2+b^2=%02X\n\t(a+b)^2=%02X\n",LHS,RHS);
	printf("\t(a+b)^2=a^2+b^2\t");
	pass(LHS,RHS);
}
