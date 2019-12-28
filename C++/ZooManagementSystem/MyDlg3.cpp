// MyDlg3.cpp : implementation file
//

#include "stdafx.h"
#include "ZooManagementSystem.h"
#include "MyDlg3.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"
#include <stdlib.h>


// MyDlg3 dialog

IMPLEMENT_DYNAMIC(MyDlg3, CDialogEx)

MyDlg3::MyDlg3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FormApplyGodfather, pParent)
	, animal_list(_T(""))
	, apply_name(_T(""))
	, apply_email(_T(""))
	, apply_birth(_T(""))
	, apply_password(_T(""))
	, combo_animal(_T(""))
{

}

MyDlg3::~MyDlg3()
{
}

void MyDlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_AnimalList, animal_list);
	DDX_Text(pDX, IDC_EditName, apply_name);
	DDX_Text(pDX, IDC_EditEmail, apply_email);
	DDX_Text(pDX, IDC_EditBirth, apply_birth);
	DDX_Text(pDX, IDC_EditPassword, apply_password);
	DDX_Control(pDX, IDC_ComboAnimal, m_comboAnimal);
	DDX_CBString(pDX, IDC_ComboAnimal, combo_animal);
}


BEGIN_MESSAGE_MAP(MyDlg3, CDialogEx)
	ON_CBN_SELCHANGE(IDC_ComboAnimal, &MyDlg3::OnCbnSelchangeComboanimal)
	ON_BN_CLICKED(IDC_ApplyNow, &MyDlg3::OnBnClickedApplynow)
END_MESSAGE_MAP()

BOOL MyDlg3::OnInitDialog()
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
	vector<CString> animal_names = MyConnection.CheckAvailableAnimalNames();
	vector<CString> animal_IDs = MyConnection.CheckAvailableAnimalIDs();
	CString species_ID;
	vector<CString> animals_specie;
	vector<CString> animals_birth;
	CString str_list = _T("Animal name | Specie | Birth date \r\n ------ \r\n");
	for (size_t i = 0; i < animal_names.size(); i++) {
		m_comboAnimal.AddString(animal_names[i]);
		species_ID = MyConnection.CheckSpecieID(animal_IDs[i]);
		animals_specie.push_back(MyConnection.CheckSpecieName(species_ID));
		animals_birth.push_back(MyConnection.CheckBirth(animal_IDs[i]));
		str_list = str_list + animal_names[i] + _T(" | ") + animals_specie[i] + _T(" | ") + animals_birth[i] +_T("\r\n");
	}
	animal_list = str_list;
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}


// MyDlg3 message handlers


void MyDlg3::OnCbnSelchangeComboanimal()
{
	m_comboAnimal.GetLBText(m_comboAnimal.GetCurSel(), combo_animal);
	UpdateData(FALSE);
}


void MyDlg3::OnBnClickedApplynow()
{
	UpdateData(TRUE);
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	int apply_ID = _ttoi(MyConnection.LastUser()) + 1;
	CString apply_ID_str;
	apply_ID_str.Format(_T("%d"), apply_ID);
	CString animalID_selected = MyConnection.CheckAnimalID(combo_animal);
	MyConnection.ApplyGodfather(apply_ID_str, apply_name, apply_email, apply_birth, apply_password, animalID_selected, _T("2019-12-28"), _T("30"));
}
