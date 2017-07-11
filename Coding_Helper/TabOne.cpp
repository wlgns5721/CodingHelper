// TabOne.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Coding_Helper.h"
#include "TabOne.h"
#include "afxdialogex.h"
#include "Coding_HelperDlg.h"
#include <string>
#include <vector>

using namespace std;


// TabOne 대화 상자입니다.

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


// TabOne 메시지 처리기입니다.




void TabOne::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
}

BOOL TabOne::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetDlgItemText(IDC_STATIC1, L"ALT + 1");
	SetDlgItemText(IDC_STATIC2, L"ALT + 2");
	SetDlgItemText(IDC_STATIC3, L"ALT + 3");
	SetDlgItemText(IDC_STATIC4, L"ALT + 4");
	SetDlgItemText(IDC_STATIC5, L"ALT + 5");
	SetDlgItemText(IDC_STATIC6, L"ALT + 6");

	SetDlgItemText(IDC_BUTTON1, L"커서 설정");
	SetDlgItemText(IDC_BUTTON2, L"커서 설정");
	SetDlgItemText(IDC_BUTTON3, L"커서 설정");
	SetDlgItemText(IDC_BUTTON4, L"커서 설정");
	SetDlgItemText(IDC_BUTTON5, L"커서 설정");
	SetDlgItemText(IDC_BUTTON6, L"커서 설정");
	SetDlgItemText(IDC_BUTTON7, L"Update");
	
	((CEdit*)GetDlgItem(IDC_EDIT1))->SetLimitText(MACRO_MAX_SIZE);
	((CEdit*)GetDlgItem(IDC_EDIT2))->SetLimitText(MACRO_MAX_SIZE);
	((CEdit*)GetDlgItem(IDC_EDIT3))->SetLimitText(MACRO_MAX_SIZE);
	((CEdit*)GetDlgItem(IDC_EDIT4))->SetLimitText(MACRO_MAX_SIZE);
	((CEdit*)GetDlgItem(IDC_EDIT5))->SetLimitText(MACRO_MAX_SIZE);
	((CEdit*)GetDlgItem(IDC_EDIT6))->SetLimitText(MACRO_MAX_SIZE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void TabOne::UpdateMacro() {
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	HANDLE hMemoryMap;
	LPBYTE pMemoryMap;
	

	//파일 매핑 커널 오브젝트 생성
	hMemoryMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, SHARED_MEMORY_SIZE, L"shared_memory");
	if (!hMemoryMap) {
		AfxMessageBox(L"file mapping object create fail!");
		return;
	}

	//프로세스의 공간상에 파일 매핑 오브젝트를 매핑
	pMemoryMap = (LPBYTE)MapViewOfFile(hMemoryMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (!pMemoryMap) {
		AfxMessageBox(L"mapping failed");
		return;
	}

	pMacroStruct = (MacroStruct*)pMemoryMap;

	//배열 초기화
	for (int i = 0; i < 6; i++) {
		memset(pMacroStruct->macroText[i], 0, 256 * sizeof(TCHAR));
		pMacroStruct->size[i] = 0;
	}

	//플래그 초기화
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateMacro();
	AfxMessageBox(L"적용되었습니다.");
}


