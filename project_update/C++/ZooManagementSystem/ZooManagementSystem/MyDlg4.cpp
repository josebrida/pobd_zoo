// MyDlg4.cpp : implementation file
//

#include "stdafx.h"
#include "ZooManagementSystem.h"
#include "MyDlg4.h"
#include "afxdialogex.h"
#include "MyDlg5.h"
#include "MyDlg6.h"
#include "MyDlg8.h"
#include "MyDlg10.h"
#include "MyDlg11.h"
#include "ZooManagementSystemDlg.h"
#include "myconnectorclassDB.h"


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
	ON_BN_CLICKED(IDC_ManageEmployees, &MyDlg4::OnBnClickedManageemployees)
	ON_BN_CLICKED(IDC_OrderButton, &MyDlg4::OnBnClickedOrderbutton)
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


void MyDlg4::OnBnClickedManageemployees()
{
	// TODO: Add your control notification handler code here
	MyDlg8 dlg;
	dlg.DoModal();
	
}


void MyDlg4::OnBnClickedOrderbutton()
{
	// TODO: Add your control notification handler code here
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	vector<CString> MedicineUserID = MyConnection.CheckResponsibleMEDICINEID();
	vector<CString> FoodUserID = MyConnection.CheckResponsibleFOODID();

	if (std::find(FoodUserID.begin(), FoodUserID.end(), username_2) != FoodUserID.end()) {
		MyDlg10 dlg;
		dlg.userID_confirm = username_2;
		dlg.DoModal();
	}
	else {
		MyDlg11 dlg;
		dlg.userID_confirm = username_2;
		dlg.DoModal();
	}
}