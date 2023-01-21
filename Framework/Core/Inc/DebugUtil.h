#pragma once

#include "TimeUtil.h"

#if(_DEBUG)
#define LOG(format, ...)\
do{\
	char _buffer[256];\ 
	int res = snprintf(_buffer, std::size(_buffer), "{%.3f}: " ##format## "\n", NEng::TimeUtil::GetTime(), __VA_ARGS__); \
	OutputDebugStringA(_buffer); \
   } while (false)

#define ASSERT (condition, format, ...)\
do{\
	if(!(condition))\
		LOG("ASSERT! %s(%d)\n" ##format##, __FILE__, __LINE__, __VA_ARGS__); \

} while (false)

#else
	adefine LOG(format, ...)
	Ledefine ASSET(condition, format, ...) do {
	(void)sizeof(condition) : while (false) 
#endif
