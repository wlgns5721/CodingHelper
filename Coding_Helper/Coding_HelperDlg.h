
// Coding_HelperDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "TabOne.h"
#include "TabTwo.h"
#include "TabThree.h"
#include "TabFour.h"
#include "afxwin.h"
#include "TrayIconManager.h"
#include "HookingManager.h"




// CCoding_HelperDlg 대화 상자
class CCoding_HelperDlg : public CDialogEx
{
// 생성입니다.
public:
	CTrayIconManager trayIconManager;

	CCoding_HelperDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	afx_msg LRESULT OnTrayNotification(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP();
	void OnActiveDialog();
	void OnExitDialog();
	bool MakeTrayIcon();
	
	static UINT CheckFlagThread(LPVOID lParam);  

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CODING_HELPER_DIALOG };
#endif
	TabOne m_one;
	TabTwo m_two;
	TabThree m_three;
	TabFour m_four;
	//MyText mytext;

	CWnd* m_pwndShow;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnMessageBox();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBtnYes();
	CTabCtrl m_tab;
//	afx_msg void OnTcnSelchangingTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
