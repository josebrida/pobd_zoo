// MyDlg5.cpp : implementation file
//

#include "stdafx.h"
#include "ZooManagementSystem.h"
#include "MyDlg5.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"
#include <stdlib.h>


// MyDlg5 dialog

IMPLEMENT_DYNAMIC(MyDlg5, CDialogEx)

MyDlg5::MyDlg5(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ManageGodfathersDialog, pParent)
	, list_pending(_T(""))
	, v_combopending(_T(""))
{

}

MyDlg5::~MyDlg5()
{
}

void MyDlg5::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LISTPENDING, list_pending);
	DDX_Control(pDX, IDC_COMBOPENDING, m_combopending);
	DDX_CBString(pDX, IDC_COMBOPENDING, v_combopending);
}


BEGIN_MESSAGE_MAP(MyDlg5, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBOPENDING, &MyDlg5::OnCbnSelchangeCombopending)
	ON_BN_CLICKED(IDC_RADIOACCEPT, &MyDlg5::OnBnClickedRadioaccept)
	ON_BN_CLICKED(IDC_RADIODECLINE, &MyDlg5::OnBnClickedRadiodecline)
	ON_BN_CLICKED(IDC_BUTTONCONFIRM, &MyDlg5::OnBnClickedButtonconfirm)
END_MESSAGE_MAP()

BOOL MyDlg5::OnInitDialog()
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
	CString str;
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	vector<CString> pending_user_ID = MyConnection.CheckPendingGodfathers();
	CString str_list = _T("User name | Animal name | Fee \r\n ------ \r\n");
	for (size_t i = 0; i < pending_user_ID.size(); i++) {
		CString pending_user_name = MyConnection.CheckUserName(pending_user_ID[i]);
		m_combopending.AddString(pending_user_name);
		CString pending_animal_name = MyConnection.CheckAnimalName(MyConnection.CheckPendingAnimal(pending_user_ID[i]));
		CString pending_fee = MyConnection.CheckPendingFee(pending_user_ID[i]);
		str_list = str_list + pending_user_name + _T(" | ") + pending_animal_name + _T(" | ") + pending_fee + _T("\r\n");
	}
	list_pending = str_list;
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// MyDlg5 message handlers


void MyDlg5::OnCbnSelchangeCombopending()
{
	m_combopending.GetLBText(m_combopending.GetCurSel(), v_combopending);
	UpdateData(FALSE);
}


void MyDlg5::OnBnClickedRadioaccept()
{
	v_decision_godfather = 1;
}


void MyDlg5::OnBnClickedRadiodecline()
{
	v_decision_godfather = -1;
}


void MyDlg5::OnBnClickedButtonconfirm()
{
	UpdateData(TRUE);
	if (v_decision_godfather == 0) {
		CString decide_msg;
		decide_msg.Format(_T("Decide!"));
		AfxMessageBox(decide_msg);
	}
	else if (v_decision_godfather == 1) {
		myconnectorclassDB MyConnection;
		MyConnection.connect();
		MyConnection.ChangeStatus(MyConnection.CheckUserID(v_combopending), _T("Approved"));
		CString today_date = MyConnection.ReturnCurrentDate();
		CString end_date = MyConnection.AddYear(today_date);
		MyConnection.SelectGodfatherDate(MyConnection.CheckUserID(v_combopending), today_date, end_date);
	}
	else if (v_decision_godfather == -1) {
		myconnectorclassDB MyConnection;
		MyConnection.connect();
		MyConnection.ChangeStatus(MyConnection.CheckUserID(v_combopending), _T("Denied"));
	}
	m_combopending.ResetContent();
	UpdateData(FALSE);
	CString str;
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	vector<CString> pending_user_ID = MyConnection.CheckPendingGodfathers();
	CString str_list = _T("User name | Animal name | Fee \r\n ------ \r\n");
	for (size_t i = 0; i < pending_user_ID.size(); i++) {
		CString pending_user_name = MyConnection.CheckUserName(pending_user_ID[i]);
		m_combopending.AddString(pending_user_name);
		CString pending_animal_name = MyConnection.CheckAnimalName(MyConnection.CheckPendingAnimal(pending_user_ID[i]));
		CString pending_fee = MyConnection.CheckPendingFee(pending_user_ID[i]);
		str_list = str_list + pending_user_name + _T(" | ") + pending_animal_name + _T(" | ") + pending_fee + _T("\r\n");
	}
	list_pending = str_list;
	UpdateData(FALSE);
}
