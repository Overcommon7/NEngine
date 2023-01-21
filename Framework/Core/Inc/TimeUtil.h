#pragma once

namespace NEng
{
    class TimeUtil
    {
    public:
        TimeUtil() = delete;
        TimeUtil(const TimeUtil& t) = delete;
        TimeUtil& operator=(const TimeUtil& t) = delete;

        static float GetTime();
        static float GetDeltaTime();
    };
}
