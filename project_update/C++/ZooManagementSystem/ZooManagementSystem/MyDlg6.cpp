// MyDlg6.cpp : implementation file
//

#include "stdafx.h"
#include "ZooManagementSystem.h"
#include "MyDlg6.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"
#include "AddAnimalDlg.h"
#include <stdlib.h>

// MyDlg6 dialog

IMPLEMENT_DYNAMIC(MyDlg6, CDialogEx)

MyDlg6::MyDlg6(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ManageAnimalsDialog, pParent)
	, animals_with_species_list(_T(""))
	, wild_year(_T(""))
	, wild_month(_T(""))
	, wild_day(_T(""))
	, v_listbox_animal(_T(""))
{

}

MyDlg6::~MyDlg6()
{
}

void MyDlg6::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, animals_with_species_list);
	DDX_Text(pDX, IDC_EditWildYear, wild_year);
	DDX_Text(pDX, IDC_EditWildMonth, wild_month);
	DDX_Text(pDX, IDC_EditWildDay, wild_day);
	DDX_Control(pDX, IDC_animal_listbox, c_listbox_animal);
	DDX_LBString(pDX, IDC_animal_listbox, v_listbox_animal);
}


BEGIN_MESSAGE_MAP(MyDlg6, CDialogEx)
	ON_BN_CLICKED(IDC_ADD_Animal_Button, &MyDlg6::OnBnClickedAddAnimalButton)
	ON_BN_CLICKED(IDC_WildDate_Button, &MyDlg6::OnBnClickedWilddateButton)
	ON_LBN_SELCHANGE(IDC_animal_listbox, &MyDlg6::OnLbnSelchangeanimallistbox)
END_MESSAGE_MAP()


