
// Coding_HelperDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Coding_Helper.h"
#include "Coding_HelperDlg.h"
#include "afxdialogex.h"
#include <string>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCoding_HelperDlg ��ȭ ����



CCoding_HelperDlg::CCoding_HelperDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CODING_HELPER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pwndShow = NULL;
}



void CCoding_HelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}

BEGIN_MESSAGE_MAP(CCoding_HelperDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(MAKE_TRAY_MESSAGE, OnTrayNotification)
	ON_COMMAND(ACTIVE_MESSAGE, OnActiveDialog)
	ON_COMMAND(EXIT_MESSAGE, OnExitDialog)


//	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB1, &CCoding_HelperDlg::OnTcnSelchangingTab1)
ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CCoding_HelperDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CCoding_HelperDlg �޽��� ó����

BOOL CCoding_HelperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString tabOne = _T("��ũ��");
	CString tabTwo = _T("����");
	CString tabThree = _T("���� ����");
	CString tabFour = _T("��ȯ");


	m_tab.InsertItem(0, tabOne);
	m_tab.InsertItem(1, tabTwo);
	m_tab.InsertItem(2, tabThree);
	m_tab.InsertItem(3, tabFour);
	m_tab.SetCurSel(0);

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);	

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}


	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CRect rect;
	m_tab.GetClientRect(&rect);
	m_one.Create(IDD_SUB1, &m_tab);
	m_one.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_SHOWWINDOW );
	m_pwndShow = &m_one;

	m_two.Create(IDD_SUB2, &m_tab);
	m_two.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_HIDEWINDOW);

	m_three.Create(IDD_SUB3, &m_tab);
	m_three.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_HIDEWINDOW);
	
	m_four.Create(IDD_SUB4, &m_tab);
	m_four.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_HIDEWINDOW);

	m_one.ShowWindow(SW_SHOW);
	
	SetDlgItemText(IDC_BTN_MSG, L"Update");

	
	m_one.UpdateMacro();

	CWinThread *pCheckFlagThread = AfxBeginThread(CheckFlagThread, this);
	CloseHandle(pCheckFlagThread);
	
	//��� ���μ����� ��ŷ�� �Ŵ� �۷ι� ��ŷ ����
	HookingManager hookingManager;
	hookingManager.MessageHooking();

	//Ʈ���� ������ ����
	if (!MakeTrayIcon()) {
		AfxMessageBox(L"create tray icon failed");
	}


	
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CCoding_HelperDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	

	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}

	else if (nID == SC_CLOSE) {
		ShowWindow(SW_HIDE);
	}

	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CCoding_HelperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CCoding_HelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CCoding_HelperDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)) 
		return TRUE;
	/*
	else if (pMsg->message == WM_SYSKEYDOWN) {   //ALT + ȭ��ǥ Ű�� ������ �� �ٸ� ������ �Ѿ��.
		int nIndex;

		if(pMsg->wParam==0x27)
			nIndex = (m_tab.GetCurSel() + 1) % 4;   //������ ������ �Ѿ��.

		else if(pMsg->wParam == 0x25)
			nIndex = (m_tab.GetCurSel() - 1) % 4;   // ���� ������ �Ѿ��.

		else
			return CDialogEx::PreTranslateMessage(pMsg);

		switch (nIndex) {
		case 0:
			m_one.ShowWindow(SW_SHOW);
			m_pwndShow = &m_one;
			break;
		case 1:
			m_two.ShowWindow(SW_SHOW);
			m_pwndShow = &m_two;
			break;
		case 2:
			m_three.ShowWindow(SW_SHOW);
			m_pwndShow = &m_three;
			break;
		case 3:
			m_four.ShowWindow(SW_SHOW);
			m_pwndShow = &m_four;
			break;
		}
		Invalidate();
		return TRUE;

	}*/
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CCoding_HelperDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	
	return CDialogEx::OnCommand(wParam, lParam);
}


void CCoding_HelperDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
	if (m_pwndShow != NULL) {
		m_pwndShow->ShowWindow(SW_HIDE);
		m_pwndShow = NULL;
	}
	int nIndex = m_tab.GetCurSel();

	switch (nIndex) {
	case 0:
		m_one.ShowWindow(SW_SHOW);
		m_pwndShow = &m_one;
		break;
	case 1:
		m_two.ShowWindow(SW_SHOW);
		m_pwndShow = &m_two;
		break;
	case 2:
		m_three.ShowWindow(SW_SHOW);
		m_pwndShow = &m_three;
		break;
	case 3:
		m_four.ShowWindow(SW_SHOW);
		m_pwndShow = &m_four;
		break;
	}
	

}

