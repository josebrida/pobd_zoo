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

MyDlg8::MyDlg8(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ManageEmployeesDialog, pParent)
	, new_employee_name(_T(""))
	, new_employee_password(_T(""))
	, new_employee_birthdate(_T(""))
	, new_employee_email(_T(""))
	, add_employee(FALSE)
	, eliminate_employee(FALSE)
	, employees_list(_T(""))
	, v_comboemployees(_T(""))
	, new_employee_begincontract(_T(""))
	, new_employee_endcontract(_T(""))
	, new_employee_phone(_T(""))
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
	DDX_Text(pDX, IDC_newemployeebirthdate, new_employee_birthdate);
	DDX_Text(pDX, IDC_newemployeeemail, new_employee_email);
	DDX_Check(pDX, IDC_AddEmployee, add_employee);
	DDX_Check(pDX, IDC_EliminateEmployee, eliminate_employee);
	DDX_Text(pDX, IDC_EmployeesList, employees_list);
	DDX_Control(pDX, IDC_COMBOEmployees, c_comboemployees);
	DDX_CBString(pDX, IDC_COMBOEmployees, v_comboemployees);
	DDX_Text(pDX, IDC_newemployeebegincontract, new_employee_begincontract);
	DDX_Text(pDX, IDC_newemployeeendcontract, new_employee_endcontract);
	DDX_Text(pDX, IDC_newemployeephone, new_employee_phone);
}


BEGIN_MESSAGE_MAP(MyDlg8, CDialogEx)
	ON_BN_CLICKED(IDC_AddEmployee, &MyDlg8::OnBnClickedAddemployee)
	ON_BN_CLICKED(IDC_ADDEmployeeButton, &MyDlg8::OnBnClickedAddemployeebutton)
	ON_BN_CLICKED(IDC_EliminateEmployee, &MyDlg8::OnBnClickedEliminateemployee)
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




void MyDlg8::OnBnClickedAddemployee()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (add_employee == (BOOL)true)
	{
		GetDlgItem(IDC_newemployeename)->EnableWindow(true);
		GetDlgItem(IDC_newemployeepassword)->EnableWindow(true);
		GetDlgItem(IDC_newemployeebirthdate)->EnableWindow(true);
		GetDlgItem(IDC_newemployeeemail)->EnableWindow(true);
		GetDlgItem(IDC_newemployeebegincontract)->EnableWindow(true);
		GetDlgItem(IDC_newemployeeendcontract)->EnableWindow(true);
		GetDlgItem(IDC_newemployeephone)->EnableWindow(true);
		GetDlgItem(IDC_ADDEmployeeButton)->EnableWindow(true);
		GetDlgItem(IDC_NewManagerType)->EnableWindow(true);
		GetDlgItem(IDC_NewKeeperType)->EnableWindow(true);
		GetDlgItem(IDC_NewVeterinarianType)->EnableWindow(true);

	}
	else
	{
		GetDlgItem(IDC_newemployeename)->EnableWindow(false);
		GetDlgItem(IDC_newemployeepassword)->EnableWindow(false);
		GetDlgItem(IDC_newemployeebirthdate)->EnableWindow(false);
		GetDlgItem(IDC_newemployeeemail)->EnableWindow(false);
		GetDlgItem(IDC_newemployeebegincontract)->EnableWindow(false);
		GetDlgItem(IDC_newemployeeendcontract)->EnableWindow(false);
		GetDlgItem(IDC_newemployeephone)->EnableWindow(false);
		GetDlgItem(IDC_ADDEmployeeButton)->EnableWindow(false);
		GetDlgItem(IDC_NewManagerType)->EnableWindow(false);
		GetDlgItem(IDC_NewKeeperType)->EnableWindow(false);
		GetDlgItem(IDC_NewVeterinarianType)->EnableWindow(false);
		GetDlgItem(IDC_ResponsibleMedicine)->EnableWindow(false);
		GetDlgItem(IDC_ResponsibleFood)->EnableWindow(false);
		GetDlgItem(IDC_ResponsibleNone)->EnableWindow(false);

	}
}


