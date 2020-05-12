#pragma once
#include "stdafx.h"
#define BONE_HEAD_ID (66)

namespace Core {
	extern bool NoSpread;
	extern PVOID LocalPlayerPawn;
	extern PVOID LocalPlayerController;
	extern PVOID TargetPawn;
	extern PVOID(*ProcessEvent)(PVOID, PVOID, PVOID, PVOID);
	BOOLEAN GetTargetHead(FVector& out);
	extern bool debugshitaf3ai;
	extern float x;
	extern float y;
	extern float z;
	extern unsigned long long events;
	extern float fara;
	extern float neara;
	extern float widtha;
	BOOLEAN Initialize();
}