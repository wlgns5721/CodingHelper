#include "stdafx.h"
#include "TrayIconManager.h"
#include "afxdialogex.h"
#include "Winuser.h"


void CTrayIconManager::MakePopUpMenu(HWND hWnd, int x, int y) {
	HMENU hMenu = CreatePopupMenu();   //�޴� ����
	AppendMenu(hMenu, MF_STRING, ACTIVE_MESSAGE, L"���α׷� Ȱ��ȭ");   //�˾� �޴� ����
	AppendMenu(hMenu, MF_STRING, EXIT_MESSAGE, L"����");    //�˾� �޴� ����
	SetForegroundWindow(hWnd);     //�˾� �޴� �ٱ��� ������ �� �˾��޴� �ݱ�
	TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON, x, y, 0, hWnd, NULL);     //�˾� �޴� ����

}