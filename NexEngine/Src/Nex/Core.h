#ifndef CORE_H_
#define CORE_H_

#ifdef NEX_PLATFORM_WINDOWS
	#ifdef NEX_BUILD_DLL
		#define NEX_API _declspec(dllexport)
	#else
		#define NEX_API _declspec(dllimport)
	#endif // NEX_BUILD_DLL
#else
	#error Nex only supports windows
#endif // NEX_PLATFORM_WINDOWS

#define BIT(x) (1 << x)
#endif // !CORE_H_
