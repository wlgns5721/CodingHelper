// MyText.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Coding_Helper.h"
#include "MyText.h"
#include "afxdialogex.h"


// MyText 대화 상자입니다.

IMPLEMENT_DYNAMIC(MyText, CDialogEx)

MyText::MyText(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SUB1, pParent)
{

}

MyText::~MyText()
{
}

void MyText::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MyText, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &MyText::OnBnClickedButton1)
END_MESSAGE_MAP()


// MyText 메시지 처리기입니다.


void MyText::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxMessageBox(L"Hi");
}
