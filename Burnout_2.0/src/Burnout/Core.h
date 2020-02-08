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



#ifdef BO_ENABLE_ASSERTS
	#define BO_ASSERT(x, ...) {if(!x)) {BO_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define BO_CORE_ASSERT(x, ...) {if(!(x)) { BO_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define BO_ASSERT(x, ...)
	#define BO_CORE_ASSERT(x, ...)
#endif



#define BIT(x) (1 << x)