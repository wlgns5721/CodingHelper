#pragma once
#include "Resource.h"
// TabOne 대화 상자입니다.

#define SHARED_MEMORY_SIZE 6 * 256 + 24
#define MACRO_MAX_SIZE 256

struct MacroStruct {	
	//입력된 문자열에 따라 동적으로 공유 메모리의 크기를 조절할 순 없을까....
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
	TabOne(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~TabOne();
	void UpdateMacro();
	MacroStruct *pMacroStruct;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CODING_HELPER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton7();
};
