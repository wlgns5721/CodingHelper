// TabThree.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Coding_Helper.h"
#include "TabThree.h"
#include "afxdialogex.h"
#include "string"
#include "windef.h"
using namespace std;

// TabThree ��ȭ �����Դϴ�.

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


// TabThree �޽��� ó�����Դϴ�.


BOOL TabThree::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CString cs;
	SetDlgItemText(IDC_BUTTON1, L"ã�ƺ���");
	SetDlgItemText(IDC_BUTTON2, L"ã�ƺ���");
	SetDlgItemText(IDC_BUTTON3, L"ã�ƺ���");
	SetDlgItemText(IDC_BUTTON4, L"����Ű ����");
	SetDlgItemText(IDC_BUTTON5, L"����Ű ����");
	SetDlgItemText(IDC_BUTTON6, L"����Ű ����");
	SetDlgItemText(IDC_STATIC1, L"ALT + 8");
	SetDlgItemText(IDC_STATIC2, L"ALT + 9");
	SetDlgItemText(IDC_STATIC3, L"ALT + 0");
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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
	FileDialog.m_ofn.lpstrTitle = L"������ �����϶� Boy~";
	if (FileDialog.DoModal() == IDOK) {
		CString path = FileDialog.GetPathName();
		SetDlgItemText(IDC_EDIT1 + index, path);
		
	}
	
	SetCurrentDirectory(current_path);

}

void TabThree::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SelectFile(0);
}


void TabThree::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SelectFile(1);
}


void TabThree::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SelectFile(2);
}


void TabThree::OnBnClickedButton4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
}
