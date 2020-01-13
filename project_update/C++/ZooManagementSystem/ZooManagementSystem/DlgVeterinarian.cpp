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
	, a_ID(_T(""))
	, a_gender(_T(""))
	, a_birth(_T(""))
	, a_age(_T(""))
	, a_origin(_T(""))
	, a_specie(_T(""))
	, a_phylum(_T(""))
	, a_class(_T(""))
	, a_order(_T(""))
	, a_suborder(_T(""))
	, a_family(_T(""))
	, a_subfamily(_T(""))
	, a_scientific(_T(""))
	, a_conservation(_T(""))
	, new_year(_T(""))
	, new_month(_T(""))
	, new_day(_T(""))
	, new_description(_T(""))
	, new_prescription(_T(""))
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
	DDX_Text(pDX, IDC_a_ID, a_ID);
	DDX_Text(pDX, IDC_a_gender, a_gender);
	DDX_Text(pDX, IDC_a_birth, a_birth);
	DDX_Text(pDX, IDC_a_age, a_age);
	DDX_Text(pDX, IDC_a_origin, a_origin);
	DDX_Text(pDX, IDC_a_specie, a_specie);
	DDX_Text(pDX, IDC_a_phylum, a_phylum);
	DDX_Text(pDX, IDC_a_class, a_class);
	DDX_Text(pDX, IDC_a_order, a_order);
	DDX_Text(pDX, IDC_a_suborder, a_suborder);
	DDX_Text(pDX, IDC_a_family, a_family);
	DDX_Text(pDX, IDC_a_subfamily, a_subfamily);
	DDX_Text(pDX, IDC_a_scientific, a_scientific);
	DDX_Text(pDX, IDC_a_conservation, a_conservation);
	DDX_Text(pDX, IDC_new_year, new_year);
	DDX_Text(pDX, IDC_new_month, new_month);
	DDX_Text(pDX, IDC_new_day, new_day);
	DDX_Text(pDX, IDC_new_description, new_description);
	DDX_Text(pDX, IDC_new_prescription, new_prescription);
}


BEGIN_MESSAGE_MAP(DlgVeterinarian, CDialogEx)
	ON_CBN_SELCHANGE(IDC_ComboAnimal, &DlgVeterinarian::OnCbnSelchangeComboanimal)
	ON_BN_CLICKED(IDC_Type_Routine, &DlgVeterinarian::OnBnClickedTypeRoutine)
	ON_BN_CLICKED(IDC_Type_Emergency, &DlgVeterinarian::OnBnClickedTypeEmergency)
	ON_BN_CLICKED(IDC_ADD_Record, &DlgVeterinarian::OnBnClickedAddRecord)
	ON_BN_CLICKED(IDC_insert_today, &DlgVeterinarian::OnBnClickedinserttoday)
END_MESSAGE_MAP()


// DlgVeterinarian message handlers


void DlgVeterinarian::OnCbnSelchangeComboanimal()
{
	c_combo_animal.GetLBText(c_combo_animal.GetCurSel(), v_combo_animal);
	UpdateData(FALSE);

	GetDlgItem(IDC_ADD_Record)->EnableWindow(true);

	myconnectorclassDB MyConnection;
	MyConnection.connect();

	CString animal_ID = MyConnection.CheckAnimalID(v_combo_animal);
	CString where = _T("animal_ID = '") + animal_ID + _T("'");

	// Present animal information for selected animal
	a_ID = animal_ID;
	a_gender = MyConnection.SimpleQuery(_T("gender"), _T("animal"), _T("animal_ID"), animal_ID);
	a_birth = MyConnection.SimpleQuery(_T("birth_date"), _T("animal"), _T("animal_ID"), animal_ID);
	CString today = MyConnection.ReturnCurrentDate();
	a_age.Format(_T("%d"), _ttoi(MyConnection.CalculateDateDiff(today, a_birth)) / 365);
	a_origin = MyConnection.SimpleQuery(_T("origin"), _T("animal"), _T("animal_ID"), animal_ID);
	CString specie_ID = MyConnection.SimpleQuery(_T("species_ID"), _T("belongs"), _T("animal_ID"), animal_ID);
	a_specie = MyConnection.SimpleQuery(_T("species_name"), _T("species"), _T("species_ID"), specie_ID);
	a_phylum = MyConnection.SimpleQuery(_T("phylum"), _T("species"), _T("species_ID"), specie_ID);
	a_class = MyConnection.SimpleQuery(_T("class"), _T("species"), _T("species_ID"), specie_ID);
	a_order = MyConnection.SimpleQuery(_T("species_order"), _T("species"), _T("species_ID"), specie_ID);
	a_suborder = MyConnection.SimpleQuery(_T("suborder"), _T("species"), _T("species_ID"), specie_ID);
	a_family = MyConnection.SimpleQuery(_T("family"), _T("species"), _T("species_ID"), specie_ID);
	a_subfamily = MyConnection.SimpleQuery(_T("subfamily"), _T("species"), _T("species_ID"), specie_ID);
	CString a_genus = MyConnection.SimpleQuery(_T("genus"), _T("species"), _T("species_ID"), specie_ID);
	CString a_specific = MyConnection.SimpleQuery(_T("scientific_name"), _T("species"), _T("species_ID"), specie_ID);
	a_scientific = a_genus + _T(" ") + a_specific;
	a_conservation = MyConnection.SimpleQuery(_T("conservation_status"), _T("species"), _T("species_ID"), specie_ID);

	// Build medical record for selected animal
	vector<CString> date = MyConnection.VectorQuery(_T("appointment_date"), _T("medical_record"), where);
	vector<CString> description = MyConnection.VectorQuery(_T("record_description"), _T("medical_record"), where);
	vector<CString> record_type = MyConnection.VectorQuery(_T("record_type"), _T("medical_record"), where);
	vector<CString> prescription = MyConnection.VectorQuery(_T("prescription"), _T("medical_record"), where);
	vector<CString> vet_ID = MyConnection.VectorQuery(_T("user_ID"), _T("medical_record"), where);

	CString str_list = _T("Date | Type | Veterinarian ID | Description | Prescription \r\n ------ \r\n");
	for (size_t i = 0; i < record_type.size(); i++) {
		str_list = str_list + date[i] + _T(" | ") + record_type[i] + _T(" | ") + vet_ID[i] + _T(" | ") + description[i] + _T(" | ") + prescription[i] +_T("\r\n");
	}
	history_records = str_list;
	UpdateData(FALSE);
}


