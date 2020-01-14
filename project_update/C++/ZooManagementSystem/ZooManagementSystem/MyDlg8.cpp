// MyDlg8.cpp : implementation file
//

#include "stdafx.h"
#include "ZooManagementSystem.h"
#include "MyDlg8.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"
#include <stdlib.h>

// MyDlg8 dialog

IMPLEMENT_DYNAMIC(MyDlg8, CDialogEx)

BOOL MyDlg8::OnInitDialog()
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
	vector<CString> employee_user_ID = MyConnection.CheckEmployeeID();
	vector<CString> keeper_IDs = MyConnection.CheckKeeperIDs();
	vector<CString> manager_IDs = MyConnection.CheckManagerIDs();
	vector<CString> veterinarian_IDs = MyConnection.CheckVeterinarianIDs();
	CString type;
	CString str_list = _T("Name | Type | Email | Phone | Birth date | Begin contract | End contract \r\n ------ \r\n");
	for (size_t i = 0; i < employee_user_ID.size(); i++) {
		CString employee_user_name = MyConnection.CheckUserName(employee_user_ID[i]);
		if (std::find(keeper_IDs.begin(), keeper_IDs.end(), employee_user_ID[i]) != keeper_IDs.end()) {
			type = _T("Keeper");
		}
		else if (std::find(manager_IDs.begin(), manager_IDs.end(), employee_user_ID[i]) != manager_IDs.end()) {
			type = _T("Manager");
		}
		else if (std::find(veterinarian_IDs.begin(), veterinarian_IDs.end(), employee_user_ID[i]) != veterinarian_IDs.end()) {
			type = _T("Veterinarian");
		}
		CString end_contract = MyConnection.SimpleQuery(_T("end_contract"), _T("employee"), _T("user_ID"), employee_user_ID[i]);
		if (end_contract.IsEmpty()) {
			end_contract = _T("None");
		}
		str_list = str_list + employee_user_name + _T(" | ") + type + _T(" | ") + MyConnection.SimpleQuery(_T("email"), _T("user"), _T("user_ID"), employee_user_ID[i]) + _T(" | ") +
			MyConnection.SimpleQuery(_T("phone"), _T("employee"), _T("user_ID"), employee_user_ID[i]) + _T(" | ") + 
			MyConnection.SimpleQuery(_T("birth_date"), _T("user"), _T("user_ID"), employee_user_ID[i]) + _T(" | ") +
			MyConnection.SimpleQuery(_T("begin_contract"), _T("employee"), _T("user_ID"), employee_user_ID[i]) + _T(" | ") +
			end_contract + _T("\r\n");
	}
	employees_list = str_list;
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

MyDlg8::MyDlg8(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ManageEmployeesDialog, pParent)
	, new_employee_name(_T(""))
	, new_employee_password(_T(""))
	, new_employee_email(_T(""))
	, employees_list(_T(""))
	, v_comboemployees(_T(""))
	, new_employee_phone(_T(""))
	, birth_day(_T(""))
	, begin_day(_T(""))
	, end_day(_T(""))
	, birth_year(_T(""))
	, begin_year(_T(""))
	, end_year(_T(""))
	, birth_month(_T(""))
	, begin_month(_T(""))
	, end_month(_T(""))
{

}

MyDlg8::~MyDlg8()
{
}

void MyDlg8::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_newemployeename, new_employee_name);
	DDX_Text(pDX, IDC_newemployeepassword, new_employee_password);
	DDX_Text(pDX, IDC_newemployeeemail, new_employee_email);
	DDX_Text(pDX, IDC_EmployeesList, employees_list);
	DDX_Control(pDX, IDC_COMBOEmployees, c_comboemployees);
	DDX_CBString(pDX, IDC_COMBOEmployees, v_comboemployees);
	DDX_Text(pDX, IDC_newemployeephone, new_employee_phone);
	DDX_Text(pDX, IDC_newemployeebirthday, birth_day);
	DDX_Text(pDX, IDC_newemployeebegincontractday, begin_day);
	DDX_Text(pDX, IDC_newemployeeendcontractday, end_day);
	DDX_Text(pDX, IDC_birth_year, birth_year);
	DDX_Text(pDX, IDC_begin_year, begin_year);
	DDX_Text(pDX, IDC_end_year, end_year);
	DDX_Text(pDX, IDC_birth_month, birth_month);
	DDX_Text(pDX, IDC_begin_month, begin_month);
	DDX_Text(pDX, IDC_end_month, end_month);
}


