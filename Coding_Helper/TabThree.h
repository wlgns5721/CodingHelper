#pragma once
#include "afxwin.h"


// TabThree 대화 상자입니다.

class TabThree : public CDialogEx
{
	DECLARE_DYNAMIC(TabThree)

public:
	TabThree(CWnd* pParent = NULL);   // 표준 생성자입니다.
	void ExecuteFile(int index);
	void TabThree::SelectFile(int index);
	virtual ~TabThree();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUB3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
