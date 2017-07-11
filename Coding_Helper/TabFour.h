#pragma once
#include "afxcmn.h"
#include "ChildDlg.h"
#include "vector"
#include "iostream"

using namespace std;
// TabFour 대화 상자입니다.

#define CONVERT_MAX_SIZE 10

struct ConvertStruct {
	TCHAR origin_array[CONVERT_MAX_SIZE][32];
	TCHAR converted_array[CONVERT_MAX_SIZE][128];
};


class TabFour : public CDialog
{
	DECLARE_DYNAMIC(TabFour)

public:
	TabFour(CWnd* pParent = NULL);   // 표준 생성자입니다.
	CChildDlg childDlg;
	vector<CString> origin_vec;
	vector<CString> converted_vec;
	ConvertStruct convertStruct;
	void UpdateInfo();
	void InitBuffer();
	virtual ~TabFour();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUB4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnChangeEdit3();
	CRichEditCtrl m_richedit;
	CListCtrl m_list;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
