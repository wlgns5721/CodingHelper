#pragma once


// MyText ��ȭ �����Դϴ�.

class MyText : public CDialogEx
{
	DECLARE_DYNAMIC(MyText)

public:
	MyText(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~MyText();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUB1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
