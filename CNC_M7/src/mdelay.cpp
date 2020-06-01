#include <mdelay.h>

void mdelay(uint32_t volatile t)
{
	while(t--){};
}

