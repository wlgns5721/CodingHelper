// TabFour.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Coding_Helper.h"
#include "TabFour.h"
#include "afxdialogex.h"
#include "string"
#include "HookingManager.h"

// TabFour 대화 상자입니다.

IMPLEMENT_DYNAMIC(TabFour, CDialog)

TabFour::TabFour(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SUB4, pParent)
{

}

TabFour::~TabFour()
{
}

void TabFour::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT3, m_richedit);
	DDX_Control(pDX, IDC_LIST2, m_list);
}


BEGIN_MESSAGE_MAP(TabFour, CDialog)
	ON_EN_CHANGE(IDC_EDIT3, &TabFour::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON1, &TabFour::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &TabFour::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &TabFour::OnBnClickedButton3)
END_MESSAGE_MAP()


// TabFour 메시지 처리기입니다.


BOOL TabFour::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetDlgItemText(IDC_STATIC1, L"가상 키 변환");
	SetDlgItemText(IDC_STATIC2, L"ASCII 변환");
	SetDlgItemText(IDC_BUTTON1, L"Add");
	SetDlgItemText(IDC_BUTTON2, L"Remove");
	SetDlgItemText(IDC_BUTTON3, L"Update");
	
	
	m_richedit.SetEventMask(m_richedit.GetEventMask() | ENM_CHANGE);
	
	m_list.InsertColumn(0, L"target", LVCFMT_LEFT, 140, -1);
	m_list.InsertColumn(1, L"converted", LVCFMT_LEFT, 140, -1);
	
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	UpdateInfo();

	InitBuffer();
	
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL TabFour::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	int currentFocus;
	short keyname = 0;
	if (GetFocus() != NULL)
		currentFocus = GetFocus()->GetDlgCtrlID();
	else
		return 1;
	if (currentFocus == IDC_EDIT1) {
		CString result = L"";
		TCHAR* message;

		int virtual_key = pMsg->wParam;
		if (virtual_key == 0xe5) {
			SetDlgItemText(IDC_EDIT1, L"");
			SetDlgItemText(IDC_EDIT2, L"영문 키로 전환해 주세요");
			return CDialog::PreTranslateMessage(pMsg);
		}
		switch (pMsg->message) {
		case WM_CHAR:
			message = L"WM_CHAR";
			keyname = VkKeyScan(virtual_key);
			break;
			
		case WM_SYSCHAR:
			message = L"WM_SYSCHAR";
			break;
		case WM_KEYDOWN:
			message = L"WM_KEYDOWN";
			break;
		default:
			return 0;
		}

		result.Format(L"message : %s  , virtual key : 0x%x ",message,virtual_key);
		SetDlgItemText(IDC_EDIT1, L"");
		SetDlgItemText(IDC_EDIT2,result);
		if (virtual_key == VK_TAB)
			return 1;
		
	}
	
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}


void TabFour::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString original;
	CString conversed = L"";
	CString result = L"";
	GetDlgItemText(IDC_EDIT3, original);
	for (int i = 0; i < original.GetLength(); i++) {
		conversed.Format(L"0x%x ", original[i]);
		result += conversed;
	}
	SetDlgItemText(IDC_EDIT4, result);
}

//새로운 정보를 추가하는 창을 띄운다.
void TabFour::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString origin, converted_text;
	if (childDlg.DoModal() == IDOK) {
		int row = m_list.GetItemCount();
		origin = childDlg.origin;
		converted_text = childDlg.converted_text;
		if (origin_vec.size() >= 10)
			AfxMessageBox(L"최대 10개 까지 등록 가능합니다. ");
		else {
			m_list.InsertItem(row, origin);
			m_list.SetItem(row, 1, LVIF_TEXT, converted_text, 0, 0, 0, NULL);
			origin_vec.push_back(origin);
			converted_vec.push_back(converted_text);
		}
	}
	

	childDlg.DestroyWindow();
}


//선택된 행을 삭제한다.
void TabFour::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_list.GetSelectionMark();
	m_list.DeleteItem(index);

	if (!m_list.GetItemCount()) { //리스트에 아무것도 없을 벡터에서 element를 삭제한 후경우 리턴한다.
		vector<CString>::iterator it = origin_vec.begin();
		it += index;
		origin_vec.erase(it);
	
		it = converted_vec.begin();
		it += index;
		converted_vec.erase(it);

		return;
	}
		
	else if (m_list.GetItemCount() - 1 < index)  //맨 마지막 요소를 삭제할 경우 인덱스를 1 뺀다.
		index--;
	
	
	m_list.SetSelectionMark(index);
	vector<CString>::iterator it = origin_vec.begin();
	it += index;
	origin_vec.erase(it);

	it = converted_vec.begin();
	it += index;
	converted_vec.erase(it);

	m_list.SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	m_list.SetFocus();
}

void TabFour::UpdateInfo() {
	HANDLE hMemoryMap;
	LPBYTE pMemoryMap;
	int size = sizeof(convertStruct);
	//origin vector 파일 매핑 커널 오브젝트 생성
	hMemoryMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, size, L"translate");
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

	ConvertStruct *pConvertStruct = (ConvertStruct*)pMemoryMap;
	
	InitBuffer();

	for (int i = 0; i < origin_vec.size(); i++) {
		memcpy(convertStruct.origin_array[i], (TCHAR*)(LPCTSTR)origin_vec[i], origin_vec[i].GetLength()*sizeof(TCHAR));
		memcpy(convertStruct.converted_array[i], (TCHAR*)(LPCTSTR)converted_vec[i], converted_vec[i].GetLength()*sizeof(TCHAR));
	}
	memcpy(pConvertStruct, &convertStruct, size);
	
}

void TabFour::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateInfo();
	HookingManager hookingManager;
	hookingManager.MessageHooking();

	AfxMessageBox(L"적용되었습니다.");
}

void TabFour::InitBuffer() {
	for (int i = 0; i < CONVERT_MAX_SIZE; i++) {
		memset(convertStruct.origin_array[i], '\0', 32);
		memset(convertStruct.converted_array[i], '\0', 128);
	}
}