#include "core.h"


DWORD GetWeChatWinBase() {
	return (DWORD)GetModuleHandleA("WeChatWin.dll");
}

VOID ChangeVersion(DWORD latestVersion) {
	
	DWORD base = GetWeChatWinBase();
	LPDWORD address = (LPDWORD)(base + CHANGE_VERSION_OFFSET);
	*(DWORD*)address = latestVersion;

}

VOID AutoLoadImage() {	
	char settime[] = "00:00-00:00";
	DWORD AutoDownloadTimeSettingAddr = GetWeChatWinBase() + AUTO_DOWNLOAD_IMG_OFFSET;
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)AutoDownloadTimeSettingAddr, settime, strlen(settime) + 1, 0);

}