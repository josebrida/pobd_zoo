// DlgConfirmExtend.cpp : implementation file
//

#include "stdafx.h"
#include "ZooManagementSystem.h"
#include "DlgConfirmExtend.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"


// DlgConfirmExtend dialog

IMPLEMENT_DYNAMIC(DlgConfirmExtend, CDialogEx)

BOOL DlgConfirmExtend::OnInitDialog()
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
	CString today_date = MyConnection.ReturnCurrentDate();
	
	// Present animal name
	confirm_name = MyConnection.CheckAnimalName(animal_ID);

	// Present animal fee
	CString animal_birth = MyConnection.CheckBirth(animal_ID);
	int age = _ttoi(MyConnection.CalculateDateDiff(today_date, animal_birth)) / 365;
	CString base_fee = MyConnection.CheckSpeciesFee(MyConnection.CheckSpecieID(animal_ID));
	confirm_fee.Format(_T("%d"), 200 / (age + 1) + _ttoi(base_fee));

	// Present new end date
	CString end_date = MyConnection.DoubleQuery(_T("ending_date"), _T("godfather"), _T("user_ID"), user_ID, _T("animal_ID"), animal_ID);
	confirm_end = MyConnection.AddYear(end_date);

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

DlgConfirmExtend::DlgConfirmExtend(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ConfirmExtend, pParent)
	, confirm_name(_T(""))
	, confirm_fee(_T(""))
	, confirm_end(_T(""))
{

}

DlgConfirmExtend::~DlgConfirmExtend()
{
}

void DlgConfirmExtend::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_AnimalName, confirm_name);
	DDX_Text(pDX, IDC_Fee, confirm_fee);
	DDX_Text(pDX, IDC_NewEnd, confirm_end);
}


BEGIN_MESSAGE_MAP(DlgConfirmExtend, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Cancel, &DlgConfirmExtend::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_Yes, &DlgConfirmExtend::OnBnClickedButtonYes)
END_MESSAGE_MAP()


// DlgConfirmExtend message handlers


void DlgConfirmExtend::OnBnClickedButtonCancel()
{
	// Close dialog
	EndDialog(0);
}


void DlgConfirmExtend::OnBnClickedButtonYes()
{
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	MyConnection.UpdateDouble(_T("godfather"), _T("fee"), confirm_fee, _T("user_ID"), user_ID, _T("animal_ID"), animal_ID);
	MyConnection.UpdateDouble(_T("godfather"), _T("ending_date"), confirm_end, _T("user_ID"), user_ID, _T("animal_ID"), animal_ID);

	EndDialog(0);
}