BEGIN_MESSAGE_MAP(MyDlg8, CDialogEx)
	ON_BN_CLICKED(IDC_ADDEmployeeButton, &MyDlg8::OnBnClickedAddemployeebutton)
	ON_BN_CLICKED(IDC_EliminateEmployeeButton, &MyDlg8::OnBnClickedEliminateemployeebutton)
	ON_BN_CLICKED(IDC_VeterinarianRadio, &MyDlg8::OnBnClickedVeterinarianradio)
	ON_BN_CLICKED(IDC_ManagerRadio, &MyDlg8::OnBnClickedManagerradio)
	ON_BN_CLICKED(IDC_KeeperRadio, &MyDlg8::OnBnClickedKeeperradio)
	ON_BN_CLICKED(IDC_VeterinarianRadio, &MyDlg8::OnBnClickedVeterinarianradio)
	ON_BN_CLICKED(IDC_NewManagerType, &MyDlg8::OnBnClickedNewmanagertype)
	ON_BN_CLICKED(IDC_NewKeeperType, &MyDlg8::OnBnClickedNewkeepertype)
	ON_BN_CLICKED(IDC_NewVeterinarianType, &MyDlg8::OnBnClickedNewveterinariantype)
	ON_CBN_SELCHANGE(IDC_COMBOEmployees, &MyDlg8::OnCbnSelchangeComboemployees)
	ON_BN_CLICKED(IDC_ResponsibleFood, &MyDlg8::OnBnClickedResponsiblefood)
	ON_BN_CLICKED(IDC_ResponsibleMedicine, &MyDlg8::OnBnClickedResponsiblemedicine)
	ON_BN_CLICKED(IDC_ResponsibleNone, &MyDlg8::OnBnClickedResponsiblenone)
END_MESSAGE_MAP()


// MyDlg7 message handlers



