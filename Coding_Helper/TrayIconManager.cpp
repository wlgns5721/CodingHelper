#include "stdafx.h"
#include "TrayIconManager.h"
#include "afxdialogex.h"
#include "Winuser.h"


void CTrayIconManager::MakePopUpMenu(HWND hWnd, int x, int y) {
	HMENU hMenu = CreatePopupMenu();   //메뉴 생성
	AppendMenu(hMenu, MF_STRING, ACTIVE_MESSAGE, L"프로그램 활성화");   //팝업 메뉴 구성
	AppendMenu(hMenu, MF_STRING, EXIT_MESSAGE, L"종료");    //팝업 메뉴 구성
	SetForegroundWindow(hWnd);     //팝업 메뉴 바깥을 눌렀을 때 팝업메뉴 닫기
	TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON, x, y, 0, hWnd, NULL);     //팝업 메뉴 띄우기

}