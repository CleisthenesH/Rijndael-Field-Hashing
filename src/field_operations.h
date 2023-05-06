#prama once

#include <stdint.h>

const uint8_t index[];
const uint8_t power[];

static uint8_t inline gadd(uint8_t a, uint8_t b)
{
	return a ^ b;
}

static uint8_t inline gmul(uint8_t a, uint8_t b)
{
	if (a == 0 || b == 0)
		return 0;

	uint16_t sum = index[a] + index[b];

	if (sum > 255)
		sum -= 255;

	return power[sum];
}

static uint8_t inline ginv(uint8_t a)
{
	return power[index[1] - index[a]];
}
