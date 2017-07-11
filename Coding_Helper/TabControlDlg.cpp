// TabControlDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Coding_Helper.h"
#include "TabControlDlg.h"
#include "afxdialogex.h"


// CTabControlDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTabControlDlg, CDialogEx)

CTabControlDlg::CTabControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CODING_HELPER_DIALOG, pParent)
{
}

CTabControlDlg::~CTabControlDlg()
{
}

void CTabControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabControlDlg, CDialogEx)
END_MESSAGE_MAP()


// CTabControlDlg 메시지 처리기입니다.
