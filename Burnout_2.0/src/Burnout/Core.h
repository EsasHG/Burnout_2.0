#pragma once

#ifdef BO_PLATFORM_WINDOWS
	#ifdef BO_BUILD_DLL
		#define BURNOUT_API __declspec(dllexport)
	#else
		#define BURNOUT_API __declspec(dllimport)
	#endif // BO_BUILD_DLL
#else
	#error Burnout only supports windows!
#endif // BO_PLATFORM_WINDOWS