LRESULT CCoding_HelperDlg::OnTrayNotification(WPARAM wParam, LPARAM lParam) {
	switch (lParam) {
	case WM_LBUTTONDOWN: {
		ShowWindow(SW_SHOW);
		SetForegroundWindow(); //�ֻ�����
		break;
	}

	case WM_RBUTTONDOWN: {
		POINT pos;
		GetCursorPos(&pos);
		trayIconManager.MakePopUpMenu(GetSafeHwnd(),pos.x,pos.y);
		break;
	}
	}
	return 1;
}

void CCoding_HelperDlg::OnActiveDialog() {
	ShowWindow(SW_SHOW);
	SetForegroundWindow(); //�ֻ�����
}


void CCoding_HelperDlg::OnExitDialog() {
	NOTIFYICONDATA nid; 

	//tray icon�� �����.
	ZeroMemory(&nid, sizeof(NOTIFYICONDATA));
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = GetSafeHwnd();
	nid.uFlags = NULL;
	Shell_NotifyIcon(NIM_DELETE, &nid);

	CDialog::OnCancel();
	
}

bool CCoding_HelperDlg::MakeTrayIcon() {
	//Ʈ���� ������ ����
	NOTIFYICONDATA nid;
	ZeroMemory(&nid, sizeof(nid));
	nid.cbSize = sizeof(nid);
	nid.uID = 0;
	nid.hWnd = GetSafeHwnd();
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	lstrcpy(nid.szTip, L"coding helper");
	nid.uCallbackMessage = MAKE_TRAY_MESSAGE;
	bool bRet = ::Shell_NotifyIcon(NIM_ADD, &nid);    //tray icon ���
	return bRet;
}



UINT CCoding_HelperDlg::CheckFlagThread(LPVOID lParam) {
	CCoding_HelperDlg* pCodingDlg = (CCoding_HelperDlg*)lParam;
	MacroStruct* pMacroStruct = pCodingDlg->m_one.pMacroStruct;
	HANDLE hOpenMemoryMap;
	LPBYTE pOpenMemoryMap;
	HookingManager hookingManager;
	
	while (1) {
		Sleep(50);
		if (pMacroStruct->isPressButton == true) {
			pMacroStruct->isPressButton = false;

			hOpenMemoryMap = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, NULL, L"clipboard");
			pOpenMemoryMap = (LPBYTE)MapViewOfFile(hOpenMemoryMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);

			if (pMacroStruct->convertSwitch == true) {
				pMacroStruct->convertSwitch = false;
				int index = pMacroStruct->convert_index;
				hookingManager.ConvertText(wcslen(pCodingDlg->m_four.convertStruct.origin_array[index]));
			}
			else
				hookingManager.PasteClipboardText();
			
			Sleep(100);
			int dataLength = wcslen((TCHAR*)pOpenMemoryMap);
			TCHAR* clipboardData = (TCHAR*)pOpenMemoryMap;
			hookingManager.CopyToClipboard(clipboardData, wcslen(clipboardData));
		}
		else if (pMacroStruct->activateSwitch == true) {
			pMacroStruct->activateSwitch = false;
			CCoding_HelperDlg *pDlg = (CCoding_HelperDlg*)AfxGetMainWnd();     //static function���� Ŭ���� ��� function�� ȣ���Ϸ��� �̷��� �ؾ� ��
			pDlg->ShowWindow(SW_SHOW);

			//�ֻ��� ������� �����ϱ�. ���� Ȱ��ȭ�� �������� �����忡 ���� �����带 attach���ѳ��ƾ� ��
			HWND hWndForeground = ::GetForegroundWindow();
			HWND hWnd = pDlg->GetSafeHwnd();
			DWORD Strange = ::GetWindowThreadProcessId(hWndForeground, NULL);
			DWORD My = ::GetWindowThreadProcessId(pDlg->GetSafeHwnd(), NULL);
			if (!::AttachThreadInput(Strange, My, TRUE))
				continue;
			//::SetForegroundWindow(hWnd);
			::BringWindowToTop(hWnd);
			if (!::AttachThreadInput(Strange, My, FALSE))
				continue;
			pDlg->SetForegroundWindow();
		}

		else if (pMacroStruct->executeSwitch == true) {
			pMacroStruct->executeSwitch = false;
			pCodingDlg->m_three.ExecuteFile(pMacroStruct->execute_index);
		}

	}

	return 0;
}
