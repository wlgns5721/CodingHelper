// AddDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Coding_Helper.h"
#include "ChildDlg.h"
#include "afxdialogex.h"


// AddDialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CChildDlg, CDialogEx)

CChildDlg::CChildDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHILDDLG, pParent)
{

}

CChildDlg::~CChildDlg()
{
}

void CChildDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChildDlg, CDialogEx)
END_MESSAGE_MAP()


// AddDialog �޽��� ó�����Դϴ�.


BOOL CChildDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetDlgItemText(IDC_STATIC1, L"��ȯ ��� : ");
	SetDlgItemText(IDC_STATIC2, L"��ȯ�� �ؽ�Ʈ : ");
	((CEdit*)GetDlgItem(IDC_EDIT1))->SetLimitText(32);
	((CEdit*)GetDlgItem(IDC_EDIT2))->SetLimitText(128);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CChildDlg::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	GetDlgItemText(IDC_EDIT1, origin);
	GetDlgItemText(IDC_EDIT2, converted_text);

	CDialogEx::OnOK();
}
