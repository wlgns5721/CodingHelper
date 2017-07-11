// TabOne.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Coding_Helper.h"
#include "TabOne.h"
#include "afxdialogex.h"
#include "Coding_HelperDlg.h"
#include <string>
#include <vector>

using namespace std;


// TabOne ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(TabOne, CDialogEx)

TabOne::TabOne(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CODING_HELPER_DIALOG, pParent)
{
	
}

TabOne::~TabOne()
{
}

void TabOne::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TabOne, CDialogEx)
	
	ON_BN_CLICKED(IDC_BUTTON1, &TabOne::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON7, &TabOne::OnBnClickedButton7)
END_MESSAGE_MAP()


// TabOne �޽��� ó�����Դϴ�.




void TabOne::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
}

BOOL TabOne::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetDlgItemText(IDC_STATIC1, L"ALT + 1");
	SetDlgItemText(IDC_STATIC2, L"ALT + 2");
	SetDlgItemText(IDC_STATIC3, L"ALT + 3");
	SetDlgItemText(IDC_STATIC4, L"ALT + 4");
	SetDlgItemText(IDC_STATIC5, L"ALT + 5");
	SetDlgItemText(IDC_STATIC6, L"ALT + 6");

	SetDlgItemText(IDC_BUTTON1, L"Ŀ�� ����");
	SetDlgItemText(IDC_BUTTON2, L"Ŀ�� ����");
	SetDlgItemText(IDC_BUTTON3, L"Ŀ�� ����");
	SetDlgItemText(IDC_BUTTON4, L"Ŀ�� ����");
	SetDlgItemText(IDC_BUTTON5, L"Ŀ�� ����");
	SetDlgItemText(IDC_BUTTON6, L"Ŀ�� ����");
	SetDlgItemText(IDC_BUTTON7, L"Update");
	
	((CEdit*)GetDlgItem(IDC_EDIT1))->SetLimitText(MACRO_MAX_SIZE);
	((CEdit*)GetDlgItem(IDC_EDIT2))->SetLimitText(MACRO_MAX_SIZE);
	((CEdit*)GetDlgItem(IDC_EDIT3))->SetLimitText(MACRO_MAX_SIZE);
	((CEdit*)GetDlgItem(IDC_EDIT4))->SetLimitText(MACRO_MAX_SIZE);
	((CEdit*)GetDlgItem(IDC_EDIT5))->SetLimitText(MACRO_MAX_SIZE);
	((CEdit*)GetDlgItem(IDC_EDIT6))->SetLimitText(MACRO_MAX_SIZE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void TabOne::UpdateMacro() {
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	HANDLE hMemoryMap;
	LPBYTE pMemoryMap;
	

	//���� ���� Ŀ�� ������Ʈ ����
	hMemoryMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, SHARED_MEMORY_SIZE, L"shared_memory");
	if (!hMemoryMap) {
		AfxMessageBox(L"file mapping object create fail!");
		return;
	}

	//���μ����� ������ ���� ���� ������Ʈ�� ����
	pMemoryMap = (LPBYTE)MapViewOfFile(hMemoryMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (!pMemoryMap) {
		AfxMessageBox(L"mapping failed");
		return;
	}

	pMacroStruct = (MacroStruct*)pMemoryMap;

	//�迭 �ʱ�ȭ
	for (int i = 0; i < 6; i++) {
		memset(pMacroStruct->macroText[i], 0, 256 * sizeof(TCHAR));
		pMacroStruct->size[i] = 0;
	}

	//�÷��� �ʱ�ȭ
	pMacroStruct->isPressButton = false;

	for (int i = 0; i < 6; i++) {
		CString Ctext;
		GetDlgItemText(IDC_EDIT1 + i, Ctext);
		int size = Ctext.GetLength();
		char* text = LPSTR(LPCTSTR(Ctext));
		memcpy(&(pMacroStruct->macroText[i]), text, sizeof(TCHAR)*size);
		pMacroStruct->size[i] = size;
		//memcpy(&(tempMacroStruct.macroTextVector[i]), &text,sizeof(string));
		//tempMacroStruct.macroTextVector.push_back(text);
	}

	

}



void TabOne::OnBnClickedButton7()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateMacro();
	AfxMessageBox(L"����Ǿ����ϴ�.");
}


