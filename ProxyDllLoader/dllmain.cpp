#include <Windows.h>
#include "dll_proxy.h"
#include "dll_loader.h"

DWORD WINAPI _dll_main(LPVOID lpParam)
{
	__load_dll__();
	FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(lpParam), NULL);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		if(__load_proxy__()) { CreateThread(nullptr, NULL, _dll_main, hModule, NULL, nullptr); }
		else 
		{ 
			MessageBox(NULL, L"Error while loading Proxy DLL.", L"Error.", MB_ICONERROR);
		}
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}