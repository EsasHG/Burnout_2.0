#pragma once

#include <memory>

#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x86 */
		#define BO_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define BO_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define BO_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif

	 /* We also have to check __ANDROID__ before __linux__
	  * since android is based on the linux kernel
	  * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define BO_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define BO_PLATFORM_LINUX
	#error "Linux is not supported!"
#else	
	#error "Unknown platform!"
#endif // End of platform detection




// DLL support
#ifdef BO_PLATFORM_WINDOWS
	#if BO_DYNAMIC_LINK
		#ifdef BP_BUILD_DLL
			#define BURNOUT_API __declspec(dllexport)	
		#else
			#define BURNOUT_API __declspec(dllimport)
		#endif
	#else
		#define BURNOUT_API
	#endif
#else	
	#error Bornout only supports Windows!
#endif // End of DLL support




#ifdef BO_DEBUG
	#define BO_ENABLE_ASSERTS
#endif // !BO_DEBUG



#ifdef BO_ENABLE_ASSERTS
	#define BO_ASSERT(x, ...) {if(!x)) {BO_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define BO_CORE_ASSERT(x, ...) {if(!(x)) { BO_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define BO_ASSERT(x, ...)
	#define BO_CORE_ASSERT(x, ...)
#endif

//#define BO_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define BO_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) {return this->fn(std::forward<decltype(args)>(args)...);}


#define BIT(x) (1 << x)


namespace Burnout
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

}