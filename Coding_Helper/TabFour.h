#pragma once
#include "afxcmn.h"
#include "ChildDlg.h"
#include "vector"
#include "iostream"

using namespace std;
// TabFour ��ȭ �����Դϴ�.

#define CONVERT_MAX_SIZE 10

struct ConvertStruct {
	TCHAR origin_array[CONVERT_MAX_SIZE][32];
	TCHAR converted_array[CONVERT_MAX_SIZE][128];
};


class TabFour : public CDialog
{
	DECLARE_DYNAMIC(TabFour)

public:
	TabFour(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	CChildDlg childDlg;
	vector<CString> origin_vec;
	vector<CString> converted_vec;
	ConvertStruct convertStruct;
	void UpdateInfo();
	void InitBuffer();
	virtual ~TabFour();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUB4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
