#pragma once

#include <memory>

// PLATFORM SELECTION /////////////////////////////////////
// WINDOWS (64-BIT)
#ifdef _WIN32
	#ifdef _WIN64
		#define SPL_PLATFORM_WINDOWS
	#else
		#error "32-bit Windows is not supported!"
	#endif
// APPLE (IPHONE & MACOS)
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "Target iPhone simulator not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define SPL_PLATFORM_IOS
		#error "iOS is not supported!"
	#elif TARGET_OS_MAC
		#define SPL_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#endif
// ANDROID
#elif defined(__ANDROID__)
	#define SPL_PLATFORM_ANDROID
	#error "Android is not supported!"
// LINUX
#elif defined(__linux__)
	#define SPL_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	#error "Unknown platform!"
#endif // PLATFORM SELECTION //////////////////////////////

// DLL SUPPORT ////////////////////////////////////////////
#ifdef SPL_PLATFORM_WINDOWS
	#ifdef SPL_DYNAMIC_LINK
		#ifdef SPL_BUILD_DLL
			#define SPOTLIGHT_API _declspec(dllexport)
		#else
			#define SPOTLIGHT_API _declspec(dllimport)
		#endif
	#else
		#define SPOTLIGHT_API
	#endif
#else
	#error "Spotlight only currently supports Windows!"
#endif // DLL SUPPORT /////////////////////////////////////

// BUILD CONFIGURATIONS ///////////////////////////////////
#ifdef SPL_DEBUG
	#define SPL_ENABLE_ASSERTS
#endif // BUILD CONFIGURATIONS ////////////////////////////

// Use to assert a statement and whenever proven false will break the debug session.
#ifdef SPL_ENABLE_ASSERTS
	#define SPL_ASSERT(x, ...) if(!(x)) { SPL_FATAL("Assertion Failed! {0}", __VA_ARGS__); __debugbreak(); }
	#define SPL_CORE_ASSERT(x, ...) if(!(x)) { SPL_CORE_FATAL("Assertion Failed! {0}", __VA_ARGS__); __debugbreak(); }
#else
	#define SPL_ASSERT(x, ...)
	#define SPL_CORE_ASSERT(x, ...)
#endif

// For use of pointing functions for std::function variable
#define SPL_BIND_FUNC(func) std::bind(&func, this, std::placeholders::_1)

namespace Spotlight
{

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
	
}