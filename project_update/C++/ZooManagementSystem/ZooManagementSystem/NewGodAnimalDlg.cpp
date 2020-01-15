// NewGodAnimalDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZooManagementSystem.h"
#include "NewGodAnimalDlg.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"


// NewGodAnimalDlg dialog

IMPLEMENT_DYNAMIC(NewGodAnimalDlg, CDialogEx)

BOOL NewGodAnimalDlg::OnInitDialog()
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

	vector<CString> available_IDs = MyConnection.CheckAvailableAnimalIDs();
	vector<CString> godanimals_IDs = MyConnection.VectorQuery(_T("animal_ID"), _T("godfather"), _T("user_ID = ") + username);
	vector<CString> godanimals_declined_IDs = MyConnection.VectorQuery(_T("animal_ID"), _T("godfather"), _T("user_ID = ") + username + _T(" AND status = 'Denied'"));
	for (size_t i = 0; i < available_IDs.size(); i++) {
		if (std::find(godanimals_IDs.begin(), godanimals_IDs.end(), available_IDs[i]) == godanimals_IDs.end()) {
			CString godanimals_name = MyConnection.CheckAnimalName(available_IDs[i]);
			c_select_new_godanimal.AddString(godanimals_name);
		}
		else {
			if (std::find(godanimals_declined_IDs.begin(), godanimals_declined_IDs.end(), available_IDs[i]) != godanimals_declined_IDs.end()) {
				CString godanimals_name = MyConnection.CheckAnimalName(available_IDs[i]);
				c_select_new_godanimal.AddString(godanimals_name);
			}
		}
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

NewGodAnimalDlg::NewGodAnimalDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NewGodAnimal, pParent)
	, v_select_new_godanimal(_T(""))
	, selected_specie(_T(""))
	, selected_fee(_T(""))
{

}

NewGodAnimalDlg::~NewGodAnimalDlg()
{
}

void NewGodAnimalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SelectNewGodAnimal, c_select_new_godanimal);
	DDX_CBString(pDX, IDC_SelectNewGodAnimal, v_select_new_godanimal);
	DDX_Text(pDX, IDC_SelectedSpecie, selected_specie);
	DDX_Text(pDX, IDC_SelectedFee, selected_fee);
}


BEGIN_MESSAGE_MAP(NewGodAnimalDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_SelectNewGodAnimal, &NewGodAnimalDlg::OnCbnSelchangeSelectnewgodanimal)
	ON_BN_CLICKED(IDC_ButtonSubmitRequest, &NewGodAnimalDlg::OnBnClickedButtonsubmitrequest)
END_MESSAGE_MAP()


// NewGodAnimalDlg message handlers


void NewGodAnimalDlg::OnCbnSelchangeSelectnewgodanimal()
{
	// TODO: Add your control notification handler code here
	c_select_new_godanimal.GetLBText(c_select_new_godanimal.GetCurSel(), v_select_new_godanimal);

	if (!v_select_new_godanimal.IsEmpty()) {
		GetDlgItem(IDC_ButtonSubmitRequest)->EnableWindow(true);
	}

	UpdateData(FALSE);

	myconnectorclassDB MyConnection;
	MyConnection.connect();

	CString animal_ID = MyConnection.SimpleQuery(_T("animal_ID"), _T("animal"), _T("animal_name"), v_select_new_godanimal);
	selected_specie = MyConnection.SimpleQuery(_T("species_name"), _T("species"), _T("species_ID"), MyConnection.SimpleQuery(_T("species_ID"), _T("belongs"), _T("animal_ID"), animal_ID));
	
	CString today_date = MyConnection.ReturnCurrentDate();
	CString animal_birth = MyConnection.CheckBirth(animal_ID);
	CString age;
	age.Format(_T("%d"), _ttoi(MyConnection.CalculateDateDiff(today_date, animal_birth)) / 365);
	CString base_fee = MyConnection.CheckSpeciesFee(MyConnection.CheckSpecieID(animal_ID));
	CString fee;
	fee.Format(_T("%d"), 200 / (_ttoi(age) + 1) + _ttoi(base_fee));
	selected_fee = fee;

	UpdateData(FALSE);
}


void NewGodAnimalDlg::OnBnClickedButtonsubmitrequest()
{
	// TODO: Add your control notification handler code here
	myconnectorclassDB MyConnection;
	MyConnection.connect();

	CString msg;

	UpdateData(FALSE);

	CString animal_ID = MyConnection.SimpleQuery(_T("animal_ID"), _T("animal"), _T("animal_name"), v_select_new_godanimal);
	CString today_date = MyConnection.ReturnCurrentDate();
	CString animal_birth = MyConnection.CheckBirth(animal_ID);
	CString age;
	age.Format(_T("%d"), _ttoi(MyConnection.CalculateDateDiff(today_date, animal_birth)) / 365);
	CString base_fee = MyConnection.CheckSpeciesFee(MyConnection.CheckSpecieID(animal_ID));
	CString fee;
	fee.Format(_T("%d"), 200 / (_ttoi(age) + 1) + _ttoi(base_fee));

	MyConnection.SimpleInsert(_T("godfather"), animal_ID + _T(", ") + username + _T(", 'Pending', '") + today_date + _T("', ") + fee + _T(", NULL, NULL"));

	msg.Format(_T("Request sent!"));
	AfxMessageBox(msg);

	EndDialog(0);
}

