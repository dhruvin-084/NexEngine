#ifndef CORE_H_
#define CORE_H_


#ifdef NEX_PLATFORM_WINDOWS
	#ifdef NEX_DYNEMIC_BUILD
		#ifdef NEX_BUILD_DLL
			#define NEX_API _declspec(dllexport)
		#else
			#define NEX_API _declspec(dllimport)
		#endif // NEX_BUILD_DLL
	#else
		#define NEX_API
	#endif
#else
	#error Nex only supports windows
#endif // NEX_PLATFORM_WINDOWS

#ifdef NEX_DEBUG
	#define NEX_ENABLE_ASSERTS
#endif

#ifdef NEX_ENABLE_ASSERTS
	#define NEX_ASSERT(x, ...) {if(!x) {NEX_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak();}}
	#define NEX_CORE_ASSERT(x, ...) {if(!x) {NEX_CORE_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define NEX_ASSERT(x, ...)
	#define NEX_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define NEX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#endif // !CORE_H_
