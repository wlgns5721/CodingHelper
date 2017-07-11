// TabFour.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Coding_Helper.h"
#include "TabFour.h"
#include "afxdialogex.h"
#include "string"
#include "HookingManager.h"

// TabFour ��ȭ �����Դϴ�.

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


// TabFour �޽��� ó�����Դϴ�.


BOOL TabFour::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetDlgItemText(IDC_STATIC1, L"���� Ű ��ȯ");
	SetDlgItemText(IDC_STATIC2, L"ASCII ��ȯ");
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
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


BOOL TabFour::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
			SetDlgItemText(IDC_EDIT2, L"���� Ű�� ��ȯ�� �ּ���");
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
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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

//���ο� ������ �߰��ϴ� â�� ����.
void TabFour::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString origin, converted_text;
	if (childDlg.DoModal() == IDOK) {
		int row = m_list.GetItemCount();
		origin = childDlg.origin;
		converted_text = childDlg.converted_text;
		if (origin_vec.size() >= 10)
			AfxMessageBox(L"�ִ� 10�� ���� ��� �����մϴ�. ");
		else {
			m_list.InsertItem(row, origin);
			m_list.SetItem(row, 1, LVIF_TEXT, converted_text, 0, 0, 0, NULL);
			origin_vec.push_back(origin);
			converted_vec.push_back(converted_text);
		}
	}
	

	childDlg.DestroyWindow();
}


//���õ� ���� �����Ѵ�.
void TabFour::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int index = m_list.GetSelectionMark();
	m_list.DeleteItem(index);

	if (!m_list.GetItemCount()) { //����Ʈ�� �ƹ��͵� ���� ���Ϳ��� element�� ������ �İ�� �����Ѵ�.
		vector<CString>::iterator it = origin_vec.begin();
		it += index;
		origin_vec.erase(it);
	
		it = converted_vec.begin();
		it += index;
		converted_vec.erase(it);

		return;
	}
		
	else if (m_list.GetItemCount() - 1 < index)  //�� ������ ��Ҹ� ������ ��� �ε����� 1 ����.
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
	//origin vector ���� ���� Ŀ�� ������Ʈ ����
	hMemoryMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, size, L"translate");
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateInfo();
	HookingManager hookingManager;
	hookingManager.MessageHooking();

	AfxMessageBox(L"����Ǿ����ϴ�.");
}

void TabFour::InitBuffer() {
	for (int i = 0; i < CONVERT_MAX_SIZE; i++) {
		memset(convertStruct.origin_array[i], '\0', 32);
		memset(convertStruct.converted_array[i], '\0', 128);
	}
}