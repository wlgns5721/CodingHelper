
// Coding_HelperDlg.h : ��� ����
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




// CCoding_HelperDlg ��ȭ ����
class CCoding_HelperDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CTrayIconManager trayIconManager;

	CCoding_HelperDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	afx_msg LRESULT OnTrayNotification(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP();
	void OnActiveDialog();
	void OnExitDialog();
	bool MakeTrayIcon();
	
	static UINT CheckFlagThread(LPVOID lParam);  

	// ��ȭ ���� �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
