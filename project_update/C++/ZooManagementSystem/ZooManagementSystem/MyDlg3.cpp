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
	, apply_birth_y(_T(""))
	, apply_password(_T(""))
	, combo_animal(_T(""))
	, apply_birth_m(_T(""))
	, apply_birth_d(_T(""))
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
	DDX_Text(pDX, IDC_EditBirthYear, apply_birth_y);
	DDX_Text(pDX, IDC_EditPassword, apply_password);
	DDX_Control(pDX, IDC_ComboAnimal, m_comboAnimal);
	DDX_CBString(pDX, IDC_ComboAnimal, combo_animal);
	DDX_Text(pDX, IDC_EditBirthMonth, apply_birth_m);
	DDX_Text(pDX, IDC_EditBirthDay, apply_birth_d);
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
	CString age;
	CString fee;
	CString base_fee;
	vector<CString> age_str;
	vector<CString> fee_str;
	CString today_date = MyConnection.ReturnCurrentDate();
	CString str_list = _T("Animal name | Specie | Age (years) | Fee (€/year) \r\n ------ \r\n");
	for (size_t i = 0; i < animal_names.size(); i++) {
		m_comboAnimal.AddString(animal_names[i]);
		species_ID = MyConnection.CheckSpecieID(animal_IDs[i]);
		animals_specie.push_back(MyConnection.CheckSpecieName(species_ID));
		animals_birth.push_back(MyConnection.CheckBirth(animal_IDs[i]));
		age.Format(_T("%d"), _ttoi(MyConnection.CalculateDateDiff(today_date, animals_birth[i]))/365);
		age_str.push_back(age);
		base_fee = MyConnection.CheckSpeciesFee(MyConnection.CheckSpecieID(animal_IDs[i]));
		fee.Format(_T("%d"), 200/(_ttoi(age_str[i])+1) + _ttoi(base_fee));
		fee_str.push_back(fee);
		str_list = str_list + animal_names[i] + _T(" | ") + animals_specie[i] + _T(" | ") + age_str[i] + _T(" | ") + fee_str[i] +_T("\r\n");
	}
	animal_list = str_list;
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}


// MyDlg3 message handlers


void MyDlg3::OnCbnSelchangeComboanimal()
{
	m_comboAnimal.GetLBText(m_comboAnimal.GetCurSel(), combo_animal);
}

CString apply_msg;

void MyDlg3::OnBnClickedApplynow()
{
	UpdateData(TRUE);
	int is_email = apply_email.Find(_T("@"));
	bool is_year;
	bool is_month;
	bool is_day;
	if (1900 <= _ttoi(apply_birth_y)) {
		is_year = TRUE;	
		if ((_ttoi(apply_birth_y)%4 == 0 && _ttoi(apply_birth_y)%100 != 0) || _ttoi(apply_birth_y)%400 == 0) {
			vector<int> days_of_month{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
			if (1 <= _ttoi(apply_birth_m) && _ttoi(apply_birth_m) <= 12) {
				is_month = TRUE;
				if (1 <= _ttoi(apply_birth_d) && _ttoi(apply_birth_d) <= days_of_month[_ttoi(apply_birth_m) - 1]) {
					is_day = TRUE;
				}
				else {
					is_day = FALSE;
				}
			}
			else {
				is_month = FALSE;
			}
		}
		else {
			vector<int> days_of_month{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
			if (1 <= _ttoi(apply_birth_m) && _ttoi(apply_birth_m) <= 12) {
				is_month = TRUE;
				if (1 <= _ttoi(apply_birth_d) && _ttoi(apply_birth_d) <= days_of_month[_ttoi(apply_birth_m) - 1]) {
					is_day = TRUE;
				}
				else {
					is_day = FALSE;
				}
			}
			else {
				is_month = FALSE;
			}
		}
	}
	else {
		is_year = FALSE;
	}
	if (!apply_name.IsEmpty() && !apply_email.IsEmpty() && !apply_birth_y.IsEmpty() && !apply_birth_m.IsEmpty() && !apply_birth_d.IsEmpty() && !combo_animal.IsEmpty() && is_email != -1 && is_year && is_month && is_day) {
		myconnectorclassDB MyConnection;
		MyConnection.connect();
		int apply_ID = _ttoi(MyConnection.LastUser()) + 1;
		CString apply_ID_str;
		apply_ID_str.Format(_T("%d"), apply_ID);
		CString animalID_selected = MyConnection.CheckAnimalID(combo_animal);
		CString today_date = MyConnection.ReturnCurrentDate();
		CString apply_birth = apply_birth_y + _T("-") + apply_birth_m + _T("-") + apply_birth_d;
		CString animals_birth = MyConnection.CheckBirth(MyConnection.CheckAnimalID(combo_animal));
		CString age;
		age.Format(_T("%d"), _ttoi(MyConnection.CalculateDateDiff(today_date, animals_birth)) / 365);
		CString base_fee;
		base_fee = MyConnection.CheckSpeciesFee(MyConnection.CheckSpecieID(MyConnection.CheckAnimalID(combo_animal)));
		CString fee;
		fee.Format(_T("%d"), 200 / (_ttoi(age) + 1) + _ttoi(base_fee));
		MyConnection.ApplyGodfather(apply_ID_str, apply_name, apply_email, apply_birth, apply_password, animalID_selected, today_date, fee);
		apply_msg.Format(_T("Application sent!"));
		AfxMessageBox(apply_msg);
		EndDialog(0);
	}
	else {
		apply_msg.Format(_T("Error! Please check that all fields are filled correctly."));
		AfxMessageBox(apply_msg);
	}
}