void MyDlg8::OnBnClickedAddemployeebutton()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString msg;

	myconnectorclassDB MyConnection;
	MyConnection.connect();

	int is_email = new_employee_email.Find(_T("@"));
	int is_number = TRUE;
	for (int i = 0; i < new_employee_phone.GetLength(); i++) {
		if (!isdigit(new_employee_phone[i])) {
			is_number = FALSE;
		}
	}

	CString new_employee_birthdate = birth_year + _T("-") + birth_month + _T("-") + birth_day;
	CString new_employee_begincontract = begin_year + _T("-") + begin_month + _T("-") + begin_day;
	CString new_employee_endcontract;

	CString today = MyConnection.ReturnCurrentDate();
	CString today_year = today.Left(4);
	CString aux = today.Mid(5);
	CString today_month = aux.Left(2);
	CString today_day = aux.Mid(3);
	bool is_year_birth = FALSE;
	bool is_month_birth = FALSE;
	bool is_day_birth = FALSE;
	bool birth_cmp = FALSE;
	if (1900 <= _ttoi(birth_year)) {
		is_year_birth = TRUE;
		if ((_ttoi(birth_year) % 4 == 0 && _ttoi(birth_year) % 100 != 0) || _ttoi(birth_year) % 400 == 0) {
			vector<int> days_of_month{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
			if (1 <= _ttoi(birth_month) && _ttoi(birth_month) <= 12) {
				is_month_birth = TRUE;
				if (1 <= _ttoi(birth_day) && _ttoi(birth_day) <= days_of_month[_ttoi(birth_month) - 1]) {
					is_day_birth = TRUE;
				}
			}
		}
		else {
			vector<int> days_of_month{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
			if (1 <= _ttoi(birth_month) && _ttoi(birth_month) <= 12) {
				is_month_birth = TRUE;
				if (1 <= _ttoi(birth_day) && _ttoi(birth_day) <= days_of_month[_ttoi(birth_month) - 1]) {
					is_day_birth = TRUE;
				}
			}
		}
		if (is_year_birth && is_month_birth && is_day_birth) {
			CString test_date = birth_year + _T("-") + birth_month + _T("-") + birth_day;
			int diff_end = _ttoi(MyConnection.CalculateDateDiff(today, test_date));
			if (diff_end >= 0) {
				birth_cmp = TRUE;
			}
			else {
				msg.Format(_T("Error! Birth date must be past date."));
				AfxMessageBox(msg);
			}
		}
	}
	bool is_year_end = FALSE;
	bool is_month_end = FALSE;
	bool is_day_end = FALSE;
	bool end_cmp = FALSE;
	bool begin_cmp = FALSE;
	if (end_year.IsEmpty() & end_month.IsEmpty() & end_day.IsEmpty()) {
		new_employee_endcontract = _T("Null");
		is_year_end = TRUE;
		is_month_end = TRUE;
		is_day_end = TRUE;
		end_cmp = TRUE;
		begin_cmp = TRUE;
	}
	else {
		if (1900 <= _ttoi(end_year)) {
			is_year_end = TRUE;
			if ((_ttoi(end_year) % 4 == 0 && _ttoi(end_year) % 100 != 0) || _ttoi(end_year) % 400 == 0) {
				vector<int> days_of_month{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
				if (1 <= _ttoi(end_month) && _ttoi(end_month) <= 12) {
					is_month_end = TRUE;
					if (1 <= _ttoi(end_day) && _ttoi(end_day) <= days_of_month[_ttoi(end_month) - 1]) {
						is_day_end = TRUE;
					}
				}
			}
			else {
				vector<int> days_of_month{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
				if (1 <= _ttoi(end_month) && _ttoi(end_month) <= 12) {
					is_month_end = TRUE;
					if (1 <= _ttoi(end_day) && _ttoi(end_day) <= days_of_month[_ttoi(end_month) - 1]) {
						is_day_end = TRUE;
					}
				}
			}
		}
		if (is_year_end && is_month_end && is_day_end) {
			CString test_date = end_year + _T("-") + end_month + _T("-") + end_day;
			int diff_end = _ttoi(MyConnection.CalculateDateDiff(today, test_date));
			if (diff_end < 0) {
				new_employee_endcontract = _T("'") + end_year + _T("-") + end_month + _T("-") + end_day + _T("'");
				end_cmp = TRUE;
			}
			else {
				msg.Format(_T("Error! Insert future end date."));
				AfxMessageBox(msg);
			}
		}
	}
	bool is_year_begin = FALSE;
	bool is_month_begin = FALSE;
	bool is_day_begin = FALSE;
	bool begin_birth_cmp = FALSE;
	if (1900 <= _ttoi(begin_year)) {
		is_year_begin = TRUE;
		if ((_ttoi(begin_year) % 4 == 0 && _ttoi(begin_year) % 100 != 0) || _ttoi(begin_year) % 400 == 0) {
			vector<int> days_of_month{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
			if (1 <= _ttoi(begin_month) && _ttoi(begin_month) <= 12) {
				is_month_begin = TRUE;
				if (1 <= _ttoi(begin_day) && _ttoi(begin_day) <= days_of_month[_ttoi(begin_month) - 1]) {
					is_day_begin = TRUE;
				}
			}
		}
		else {
			vector<int> days_of_month{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
			if (1 <= _ttoi(begin_month) && _ttoi(begin_month) <= 12) {
				is_month_begin = TRUE;
				if (1 <= _ttoi(begin_day) && _ttoi(begin_day) <= days_of_month[_ttoi(begin_month) - 1]) {
					is_day_begin = TRUE;
				}
			}
		}
		if (is_year_begin & is_month_begin && is_day_begin && is_year_end && is_month_end && is_day_end && is_year_birth && is_month_birth && is_day_birth && !end_year.IsEmpty()) {
			CString test_date1 = end_year + _T("-") + end_month + _T("-") + end_day;
			CString test_date2 = begin_year + _T("-") + begin_month + _T("-") + begin_day;
			int diff_begin = _ttoi(MyConnection.CalculateDateDiff(test_date1, test_date2));
			if (diff_begin > 0) {
				begin_cmp = TRUE;
				CString test_date1 = birth_year + _T("-") + birth_month + _T("-") + birth_day;
				CString test_date2 = begin_year + _T("-") + begin_month + _T("-") + begin_day;
				int diff_begin = _ttoi(MyConnection.CalculateDateDiff(test_date2, test_date1));
				if (diff_begin > 0) {
					begin_birth_cmp = TRUE;
				}
				else {
					msg.Format(_T("Error! Birth date must be previous to begin date."));
					AfxMessageBox(msg);
				}
			}
			else {
				msg.Format(_T("Error! Begin date must be previous to end date."));
				AfxMessageBox(msg);
			}
		}
	}


	if (is_email != -1 && is_year_end && is_month_end && is_day_end && is_year_begin && is_month_begin && is_day_begin && is_year_birth && is_month_birth && is_day_birth && begin_cmp && end_cmp && birth_cmp && new_type_employee != 0 && begin_birth_cmp && is_number) {
		if (new_type_employee == 1) {
			if (!new_responsability.IsEmpty()) {
				int new_apply_ID = _ttoi(MyConnection.LastUser()) + 1;
				CString new_apply_ID_str;
				new_apply_ID_str.Format(_T("%d"), new_apply_ID);
				MyConnection.NewManager(new_apply_ID_str, new_employee_name, new_employee_email, new_employee_birthdate, new_employee_password, new_employee_begincontract, new_employee_endcontract, new_employee_phone);
				if (new_responsability != _T("None")) {
					vector<CString> stock_IDs = MyConnection.VectorQuery(_T("stock_ID"), _T("stock"), _T("stock_type = '") + new_responsability + _T("'"));
					for (size_t i = 0; i < stock_IDs.size(); i++) {
						CString insert = _T("'") + new_apply_ID_str + _T("', '") + stock_IDs[i] + _T("'");
						MyConnection.SimpleInsert(_T("responsible"), insert);
					}
				}
			}
			else {
				msg.Format(_T("Error! Select responsability."));
				AfxMessageBox(msg);
			}
		}
		else if (new_type_employee == 2) {
			myconnectorclassDB MyConnection;
			MyConnection.connect();
			int new_apply_ID = _ttoi(MyConnection.LastUser()) + 1;
			CString new_apply_ID_str;
			new_apply_ID_str.Format(_T("%d"), new_apply_ID);
			MyConnection.NewKeeper(new_apply_ID_str, new_employee_name, new_employee_email, new_employee_birthdate, new_employee_password, new_employee_begincontract, new_employee_endcontract, new_employee_phone);

		}
		else if (new_type_employee == 3) {
			myconnectorclassDB MyConnection;
			MyConnection.connect();
			int new_apply_ID = _ttoi(MyConnection.LastUser()) + 1;
			CString new_apply_ID_str;
			new_apply_ID_str.Format(_T("%d"), new_apply_ID);
			MyConnection.NewVeterinarian(new_apply_ID_str, new_employee_name, new_employee_email, new_employee_birthdate, new_employee_password, new_employee_begincontract, new_employee_endcontract, new_employee_phone);

		}
		msg.Format(_T("User created!"));
		AfxMessageBox(msg);
		new_employee_name = _T("");
		new_employee_email = _T("");
		new_employee_phone = _T("");
		new_employee_password = _T("");
		begin_day = _T("");
		begin_month = _T("");
		begin_year = _T("");
		end_day = _T("");
		end_month = _T("");
		end_year = _T("");
		birth_day = _T("");
		birth_month = _T("");
		birth_year = _T("");

		vector<CString> employee_user_ID = MyConnection.CheckEmployeeID();
		vector<CString> keeper_IDs = MyConnection.CheckKeeperIDs();
		vector<CString> manager_IDs = MyConnection.CheckManagerIDs();
		vector<CString> veterinarian_IDs = MyConnection.CheckVeterinarianIDs();
		CString type;
		CString str_list = _T("Name | Type | Email | Phone | Birth date | Begin contract | End contract \r\n ------ \r\n");
		for (size_t i = 0; i < employee_user_ID.size(); i++) {
			CString employee_user_name = MyConnection.CheckUserName(employee_user_ID[i]);
			if (std::find(keeper_IDs.begin(), keeper_IDs.end(), employee_user_ID[i]) != keeper_IDs.end()) {
				type = _T("Keeper");
			}
			else if (std::find(manager_IDs.begin(), manager_IDs.end(), employee_user_ID[i]) != manager_IDs.end()) {
				type = _T("Manager");
			}
			else if (std::find(veterinarian_IDs.begin(), veterinarian_IDs.end(), employee_user_ID[i]) != veterinarian_IDs.end()) {
				type = _T("Veterinarian");
			}
			CString end_contract = MyConnection.SimpleQuery(_T("end_contract"), _T("employee"), _T("user_ID"), employee_user_ID[i]);
			if (end_contract.IsEmpty()) {
				end_contract = _T("None");
			}
			str_list = str_list + employee_user_name + _T(" | ") + type + _T(" | ") + MyConnection.SimpleQuery(_T("email"), _T("user"), _T("user_ID"), employee_user_ID[i]) + _T(" | ") +
				MyConnection.SimpleQuery(_T("phone"), _T("employee"), _T("user_ID"), employee_user_ID[i]) + _T(" | ") +
				MyConnection.SimpleQuery(_T("birth_date"), _T("user"), _T("user_ID"), employee_user_ID[i]) + _T(" | ") +
				MyConnection.SimpleQuery(_T("begin_contract"), _T("employee"), _T("user_ID"), employee_user_ID[i]) + _T(" | ") +
				end_contract + _T("\r\n");
		}
		employees_list = str_list;
		UpdateData(FALSE);
	}
	else {
		msg.Format(_T("Error! Check inputs."));
		AfxMessageBox(msg);
	}
}


void MyDlg8::OnBnClickedManagerradio()
{
	UpdateData(TRUE);
	CString str;
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	vector<CString> manager_user_ID = MyConnection.CheckManagerIDs();
	type_employee = 1;
	if (type_employee == 1) {
		c_comboemployees.ResetContent();
		for (size_t i = 0; i < manager_user_ID.size(); i++) {
			CString manager_user_name = MyConnection.CheckUserName(manager_user_ID[i]);
			c_comboemployees.AddString(manager_user_name);
		}
	}
}


void MyDlg8::OnBnClickedKeeperradio()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	type_employee = 2;
	CString str;
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	vector<CString> keeper_user_ID = MyConnection.CheckKeeperIDs();

	if (type_employee == 2) {
		c_comboemployees.ResetContent();
		for (size_t i = 0; i < keeper_user_ID.size(); i++) {
			CString keeper_user_name = MyConnection.CheckUserName(keeper_user_ID[i]);
			c_comboemployees.AddString(keeper_user_name);
		}
	}
}


void MyDlg8::OnBnClickedVeterinarianradio()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	type_employee = 3;
	CString str;
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	vector<CString> veterinarian_user_ID = MyConnection.CheckVeterinarianIDs();

	if (type_employee == 3) {
		c_comboemployees.ResetContent();
		for (size_t i = 0; i < veterinarian_user_ID.size(); i++) {
			CString veterinarian_user_name = MyConnection.CheckUserName(veterinarian_user_ID[i]);
			c_comboemployees.AddString(veterinarian_user_name);
		}
	}
}

void MyDlg8::OnCbnSelchangeComboemployees()
{
	// TODO: Add your control notification handler code here
	c_comboemployees.GetLBText(c_comboemployees.GetCurSel(), v_comboemployees);
	UpdateData(FALSE);
}



void MyDlg8::OnBnClickedEliminateemployeebutton()
{
	// TODO: Add your control notification handler code here
	CString msg_eliminate;
	UpdateData(TRUE);
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	if (type_employee == 1) {
		CString manager_selected = MyConnection.CheckUserID(v_comboemployees);
		MyConnection.EliminateManager(manager_selected);
	}
	else if (type_employee == 2) {
		CString keeper_selected = MyConnection.CheckUserID(v_comboemployees);
		MyConnection.EliminateKeeper(keeper_selected);
	}
	else if (type_employee == 3) {
		CString veterinarian_selected = MyConnection.CheckUserID(v_comboemployees);
		MyConnection.EliminateVeterinarian(veterinarian_selected);
	}

	vector<CString> employee_user_ID = MyConnection.CheckEmployeeID();
	vector<CString> keeper_IDs = MyConnection.CheckKeeperIDs();
	vector<CString> manager_IDs = MyConnection.CheckManagerIDs();
	vector<CString> veterinarian_IDs = MyConnection.CheckVeterinarianIDs();
	CString type;
	CString str_list = _T("Name | Type | Email | Phone | Birth date | Begin contract | End contract \r\n ------ \r\n");
	for (size_t i = 0; i < employee_user_ID.size(); i++) {
		CString employee_user_name = MyConnection.CheckUserName(employee_user_ID[i]);
		if (std::find(keeper_IDs.begin(), keeper_IDs.end(), employee_user_ID[i]) != keeper_IDs.end()) {
			type = _T("Keeper");
		}
		else if (std::find(manager_IDs.begin(), manager_IDs.end(), employee_user_ID[i]) != manager_IDs.end()) {
			type = _T("Manager");
		}
		else if (std::find(veterinarian_IDs.begin(), veterinarian_IDs.end(), employee_user_ID[i]) != veterinarian_IDs.end()) {
			type = _T("Veterinarian");
		}
		CString end_contract = MyConnection.SimpleQuery(_T("end_contract"), _T("employee"), _T("user_ID"), employee_user_ID[i]);
		if (end_contract.IsEmpty()) {
			end_contract = _T("None");
		}
		str_list = str_list + employee_user_name + _T(" | ") + type + _T(" | ") + MyConnection.SimpleQuery(_T("email"), _T("user"), _T("user_ID"), employee_user_ID[i]) + _T(" | ") +
			MyConnection.SimpleQuery(_T("phone"), _T("employee"), _T("user_ID"), employee_user_ID[i]) + _T(" | ") +
			MyConnection.SimpleQuery(_T("birth_date"), _T("user"), _T("user_ID"), employee_user_ID[i]) + _T(" | ") +
			MyConnection.SimpleQuery(_T("begin_contract"), _T("employee"), _T("user_ID"), employee_user_ID[i]) + _T(" | ") +
			end_contract + _T("\r\n");
	}
	employees_list = str_list;

	v_comboemployees = _T("");

	// Update combo manager
	vector<CString> manager_user_ID = MyConnection.CheckManagerIDs();
	if (type_employee == 1) {
		c_comboemployees.ResetContent();
		for (size_t i = 0; i < manager_user_ID.size(); i++) {
			CString manager_user_name = MyConnection.CheckUserName(manager_user_ID[i]);
			c_comboemployees.AddString(manager_user_name);
		}
	}

	// Update combo keeper
	vector<CString> keeper_user_ID = MyConnection.CheckKeeperIDs();
	if (type_employee == 2) {
		c_comboemployees.ResetContent();
		for (size_t i = 0; i < keeper_user_ID.size(); i++) {
			CString keeper_user_name = MyConnection.CheckUserName(keeper_user_ID[i]);
			c_comboemployees.AddString(keeper_user_name);
		}
	}

	// Update combo vet
	vector<CString> veterinarian_user_ID = MyConnection.CheckVeterinarianIDs();

	if (type_employee == 3) {
		c_comboemployees.ResetContent();
		for (size_t i = 0; i < veterinarian_user_ID.size(); i++) {
			CString veterinarian_user_name = MyConnection.CheckUserName(veterinarian_user_ID[i]);
			c_comboemployees.AddString(veterinarian_user_name);
		}
	}

	msg_eliminate.Format(_T("Employee deleted!"));
	AfxMessageBox(msg_eliminate);

	UpdateData(FALSE);
}





void MyDlg8::OnBnClickedNewmanagertype()
{
	// TODO: Add your control notification handler code here
	new_type_employee = 1;
	GetDlgItem(IDC_ResponsibleMedicine)->EnableWindow(true);
	GetDlgItem(IDC_ResponsibleFood)->EnableWindow(true);
	GetDlgItem(IDC_ResponsibleNone)->EnableWindow(true);
}


void MyDlg8::OnBnClickedNewkeepertype()
{
	// TODO: Add your control notification handler code here
	new_type_employee = 2;
	GetDlgItem(IDC_ResponsibleMedicine)->EnableWindow(false);
	GetDlgItem(IDC_ResponsibleFood)->EnableWindow(false);
	GetDlgItem(IDC_ResponsibleNone)->EnableWindow(false);
}


void MyDlg8::OnBnClickedNewveterinariantype()
{
	// TODO: Add your control notification handler code here
	new_type_employee = 3;
	GetDlgItem(IDC_ResponsibleMedicine)->EnableWindow(false);
	GetDlgItem(IDC_ResponsibleFood)->EnableWindow(false);
	GetDlgItem(IDC_ResponsibleNone)->EnableWindow(false);
}

void MyDlg8::OnBnClickedResponsiblefood()
{
	// TODO: Add your control notification handler code here
	new_responsability = _T("Food");
}


void MyDlg8::OnBnClickedResponsiblemedicine()
{
	// TODO: Add your control notification handler code here
	new_responsability = _T("Medicine");
}


void MyDlg8::OnBnClickedResponsiblenone()
{
	// TODO: Add your control notification handler code here
	new_responsability = _T("None");
}
