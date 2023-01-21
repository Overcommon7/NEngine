#include "Precompiled.h"
#include "TimeUtil.h"


namespace NEng
{
	float TimeUtil::GetTime()
	{
		// get the difference in time since the start of the app
		static const auto startTime = std::chrono::high_resolution_clock::now();
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds> (currentTime - startTime).count();
		return milliseconds / 1000.0f;
	}

	float TimeUtil::GetDeltaTime()
	{
		// get the difference since the last time we checked
		static auto lastCallTime = std::chrono::high_resolution_clock::now();
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastCallTime).count();
		lastCallTime = currentTime;
		return milliseconds / 1000.0f;
	}
}

