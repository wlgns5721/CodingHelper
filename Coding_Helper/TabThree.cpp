// TabThree.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Coding_Helper.h"
#include "TabThree.h"
#include "afxdialogex.h"
#include "string"
#include "windef.h"
using namespace std;

// TabThree 대화 상자입니다.

IMPLEMENT_DYNAMIC(TabThree, CDialogEx)

TabThree::TabThree(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SUB3, pParent)
{

}

TabThree::~TabThree()
{
}


void TabThree::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
}


BEGIN_MESSAGE_MAP(TabThree, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &TabThree::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &TabThree::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &TabThree::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &TabThree::OnBnClickedButton4)
END_MESSAGE_MAP()


// TabThree 메시지 처리기입니다.


BOOL TabThree::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CString cs;
	SetDlgItemText(IDC_BUTTON1, L"찾아보기");
	SetDlgItemText(IDC_BUTTON2, L"찾아보기");
	SetDlgItemText(IDC_BUTTON3, L"찾아보기");
	SetDlgItemText(IDC_BUTTON4, L"단축키 변경");
	SetDlgItemText(IDC_BUTTON5, L"단축키 변경");
	SetDlgItemText(IDC_BUTTON6, L"단축키 변경");
	SetDlgItemText(IDC_STATIC1, L"ALT + 8");
	SetDlgItemText(IDC_STATIC2, L"ALT + 9");
	SetDlgItemText(IDC_STATIC3, L"ALT + 0");
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void TabThree::ExecuteFile(int index) {
	CString cs;
	GetDlgItemText(IDC_EDIT1 + index, cs);
	TCHAR  *tchr = (TCHAR*)(LPCTSTR)cs;
	Invalidate();
	if (!cs.Compare(L""))
		return;
	if(cs.Find(L"://")!=-1)
		ShellExecute(NULL, L"open", L"chrome",tchr, NULL, SW_SHOW);
	else
		ShellExecute(NULL, L"open", tchr, NULL, NULL, SW_SHOW);
}

void TabThree::SelectFile(int index) {
	TCHAR current_path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, current_path);
	CFileDialog FileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"", this);
	FileDialog.m_ofn.lpstrTitle = L"파일을 선택하라구 Boy~";
	if (FileDialog.DoModal() == IDOK) {
		CString path = FileDialog.GetPathName();
		SetDlgItemText(IDC_EDIT1 + index, path);
		
	}
	
	SetCurrentDirectory(current_path);

}

void TabThree::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SelectFile(0);
}


void TabThree::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SelectFile(1);
}


void TabThree::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SelectFile(2);
}


void TabThree::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
}
