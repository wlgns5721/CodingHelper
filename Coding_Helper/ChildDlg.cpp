// AddDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Coding_Helper.h"
#include "ChildDlg.h"
#include "afxdialogex.h"


// AddDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChildDlg, CDialogEx)

CChildDlg::CChildDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHILDDLG, pParent)
{

}

CChildDlg::~CChildDlg()
{
}

void CChildDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChildDlg, CDialogEx)
END_MESSAGE_MAP()


// AddDialog 메시지 처리기입니다.


BOOL CChildDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetDlgItemText(IDC_STATIC1, L"변환 대상 : ");
	SetDlgItemText(IDC_STATIC2, L"변환된 텍스트 : ");
	((CEdit*)GetDlgItem(IDC_EDIT1))->SetLimitText(32);
	((CEdit*)GetDlgItem(IDC_EDIT2))->SetLimitText(128);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CChildDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	GetDlgItemText(IDC_EDIT1, origin);
	GetDlgItemText(IDC_EDIT2, converted_text);

	CDialogEx::OnOK();
}
