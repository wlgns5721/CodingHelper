#pragma once


// CTabControlDlg ��ȭ �����Դϴ�.

class CTabControlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTabControlDlg)

public:
	CTabControlDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTabControlDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CODING_HELPER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
