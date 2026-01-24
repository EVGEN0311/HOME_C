#include "stdio.h"
#include "inttypes.h"

uint32_t N = 0;
uint32_t K = 0;

int main()
{
	scanf("%" SCNu32, &N);
	scanf("%" SCNu32, &K);
	for(uint32_t i = 0; i < K; i++ )
	{
		N = (N >> 1) | (N << 31);
	}
	
	printf("%" PRIu32, N);
}
