#pragma once
#include "Resource.h"
// TabOne ��ȭ �����Դϴ�.

#define SHARED_MEMORY_SIZE 6 * 256 + 24
#define MACRO_MAX_SIZE 256

struct MacroStruct {	
	//�Էµ� ���ڿ��� ���� �������� ���� �޸��� ũ�⸦ ������ �� ������....
	TCHAR macroText[6][MACRO_MAX_SIZE];
	int size[6];
	int execute_index = -1;
	int convert_index = -1;
	bool isPressButton;
	bool activateSwitch = false;
	bool executeSwitch = false;
	bool convertSwitch = false;
};



class TabOne : public CDialogEx
{
	DECLARE_DYNAMIC(TabOne)


public:
	TabOne(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~TabOne();
	void UpdateMacro();
	MacroStruct *pMacroStruct;

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CODING_HELPER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton7();
};
