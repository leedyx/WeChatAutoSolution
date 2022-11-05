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


#define AUTO_DOWNLOAD_IMG_OFFSET 0x2255C08
#define CHANGE_VERSION_OFFSET 0x223d90c
#define LATEST_VERSION 1661468699

DWORD GetWeChatWinBase();
VOID ChangeVersion(DWORD latestVersion);
VOID AutoLoadImage();