// MyDlg6 message handlers
BOOL MyDlg6::OnInitDialog()
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
	UpdateData(TRUE);
	CString str;
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	vector<CString> animal_IDs = MyConnection.CheckAllAnimalIDs();


	CString str_list = _T("Animal ID | Animal Name| Gender | Birth Date | Wild Date | Origin | Zone | Specie \r\n ------ \r\n");

	for (size_t i = 0; i < animal_IDs.size(); i++) {
		CString wild_date = MyConnection.CheckAnimalWildDate(animal_IDs[i]);
		if (wild_date.IsEmpty()) {
			wild_date = _T("None");
		}
		CString zone_ID = MyConnection.SimpleQuery(_T("zones_ID"), _T("lives"), _T("animal_ID"), animal_IDs[i]);
		if (zone_ID.IsEmpty()) {
			zone_ID = _T("None");
		}
		str_list =  str_list + animal_IDs[i]  +_T(" | ") + MyConnection.CheckAnimalName(animal_IDs[i]) + _T(" | ") + MyConnection.CheckAnimalGender(animal_IDs[i]) +
				    _T(" | ") + MyConnection.CheckAnimalBirthDate(animal_IDs[i]) + _T(" | ") + wild_date + 
					_T(" | ") + MyConnection.CheckAnimalOrigin(animal_IDs[i]) + _T(" | ") + zone_ID +
					_T(" | ") + MyConnection.SimpleQuery(_T("species_name"), _T("species"), _T("species_ID"), MyConnection.SimpleQuery(_T("species_ID"), _T("belongs"), _T("animal_ID"), animal_IDs[i])) + _T("\r\n");
	}
	animals_with_species_list = str_list;
	UpdateData(FALSE);

	vector<CString> available_animal_IDs = MyConnection.CheckAvailableAnimalIDs();

	for (size_t i = 0; i < available_animal_IDs.size(); i++)
	{
		CString animals_names = MyConnection.CheckAnimalName(available_animal_IDs[i]);
		c_listbox_animal.AddString(animals_names);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void MyDlg6::OnBnClickedAddAnimalButton()
{
	// TODO: Add your control notification handler code here
	AddAnimalDlg dlg;
	dlg.DoModal();
	EndDialog(0);
}


CString wild_msg;


void MyDlg6::OnBnClickedWilddateButton()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString str;
	myconnectorclassDB MyConnection;
	MyConnection.connect();

	CString today = MyConnection.ReturnCurrentDate();
	CString today_year = today.Left(4);
	CString aux = today.Mid(5);
	CString today_month = aux.Left(2);
	CString today_day = aux.Mid(3);

	bool is_year;
	bool is_month;
	bool is_day;
	if (1900 <= _ttoi(wild_year)) {
		is_year = TRUE;
		if ((_ttoi(wild_year) % 4 == 0 && _ttoi(wild_year) % 100 != 0) || _ttoi(wild_year) % 400 == 0) {
			vector<int> days_of_month{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
			if (1 <= _ttoi(wild_month) && _ttoi(wild_month) <= 12) {
				is_month = TRUE;
				if (1 <= _ttoi(wild_day) && _ttoi(wild_day) <= days_of_month[_ttoi(wild_month) - 1]) {
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
			if (1 <= _ttoi(wild_month) && _ttoi(wild_month) <= 12) {
				is_month = TRUE;
				if (1 <= _ttoi(wild_day) && _ttoi(wild_day) <= days_of_month[_ttoi(wild_month) - 1]) {
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

	if (!wild_year.IsEmpty() && !wild_month.IsEmpty() && !wild_day.IsEmpty() && is_year && is_month && is_day)
	{
		CString wild_date = wild_year + _T("-") + wild_month + _T("-") + wild_day;
		int diff = _ttoi(MyConnection.CalculateDateDiff(today, wild_date));
		if (diff >= 0) {
			CString animal_ID;
			animal_ID = MyConnection.CheckAnimalID(v_listbox_animal);

			MyConnection.GiveWildDate(animal_ID, wild_date);

			MyConnection.SimpleDelete(_T("lives"), _T("animal_ID = ") + animal_ID);

			wild_msg.Format(_T("Wild Date given!"));
			AfxMessageBox(wild_msg);

			vector<CString> animal_IDs = MyConnection.CheckAllAnimalIDs();

			CString str_list = _T("Animal ID | Animal Name| Gender | Birth Date | Wild Date | Origin | Zone | Specie \r\n ------ \r\n");

			for (size_t i = 0; i < animal_IDs.size(); i++) {
				CString wild_date = MyConnection.CheckAnimalWildDate(animal_IDs[i]);
				if (wild_date.IsEmpty()) {
					wild_date = _T("None");
				}
				CString zone_ID = MyConnection.SimpleQuery(_T("zones_ID"), _T("lives"), _T("animal_ID"), animal_IDs[i]);
				if (zone_ID.IsEmpty()) {
					zone_ID = _T("None");
				}
				str_list = str_list + animal_IDs[i] + _T(" | ") + MyConnection.CheckAnimalName(animal_IDs[i]) + _T(" | ") + MyConnection.CheckAnimalGender(animal_IDs[i]) +
					_T(" | ") + MyConnection.CheckAnimalBirthDate(animal_IDs[i]) + _T(" | ") + wild_date +
					_T(" | ") + MyConnection.CheckAnimalOrigin(animal_IDs[i]) + _T(" | ") + zone_ID +
					_T(" | ") + MyConnection.SimpleQuery(_T("species_name"), _T("species"), _T("species_ID"), MyConnection.SimpleQuery(_T("species_ID"), _T("belongs"), _T("animal_ID"), animal_IDs[i])) + _T("\r\n");
				animals_with_species_list = str_list;

				wild_year = _T("");
				wild_month = _T("");
				wild_day = _T("");

				vector<CString> available_animal_IDs = MyConnection.CheckAvailableAnimalIDs();
				c_listbox_animal.ResetContent();
				for (size_t i = 0; i < available_animal_IDs.size(); i++)
				{
					CString animals_names = MyConnection.CheckAnimalName(available_animal_IDs[i]);
					c_listbox_animal.AddString(animals_names);
				}

				UpdateData(FALSE);
			}
		}
		else {
			wild_msg.Format(_T("Error! Wild date must be past or today's date."));
			AfxMessageBox(wild_msg);
		}
	}
	else {
		wild_msg.Format(_T("Error! Please check that all fields are filled correctly."));
		AfxMessageBox(wild_msg);
	}

}


void MyDlg6::OnLbnSelchangeanimallistbox()
{
	// TODO: Add your control notification handler code here
	c_listbox_animal.GetText(c_listbox_animal.GetCurSel(), v_listbox_animal);
	UpdateData(FALSE);

}
