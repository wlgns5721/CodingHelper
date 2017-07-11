
// Coding_HelperDlg.cpp : 구현 파일
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



// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CCoding_HelperDlg 대화 상자



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


// CCoding_HelperDlg 메시지 처리기

BOOL CCoding_HelperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString tabOne = _T("매크로");
	CString tabTwo = _T("사전");
	CString tabThree = _T("빠른 실행");
	CString tabFour = _T("변환");


	m_tab.InsertItem(0, tabOne);
	m_tab.InsertItem(1, tabTwo);
	m_tab.InsertItem(2, tabThree);
	m_tab.InsertItem(3, tabFour);
	m_tab.SetCurSel(0);

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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


	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
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
	
	//모든 프로세스에 후킹을 거는 글로벌 후킹 수행
	HookingManager hookingManager;
	hookingManager.MessageHooking();

	//트레이 아이콘 생성
	if (!MakeTrayIcon()) {
		AfxMessageBox(L"create tray icon failed");
	}


	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCoding_HelperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCoding_HelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CCoding_HelperDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)) 
		return TRUE;
	/*
	else if (pMsg->message == WM_SYSKEYDOWN) {   //ALT + 화살표 키를 눌렀을 때 다른 탭으로 넘어간다.
		int nIndex;

		if(pMsg->wParam==0x27)
			nIndex = (m_tab.GetCurSel() + 1) % 4;   //오른쪽 탭으로 넘어간다.

		else if(pMsg->wParam == 0x25)
			nIndex = (m_tab.GetCurSel() - 1) % 4;   // 왼쪽 탭으로 넘어간다.

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
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	return CDialogEx::OnCommand(wParam, lParam);
}


void CCoding_HelperDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
		SetForegroundWindow(); //최상위로
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
	SetForegroundWindow(); //최상위로
}


void CCoding_HelperDlg::OnExitDialog() {
	NOTIFYICONDATA nid; 

	//tray icon을 지운다.
	ZeroMemory(&nid, sizeof(NOTIFYICONDATA));
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = GetSafeHwnd();
	nid.uFlags = NULL;
	Shell_NotifyIcon(NIM_DELETE, &nid);

	CDialog::OnCancel();
	
}

bool CCoding_HelperDlg::MakeTrayIcon() {
	//트레이 아이콘 생성
	NOTIFYICONDATA nid;
	ZeroMemory(&nid, sizeof(nid));
	nid.cbSize = sizeof(nid);
	nid.uID = 0;
	nid.hWnd = GetSafeHwnd();
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	lstrcpy(nid.szTip, L"coding helper");
	nid.uCallbackMessage = MAKE_TRAY_MESSAGE;
	bool bRet = ::Shell_NotifyIcon(NIM_ADD, &nid);    //tray icon 등록
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
			CCoding_HelperDlg *pDlg = (CCoding_HelperDlg*)AfxGetMainWnd();     //static function에서 클래스 멤버 function을 호출하려면 이렇게 해야 함
			pDlg->ShowWindow(SW_SHOW);

			//최상위 윈도우로 설정하기. 현재 활성화된 윈도우의 쓰레드에 현재 쓰레드를 attach시켜놓아야 함
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
