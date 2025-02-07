// MyDlg2.cpp : implementation file
//

#include "stdafx.h"
#include "ZooManagementSystem.h"
#include "MyDlg2.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"


// MyDlg2 dialog

IMPLEMENT_DYNAMIC(MyDlg2, CDialogEx)

BOOL MyDlg2::OnInitDialog()
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

	CString today = MyConnection.ReturnCurrentDate();

	vector<CString> aux = MyConnection.ListQuery(_T("task_ID, zones_ID, schedule_date"), _T("assigned"), _T("user_ID = ") + username + _T(" and DATEDIFF('") + today + _T("', schedule_date) > 0"), 3);

	tasks_history = _T("Type | Description | Zone | Date \r\n ----- \r\n");

	size_t k = 0;
	while (k < aux.size()) {
		for (int i = 0; i < 3; i++) {
			if (i == 0) {
				CString type = MyConnection.SimpleQuery(_T("task_type"), _T("tasks"), _T("task_ID"), aux[i + k]);
				CString description = MyConnection.SimpleQuery(_T("task_description"), _T("tasks"), _T("task_ID"), aux[i + k]);
				tasks_history = tasks_history + type + _T(" | ") + description;
			}
			else if (i == 1) {
				tasks_history = tasks_history + _T(" | ") + aux[i + k];
			}
			else if (i == 2) {
				tasks_history = tasks_history + _T(" | ") + aux[i + k];
			}
		}
		k = k + 3;
		tasks_history = tasks_history + _T("\r\n");
	}

	vector<CString> aux1 = MyConnection.ListQuery(_T("task_ID, zones_ID, schedule_date"), _T("assigned"), _T("user_ID = ") + username + _T(" and DATEDIFF('") + today + _T("', schedule_date) <= 0"), 3);

	today_tasks = _T("Type | Description | Zone | Date \r\n ----- \r\n");

	k = 0;
	while (k < aux1.size()) {
		for (int i = 0; i < 3; i++) {
			if (i == 0) {
				CString type = MyConnection.SimpleQuery(_T("task_type"), _T("tasks"), _T("task_ID"), aux1[i + k]);
				CString description = MyConnection.SimpleQuery(_T("task_description"), _T("tasks"), _T("task_ID"), aux1[i + k]);
				today_tasks = today_tasks + type + _T(" | ") + description;
			}
			else if (i == 1) {
				today_tasks = today_tasks + _T(" | ") + aux1[i + k];
			}
			else if (i == 2) {
				today_tasks = today_tasks + _T(" | ") + aux1[i + k];
			}
		}
		k = k + 3;
		today_tasks = today_tasks + _T("\r\n");
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}


MyDlg2::MyDlg2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KeeperDialog, pParent)
	, animal_ID_search(_T(""))
	, animal_name(_T(""))
	, animal_gender(_T(""))
	, animal_birth(_T(""))
	, animal_origin(_T(""))
	, results_zonesearch(_T(""))
	, zone_ID_search(_T(""))
	, tasks_history(_T(""))
	, today_tasks(_T(""))
	, result_biome(_T(""))
	, animal_specie(_T(""))
	, animal_zone(_T(""))
{

}

MyDlg2::~MyDlg2()
{
}

void MyDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, animal_ID_search);
	DDX_Text(pDX, IDC_AnimalName, animal_name);
	DDX_Text(pDX, IDC_AnimalGender, animal_gender);
	DDX_Text(pDX, IDC_AnimalBirth, animal_birth);
	DDX_Text(pDX, IDC_AnimalOrigin, animal_origin);
	DDX_Text(pDX, IDC_ResultsZone, results_zonesearch);
	DDX_Text(pDX, IDC_ZoneSearch, zone_ID_search);
	DDX_Text(pDX, IDC_tasks_history, tasks_history);
	DDX_Text(pDX, IDC_tasks_today, today_tasks);
	DDX_Text(pDX, IDC_Result_Biome, result_biome);
	DDX_Text(pDX, IDC_AnimalSpecie, animal_specie);
	DDX_Text(pDX, IDC_AnimalZone, animal_zone);
}


