// MyDlg4.cpp : implementation file
//

#include "stdafx.h"
#include "ZooManagementSystem.h"
#include "MyDlg4.h"
#include "afxdialogex.h"
#include "MyDlg5.h"
#include "MyDlg6.h"


// MyDlg4 dialog

IMPLEMENT_DYNAMIC(MyDlg4, CDialogEx)

MyDlg4::MyDlg4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ManagerDialog, pParent)
{

}

MyDlg4::~MyDlg4()
{
}

void MyDlg4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MyDlg4, CDialogEx)
	ON_BN_CLICKED(IDC_ManageGodfathers, &MyDlg4::OnBnClickedManagegodfathers)
	ON_BN_CLICKED(IDC_BUTTONMANAGEANIMALS, &MyDlg4::OnBnClickedButtonmanageanimals)
END_MESSAGE_MAP()


// MyDlg4 message handlers


void MyDlg4::OnBnClickedManagegodfathers()
{
	MyDlg5 dlg;
	dlg.DoModal();
}


void MyDlg4::OnBnClickedButtonmanageanimals()
{
	MyDlg6 dlg;
	dlg.DoModal();
}
