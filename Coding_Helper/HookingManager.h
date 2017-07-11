#include "stdafx.h"
#include "afxdialogex.h"


class HookingManager {
public:
	void CopyToClipboard(TCHAR *text, int size);
	void PasteClipboardText();
	void MessageHooking();
	void ConvertText(int convert_index);
};