#pragma once


// MyDlg8 dialog

class MyDlg8 : public CDialogEx
{
	DECLARE_DYNAMIC(MyDlg8)

public:
	MyDlg8(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MyDlg8();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ManageEmployeesDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString new_employee_name;
	CString new_employee_password;
	CString new_employee_birthdate;
	CString new_employee_email;
	BOOL add_employee;
	afx_msg void OnBnClickedAddemployee();
	afx_msg void OnBnClickedAddemployeebutton();
	BOOL eliminate_employee;
	afx_msg void OnBnClickedEliminateemployee();
	CString employees_list;
	CComboBox c_comboemployees;
	CString v_comboemployees;
	afx_msg void OnBnClickedEliminateemployeebutton();
	int type_employee = 0;
	afx_msg void OnBnClickedManagerradio();
	afx_msg void OnBnClickedKeeperradio();
	afx_msg void OnBnClickedVeterinarianradio();
	CString new_employee_begincontract;
	CString new_employee_endcontract;
	int new_type_employee = 0;
	afx_msg void OnBnClickedNewmanagertype();
	afx_msg void OnBnClickedNewkeepertype();
	afx_msg void OnBnClickedNewveterinariantype();
	CString new_employee_phone;
	afx_msg void OnCbnSelchangeComboemployees();
};
