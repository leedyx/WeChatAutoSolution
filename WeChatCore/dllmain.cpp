#include "pch.h"
#include "core.h"

// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣

#include "pch.h"
#include <Windows.h>

VOID DoAction();

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		//##########################################################
		//
		//ע�⣺������PC΢��2.6.7.57�汾�������汾������
		//
		//##########################################################
		HANDLE hANDLE = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)DoAction, NULL, NULL, 0);
		if (hANDLE != 0)
		{
			CloseHandle(hANDLE);
		}
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

VOID DoAction() {
	AutoLoadImage();
	ChangeVersion(LATEST_VERSION);

}