// DlgVeterinarian.cpp : implementation file
//

#include "stdafx.h"
#include "ZooManagementSystem.h"
#include "DlgVeterinarian.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"


// DlgVeterinarian dialog

IMPLEMENT_DYNAMIC(DlgVeterinarian, CDialogEx)

BOOL DlgVeterinarian::OnInitDialog()
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
	vector<CString> animal_IDs = MyConnection.CheckAvailableAnimalIDs();
	for (size_t i = 0; i < animal_IDs.size(); i++) {
		CString animals_name = MyConnection.CheckAnimalName(animal_IDs[i]);
		c_combo_animal.AddString(animals_name);
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

DlgVeterinarian::DlgVeterinarian(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VeterinarianDialog, pParent)
	, v_combo_animal(_T(""))
	, history_records(_T(""))
{

}

DlgVeterinarian::~DlgVeterinarian()
{
}

void DlgVeterinarian::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ComboAnimal, c_combo_animal);
	DDX_CBString(pDX, IDC_ComboAnimal, v_combo_animal);
	DDX_Text(pDX, IDC_HistoryRecords, history_records);
}


BEGIN_MESSAGE_MAP(DlgVeterinarian, CDialogEx)
	ON_CBN_SELCHANGE(IDC_ComboAnimal, &DlgVeterinarian::OnCbnSelchangeComboanimal)
END_MESSAGE_MAP()


// DlgVeterinarian message handlers


void DlgVeterinarian::OnCbnSelchangeComboanimal()
{
	c_combo_animal.GetLBText(c_combo_animal.GetCurSel(), v_combo_animal);
	UpdateData(FALSE);

	myconnectorclassDB MyConnection;
	MyConnection.connect();

	CString animal_ID = MyConnection.CheckAnimalID(v_combo_animal);
	CString where = _T("animal_ID = '") + animal_ID + _T("'");
	vector<CString> record_type = MyConnection.VectorQuery(_T("record_type"), _T("medical_record"), where);

	CString str_list = _T("Date | Type | ID | Description | Prescription \r\n ------ \r\n");
	for (size_t i = 0; i < record_type.size(); i++) {
		str_list = str_list + record_type[i] + _T("\r\n");
	}
	history_records = str_list;
	UpdateData(FALSE);
}
