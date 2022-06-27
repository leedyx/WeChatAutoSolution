#pragma once

#include "pch.h"
#include<string>
#include <SHLWAPI.H>
#pragma comment(lib, "Shlwapi.lib")


struct WxString
{
	wchar_t buf;
	DWORD len;
	DWORD maxLength;
	DWORD field1;
	DWORD field2;

};

DWORD GetWeChatWinBase();



