#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG // Release build
    return "assets/";
#else 
    return "D:/Jzt/online course/Udemy/CPP game from scratch/LightYearsGame/LightYearsGame/assets/";
#endif
}