void DlgVeterinarian::OnBnClickedTypeRoutine()
{
	record_type = _T("Routine");
}


void DlgVeterinarian::OnBnClickedTypeEmergency()
{
	record_type = _T("Emergency");
}


void DlgVeterinarian::OnBnClickedAddRecord()
{
	UpdateData(TRUE);
	bool is_year;
	bool is_month;
	bool is_day;
	if (1900 <= _ttoi(new_year)) {
		is_year = TRUE;
		if ((_ttoi(new_year) % 4 == 0 && _ttoi(new_year) % 100 != 0) || _ttoi(new_year) % 400 == 0) {
			vector<int> days_of_month{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
			if (1 <= _ttoi(new_month) && _ttoi(new_month) <= 12) {
				is_month = TRUE;
				if (1 <= _ttoi(new_day) && _ttoi(new_day) <= days_of_month[_ttoi(new_month) - 1]) {
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
			if (1 <= _ttoi(new_month) && _ttoi(new_month) <= 12) {
				is_month = TRUE;
				if (1 <= _ttoi(new_day) && _ttoi(new_day) <= days_of_month[_ttoi(new_day) - 1]) {
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
	if (!new_description.IsEmpty())
	{
		if (!record_type.IsEmpty())
		{
			if (is_year) {
				if (is_month) {
					if (is_day) {
						myconnectorclassDB MyConnection;
						MyConnection.connect();

						CString record_ID;
						CString new_date = new_year + _T("-") + new_month + _T("-") + new_day;
						record_ID.Format(_T("%d"), _ttoi(MyConnection.LastID(_T("record_ID"), _T("medical_record"))) + 1);
						CString animal_ID = MyConnection.CheckAnimalID(v_combo_animal);
						CString insert = _T("'") + record_ID + _T("', '") + username + _T("', '") + animal_ID + _T("', '") + record_type + _T("', '") + new_description + _T("', '") + new_prescription + _T("', '") + new_date + _T("'");
						MyConnection.SimpleInsert(_T("medical_record"), insert);

						// Rebuild medical record for selected animal
						CString where = _T("animal_ID = '") + animal_ID + _T("'");

						vector<CString> date = MyConnection.VectorQuery(_T("appointment_date"), _T("medical_record"), where);
						vector<CString> description = MyConnection.VectorQuery(_T("record_description"), _T("medical_record"), where);
						vector<CString> record_type = MyConnection.VectorQuery(_T("record_type"), _T("medical_record"), where);
						vector<CString> prescription = MyConnection.VectorQuery(_T("prescription"), _T("medical_record"), where);
						vector<CString> vet_ID = MyConnection.VectorQuery(_T("user_ID"), _T("medical_record"), where);

						CString str_list = _T("Date | Type | Veterinarian ID | Description | Prescription \r\n ------ \r\n");
						for (size_t i = 0; i < record_type.size(); i++) {
							str_list = str_list + date[i] + _T(" | ") + record_type[i] + _T(" | ") + vet_ID[i] + _T(" | ") + description[i] + _T(" | ") + prescription[i] + _T("\r\n");
						}
						history_records = str_list;

						// Clear Edit Controls
						new_day = _T("");
						new_month = _T("");
						new_year = _T("");
						new_description = _T("");
						new_prescription = _T("");
						UpdateData(FALSE);

						record_msg.Format(_T("Record stored!"));
					}
					else {
						record_msg.Format(_T("Invalid day!"));
					}
				}
				else {
					record_msg.Format(_T("Invalid month!"));
				}
			}
			else {
				record_msg.Format(_T("Invalid year!"));
			}
		}
		else {
			record_msg.Format(_T("Select type!"));
		}
	}
	else {
		record_msg.Format(_T("Invalid description!"));
	}
	AfxMessageBox(record_msg);
}


void DlgVeterinarian::OnBnClickedinserttoday()
{
	myconnectorclassDB MyConnection;
	MyConnection.connect();

	CString today = MyConnection.ReturnCurrentDate();
	GetDlgItem(IDC_new_year)->SetWindowText(today.Left(4));
	CString aux = today.Mid(5);
	GetDlgItem(IDC_new_month)->SetWindowText(aux.Left(2));
	GetDlgItem(IDC_new_day)->SetWindowText(aux.Mid(3));
}
