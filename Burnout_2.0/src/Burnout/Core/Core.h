#pragma once

#include <memory>

#ifdef BO_PLATFORM_WINDOWS
	#if BO_DYNAMIC_LINK
		#ifdef BO_BUILD_DLL
			#define BURNOUT_API __declspec(dllexport)
		#else
			#define BURNOUT_API __declspec(dllimport)
		#endif // BO_BUILD_DLL
	#else
		#define BURNOUT_API

#endif
#else
	#error Burnout only supports windows!
#endif // BO_PLATFORM_WINDOWS

#ifdef BO_DEBUG
	#define BO_ENABLE_ASSERTS
#endif // !BO_DEBUG



#if BO_ENABLE_ASSERTS
	#define BO_ASSERT(x, ...) {if(!x)) {BO_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define BO_CORE_ASSERT(x, ...) {if(!(x)) { BO_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define BO_ASSERT(x, ...)
	#define BO_CORE_ASSERT(x, ...)
#endif

#define BO_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)



#define BIT(x) (1 << x)


namespace Burnout
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	
	template<typename T>
	using Ref = std::shared_ptr<T>;
}