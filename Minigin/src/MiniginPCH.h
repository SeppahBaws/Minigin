#pragma once

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <vector>
#include <unordered_map>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// Helpers
template<typename T>
void SafeDelete(T* ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}
