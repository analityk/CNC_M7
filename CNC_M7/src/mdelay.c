#include <mdelay.h>

#ifdef __cplusplus
extern "C" {
#endif


void mdelay(uint32_t volatile t)
{
	while(t){t--;};
};

#ifdef __cplusplus
}
#endif