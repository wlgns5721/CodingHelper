// MyText.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Coding_Helper.h"
#include "MyText.h"
#include "afxdialogex.h"


// MyText ��ȭ �����Դϴ�.

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


// MyText �޽��� ó�����Դϴ�.


void MyText::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(L"Hi");
}
