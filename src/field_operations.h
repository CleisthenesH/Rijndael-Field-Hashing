// Copyright 2023 Kieran W Harvie. All rights reserved.

#ifndef FIELD_OPERATIONS_GUAD
#define FIELD_OPERATIONS_GUAD

#include <stdint.h>
#include <stdio.h>

extern const uint8_t gindex[256];
extern const uint8_t gpower[256];

static uint8_t inline gadd(uint8_t a, uint8_t b)
{
	return a ^ b;
}

static uint8_t inline gmul(uint8_t a, uint8_t b)
{
	if (a == 0 || b == 0)
		return 0;

	uint16_t sum = gindex[a] + gindex[b];

	if (sum > 255)
		sum -= 255;

	return gpower[sum];
}

static uint8_t inline ginv(uint8_t a)
{
	return gpower[gindex[1] - gindex[a]];
}

#endif
