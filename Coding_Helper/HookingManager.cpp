#include "stdafx.h"
#include "HookingManager.h"

void HookingManager::MessageHooking() {
	TCHAR str[100];
	static HINSTANCE hinstDll;
	HOOKPROC hGetMsgProc;
	static HHOOK hKeyHook = NULL;
	int errnum;
	hinstDll = LoadLibrary(L"CodingHelperDLL64.dll");
	if (!hinstDll) {
		MessageBox(NULL, L"dll�ε� ����", L"error", MB_OK);
		ExitProcess(1);
	}
	hGetMsgProc = (HOOKPROC)GetProcAddress(hinstDll, "GetMsgProc");
	errnum = errno;
	if (!hGetMsgProc) {
		MessageBox(NULL, L"�Լ���  ã�� �� �����ϴ�", L"error", MB_OK);
		FreeLibrary(hinstDll);
		ExitProcess(1);
	}
	/*
	if (hKeyHook != NULL) {
		UnhookWindowsHookEx(hKeyHook);
		MessageBox(NULL, L"unhook ok", L"error", MB_OK);

	}*/
	hKeyHook = SetWindowsHookEx(WH_GETMESSAGE, hGetMsgProc, hinstDll, 0); //�޽��� ��ŷ, ��ŷ�ϴ� ���ν����� hGetMsgProc�Լ�, �Լ��� �ִ� dll, �۷ι� ��
	if (!hKeyHook) {
		MessageBox(NULL, L"Hooking�� �������� ���߽��ϴ�.", L"error", MB_OK);
		FreeLibrary(hinstDll);
		ExitProcess(1);
	}

	//DLL ejection�� ���� �κ�
	//UnhookWindowsHookEx(hKeyHook);

}

void HookingManager::PasteClipboardText() {
	//set up
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	//ALT UP
	ip.ki.wVk = VK_MENU;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

	//CTRL DOWN
	ip.ki.wVk = VK_CONTROL;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));

	//V Down
	ip.ki.wVk = 0x56;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));

	//V UP
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

	//CTRL UP
	ip.ki.wVk = VK_CONTROL;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

	MSG Message;

	while (!PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
		break;
	}


}

void HookingManager::CopyToClipboard(TCHAR *text, int size) {
	HGLOBAL hglobal = GlobalAlloc(GHND | GMEM_SHARE, (size + 1) * sizeof(TCHAR));
	LPTSTR pGlobal = (LPTSTR)GlobalLock(hglobal);
	memcpy(pGlobal, text, (size + 1) * sizeof(TCHAR));
	GlobalUnlock(hglobal);

	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_UNICODETEXT, hglobal);
	CloseClipboard();
}

void HookingManager::ConvertText(int convert_index) {
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	
	for (int i = 0; i < convert_index; i++) {
		//BACKSPACE Down
		ip.ki.wVk = VK_BACK;
		ip.ki.dwFlags = 0;
		SendInput(1, &ip, sizeof(INPUT));

		//BACKSPACE UP
		ip.ki.wVk = VK_BACK;
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
	}
	
	HookingManager::PasteClipboardText();
}