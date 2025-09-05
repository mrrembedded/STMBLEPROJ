#include "user_utils.h"


void convert_float_to_byte_array(float var, uint8_t * buffer)
{
		uint8_t i;
		memcpy(buffer, &var, 4);
}

void convert_byte_array_to_float(uint8_t * buffer ,float *var)
{
		float var1;
		memcpy(&var1, buffer, sizeof(var1));
		*var = var1;
}
