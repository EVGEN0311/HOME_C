#include "stdio.h"
#include "inttypes.h"

uint32_t N = 0;
uint32_t K = 0;
uint32_t result = 0;


int main()
{
	scanf("%" SCNu32, &N);
	scanf("%" SCNu32, &K);
	
	
	for(uint32_t i = 0; i < K; i++ )
	{
		if((N >> i) & 1u)
		result |= (1u << i);
	}
	N = result;
	printf("%" PRIu32, N);
}

