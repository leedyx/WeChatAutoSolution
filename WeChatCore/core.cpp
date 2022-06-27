#include "core.h"


DWORD GetWeChatWinBase() {
	return (DWORD)GetModuleHandleA("WeChatWin.dll");
}

DWORD jmpBackAddress = 0;

VOID SaveDuiLibXML(BYTE* xmlData, DWORD xmlSize, WCHAR* xmlPathFileName)
{
	std::wstring filepath = L"D:\\WeChatDuiLibXMLFile";
	if (!PathIsDirectory(filepath.c_str()))
	{
		CreateDirectory(filepath.c_str(), NULL);
	}

	std::wstring wsXmlPathFileName = xmlPathFileName;
	int index = wsXmlPathFileName.find(L"/");
	if (index < 0) index = wsXmlPathFileName.find(L"\\");

	if (index > 0)
	{
		std::wstring wsXmlPath = wsXmlPathFileName.substr(0, index);
		filepath += L"\\" + wsXmlPath;
		if (!PathIsDirectory(filepath.c_str()))
		{
			CreateDirectory(filepath.c_str(), NULL);
		}
	}

	std::wstring wsXmlFileName = wsXmlPathFileName.substr(index + 1);
	filepath += L"\\" + wsXmlFileName;

	OutputDebugString(filepath.c_str());

	HANDLE hFile = CreateFile(filepath.c_str(),
		GENERIC_WRITE, 0, NULL,
		CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);

	DWORD dwBytesWriten = 0;
	WriteFile(hFile, xmlData, xmlSize * 2, &dwBytesWriten, NULL);

	CloseHandle(hFile);
}

__declspec(naked) VOID ListenDuiLibXML()
{
	_asm
	{
		mov ebx, dword ptr ss : [ebp - 0x4];
		xor ecx, ecx;

		pushfd;
		pushad;

		mov eax, [ebp];
		push[eax + 0x8];
		push edx;
		push[ebx];
		call SaveDuiLibXML;
		add esp, 0xC;

		popad
			popfd

			jmp jmpBackAddress
	}
}

/*
* 对任意地址添加HOOK
* dwHookAddr：HOOK的目标地址
* dwJmpAddress：跳转到的地址
* originalRecieveCode：保存旧指令的数组
* return：void
*/
void HookAnyAddress(DWORD dwHookAddr, LPVOID dwJmpAddress, char* originalRecieveCode)
{
	//组装跳转数据
	BYTE jmpCode[5] = { 0 };
	jmpCode[0] = 0xE9;

	//计算偏移
	*(DWORD*)&jmpCode[1] = (DWORD)dwJmpAddress - dwHookAddr - 5;

	// 保存以前的属性用于还原
	DWORD OldProtext = 0;

	// 因为要往代码段写入数据，又因为代码段是不可写的，所以需要修改属性
	VirtualProtect((LPVOID)dwHookAddr, 5, PAGE_EXECUTE_READWRITE, &OldProtext);
	ReadProcessMemory(GetCurrentProcess(), (LPVOID)dwHookAddr, originalRecieveCode, 5, 0);

	//写入自己的代码
	memcpy((void*)dwHookAddr, jmpCode, 5);

	// 执行完了操作之后需要进行还原
	VirtualProtect((LPVOID)dwHookAddr, 5, OldProtext, &OldProtext);
}

/*
* 对任意地址取消HOOK
* dwHookAddr：HOOK的目标地址
* originalRecieveCode：保存旧指令的数组
* return：void
*/
void UnHookAnyAddress(DWORD dwHookAddr, char* originalRecieveCode)
{
	DWORD OldProtext = 0;
	VirtualProtect((LPVOID)dwHookAddr, 5, PAGE_EXECUTE_READWRITE, &OldProtext);
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)dwHookAddr, originalRecieveCode, 5, 0);
	VirtualProtect((LPVOID)dwHookAddr, 5, OldProtext, &OldProtext);
}