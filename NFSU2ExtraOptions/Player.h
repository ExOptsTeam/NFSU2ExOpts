#include "stdio.h"
#include <windows.h>
#include "InGameFunctions.h"

int GetPOVTypeFromPlayerCamera(int a1)
{
	int result; // eax

	switch (a1)
	{
	case 0:
		result = 2;
		break;
	case 1:
		result = 4;
		break;
	case 2:
		result = 1;
		break;
	case 4:
		result = 5;
		break;
	case 5:
		result = 3;
		break;
	case 3:
	default:
		result = 0;
		break;
	}
	return result;
}