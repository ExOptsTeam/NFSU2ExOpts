#include "stdio.h"
#include <windows.h>
#include "InGameFunctions.h"

bool __stdcall UIQRTrackSelect_IsAvailable(int TrackInfoBlock, int eTrackDirection)
{
	__int16 TrackID;

	if (!TrackInfoBlock) return 0; // If block failed to load

	TrackID = *(WORD*)(TrackInfoBlock + 138);

	if (TrackID == 1001 || TrackID == 1002 || TrackID == 1003 || TrackID == 1099 || TrackID == 1102 || TrackID == 3001
		|| TrackID == 4200 || TrackID == 4300 || TrackID == 4400 || TrackID == 4600 || TrackID == 4700 || TrackID == 4800 || TrackID == 4900) return 0; // If one of crashy tracks

	return 1; // For all other races
}