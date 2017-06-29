#include "types.h"
#include "constants.h"
#include "intrinsics.h"
#include "natives.h"
#include "common.h"

void main()
{
	while (true)
	{
		print("Hello World", 1000);
		WAIT(0);
	}
}
