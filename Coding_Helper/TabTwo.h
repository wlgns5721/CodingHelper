#pragma once
#include "afxwin.h"
#include <string>
#include <vector>
#include "afxcmn.h"

using namespace std;
// TabTwo 대화 상자입니다.

struct ParsedData {
	wstring phrase;
	vector<wstring>meaning_vec;
};


class TabTwo : public CDialogEx
{
	DECLARE_DYNAMIC(TabTwo)

public:
	TabTwo(CWnd* pParent = NULL);   // 표준 생성자입니다.
	void SetPhraseInformation(int index);
	void ParsingData(wstring jsonData);
	void GetDictionaryData();
	wstring GetDictionaryData(wstring phrase);
	vector<ParsedData> dictionary_vec;
	virtual ~TabTwo();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUB2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