BEGIN_MESSAGE_MAP(MyDlg2, CDialogEx)
	ON_BN_CLICKED(IDC_Search1, &MyDlg2::OnBnClickedSearch1)
	ON_BN_CLICKED(IDC_Search2, &MyDlg2::OnBnClickedSearch2)
END_MESSAGE_MAP()


// MyDlg2 message handlers


void MyDlg2::OnBnClickedSearch1()
{
	UpdateData(TRUE);
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	vector<CString> available_animal_IDs = MyConnection.CheckAvailableAnimalIDs();
	if (std::find(available_animal_IDs.begin(), available_animal_IDs.end(), animal_ID_search) != available_animal_IDs.end()) {
		animal_name = MyConnection.CheckAnimalName(animal_ID_search);
		animal_gender = MyConnection.CheckAnimalGender(animal_ID_search);
		animal_birth = MyConnection.CheckAnimalBirthDate(animal_ID_search);
		animal_origin = MyConnection.CheckAnimalOrigin(animal_ID_search);
		CString specie_ID = MyConnection.SimpleQuery(_T("species_ID"), _T("belongs"), _T("animal_ID"), animal_ID_search);
		animal_specie = MyConnection.SimpleQuery(_T("species_name"), _T("species"), _T("species_ID"), specie_ID);
		animal_zone = MyConnection.SimpleQuery(_T("zones_ID"), _T("lives"), _T("animal_ID"), animal_ID_search);
		UpdateData(FALSE);
	}
	else {
		GetDlgItem(IDC_AnimalName)->SetWindowText(_T(""));
		GetDlgItem(IDC_AnimalGender)->SetWindowText(_T(""));
		GetDlgItem(IDC_AnimalBirth)->SetWindowText(_T(""));
		GetDlgItem(IDC_AnimalOrigin)->SetWindowText(_T(""));
		GetDlgItem(IDC_AnimalSpecie)->SetWindowText(_T(""));
		GetDlgItem(IDC_AnimalZone)->SetWindowText(_T(""));

		CString not_found;
		not_found.Format(_T("Not found!"));
		AfxMessageBox(not_found);
	}
}


void MyDlg2::OnBnClickedSearch2()
{
	UpdateData(TRUE);
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	vector<CString> zone_IDs = MyConnection.CompleteVectorQuery(_T("zones_ID"), _T("zones"));
	if (std::find(zone_IDs.begin(), zone_IDs.end(), zone_ID_search) != zone_IDs.end()) {
		result_biome = MyConnection.SimpleQuery(_T("biome"), _T("zones"), _T("zones_ID"), zone_ID_search);
		vector<CString> animal_IDs = MyConnection.CheckZoneAnimal(zone_ID_search);
		CString str = _T("Animal ID | Animal name | Specie name \r\n ----- \r\n");
		for (size_t i = 0; i < animal_IDs.size(); i++) {
			CString specie_ID = MyConnection.SimpleQuery(_T("species_ID"), _T("belongs"), _T("animal_ID"), animal_IDs[i]);
			CString specie_name = MyConnection.SimpleQuery(_T("species_name"), _T("species"), _T("species_ID"), specie_ID);
			CString animal_name = MyConnection.SimpleQuery(_T("animal_name"), _T("animal"), _T("animal_ID"), animal_IDs[i]);
			str = str + animal_IDs[i] + _T(" | ") + animal_name + _T(" | ") + specie_name + _T("\r\n");
		}
		results_zonesearch = str;
		UpdateData(FALSE);
	}
	else {
		GetDlgItem(IDC_Result_Biome)->SetWindowText(_T(""));
		GetDlgItem(IDC_ResultsZone)->SetWindowText(_T(""));

		CString not_found;
		not_found.Format(_T("Not found!"));
		AfxMessageBox(not_found);
	}
}
