#pragma once

#if defined SPL_PLATFORM_WINDOWS
#if defined SPL_DYNAMIC_LINK
	#ifdef SPL_BUILD_DLL
		#define SPOTLIGHT_API __declspec(dllexport)
	#else 
		#define	SPOTLIGHT_API __declspec(dllimport)
	#endif
#else
	#define SPOTLIGHT_API
#endif
#else
	#error This engine only supports Windows at the moment!
#endif

#ifdef SPL_DEBUG
	#define SPL_ENABLE_ASSERTS
#endif

#ifdef SPL_ENABLE_ASSERTS
	#define SPL_ASSERT(x, ...) if(!(x)) { SPL_FATAL("Assertion Failed! {0}", __VA_ARGS__); __debugbreak(); }
	#define SPL_CORE_ASSERT(x, ...) if(!(x)) { SPL_CORE_FATAL("Assertion Failed! {0}", __VA_ARGS__); __debugbreak(); }
#else
	#define SPL_ASSERT(x, ...) x;
	#define SPL_CORE_ASSERT(x, ...) x;
#endif

#define SPL_BIND_FUNC(func) std::bind(&func, this, std::placeholders::_1)