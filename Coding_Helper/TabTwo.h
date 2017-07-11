#pragma once
#include "afxwin.h"
#include <string>
#include <vector>
#include "afxcmn.h"

using namespace std;
// TabTwo ��ȭ �����Դϴ�.

struct ParsedData {
	wstring phrase;
	vector<wstring>meaning_vec;
};


class TabTwo : public CDialogEx
{
	DECLARE_DYNAMIC(TabTwo)

public:
	TabTwo(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	void SetPhraseInformation(int index);
	void ParsingData(wstring jsonData);
	void GetDictionaryData();
	wstring GetDictionaryData(wstring phrase);
	vector<ParsedData> dictionary_vec;
	virtual ~TabTwo();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUB2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox listBox;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnBnClickedButton8();
	CComboBox m_combo;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	
	
	CRichEditCtrl m_word;
	CRichEditCtrl m_explain;
	
};