void MyDlg8::OnBnClickedAddemployeebutton()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (new_type_employee == 1) {
		myconnectorclassDB MyConnection;
		MyConnection.connect();
		int new_apply_ID = _ttoi(MyConnection.LastUser()) + 1;
		CString new_apply_ID_str;
		new_apply_ID_str.Format(_T("%d"), new_apply_ID);
		MyConnection.NewManager(new_apply_ID_str, new_employee_name, new_employee_email, new_employee_birthdate, new_employee_password, new_employee_begincontract, new_employee_endcontract, new_employee_phone);
		if (new_responsability != _T("None")) {
			vector<CString> stock_IDs = MyConnection.VectorQuery(_T("stock_ID"), _T("stock"), _T("stock_type = '") + new_responsability + _T("'"));
			for (int i = 0; i < stock_IDs.size(); i++) {
				CString insert = _T("'") + new_apply_ID_str + _T("', '") + stock_IDs[i] + _T("'");
				MyConnection.SimpleInsert(_T("responsible"), insert);
			}
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
}

void MyDlg8::OnBnClickedEliminateemployee()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (eliminate_employee == (BOOL)true)
	{
		GetDlgItem(IDC_EmployeesList)->EnableWindow(true);
		GetDlgItem(IDC_COMBOEmployees)->EnableWindow(true);
		GetDlgItem(IDC_EliminateEmployeeButton)->EnableWindow(true);
		GetDlgItem(IDC_ManagerRadio)->EnableWindow(true);
		GetDlgItem(IDC_KeeperRadio)->EnableWindow(true);
		GetDlgItem(IDC_VeterinarianRadio)->EnableWindow(true);
	}
	else
	{
		GetDlgItem(IDC_EmployeesList)->EnableWindow(false);
		GetDlgItem(IDC_COMBOEmployees)->EnableWindow(false);
		GetDlgItem(IDC_EliminateEmployeeButton)->EnableWindow(false);
		GetDlgItem(IDC_ManagerRadio)->EnableWindow(false);
		GetDlgItem(IDC_KeeperRadio)->EnableWindow(false);
		GetDlgItem(IDC_VeterinarianRadio)->EnableWindow(false);
	}




	CString str;
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	vector<CString> employee_user_ID = MyConnection.CheckEmployeeID();
	CString str_list = _T("User name \r\n ------ \r\n");
	for (size_t i = 0; i < employee_user_ID.size(); i++) {
		CString employee_user_name = MyConnection.CheckUserName(employee_user_ID[i]);

		str_list = str_list + employee_user_name + _T("\r\n");
	}
	employees_list = str_list;
	UpdateData(FALSE);

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
	UpdateData(TRUE);
	if (type_employee == 1) {
		myconnectorclassDB MyConnection;
		MyConnection.connect();
		CString manager_selected = MyConnection.CheckUserID(v_comboemployees);
		MyConnection.EliminateManager(manager_selected);
	}
	else if (type_employee == 2) {
		myconnectorclassDB MyConnection;
		MyConnection.connect();
		CString keeper_selected = MyConnection.CheckUserID(v_comboemployees);
		MyConnection.EliminateKeeper(keeper_selected);
	}
	else if (type_employee == 3) {
		myconnectorclassDB MyConnection;
		MyConnection.connect();
		CString veterinarian_selected = MyConnection.CheckUserID(v_comboemployees);
		MyConnection.EliminateVeterinarian(veterinarian_selected);
	}




	CString str;
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	vector<CString> employee_user_ID = MyConnection.CheckEmployeeID();
	CString str_list = _T("User name \r\n ------ \r\n");
	for (size_t i = 0; i < employee_user_ID.size(); i++) {
		CString employee_user_name = MyConnection.CheckUserName(employee_user_ID[i]);
		str_list = str_list + employee_user_name + _T("\r\n");
	}
	employees_list = str_list;
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
