#pragma once
#include "afxwin.h"


// TabThree ��ȭ �����Դϴ�.

class TabThree : public CDialogEx
{
	DECLARE_DYNAMIC(TabThree)

public:
	TabThree(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	void ExecuteFile(int index);
	void TabThree::SelectFile(int index);
	virtual ~TabThree();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUB3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_edit1;
	CEdit m_edit2;
	CEdit m_edit3;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
