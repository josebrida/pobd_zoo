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
#include "AssignTasksDlg.h"

// MyDlg4 dialog

IMPLEMENT_DYNAMIC(MyDlg4, CDialogEx)

BOOL MyDlg4::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	vector<CString> MedicineUserID = MyConnection.CheckResponsibleMEDICINEID();
	vector<CString> FoodUserID = MyConnection.CheckResponsibleFOODID();

	if (std::find(FoodUserID.begin(), FoodUserID.end(), username_2) != FoodUserID.end()) {
		FoodUser = TRUE;
		GetDlgItem(IDC_OrderButton)->EnableWindow(true);
	}
	else if (std::find(MedicineUserID.begin(), MedicineUserID.end(), username_2) != MedicineUserID.end()) {
		MedicineUser = TRUE;
		GetDlgItem(IDC_OrderButton)->EnableWindow(true);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

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
	ON_BN_CLICKED(IDC_Add_Assign_Tasks_Button, &MyDlg4::OnBnClickedAddAssignTasksButton)
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

	if (FoodUser) {
		MyDlg10 dlg;
		dlg.userID_confirm = username_2;
		dlg.DoModal();
	}
	else if (MedicineUser) {
		MyDlg11 dlg;
		dlg.userID_confirm = username_2;
		dlg.DoModal();
	}
}

void MyDlg4::OnBnClickedAddAssignTasksButton()
{
	AssignTasksDlg dlg;
	dlg.DoModal();
}
