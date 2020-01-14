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
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString new_employee_name;
	CString new_employee_password;
	CString new_employee_email;
	afx_msg void OnBnClickedAddemployeebutton();
	CString employees_list;
	CComboBox c_comboemployees;
	CString v_comboemployees;
	afx_msg void OnBnClickedEliminateemployeebutton();
	int type_employee = 0;
	afx_msg void OnBnClickedManagerradio();
	afx_msg void OnBnClickedKeeperradio();
	afx_msg void OnBnClickedVeterinarianradio();
	int new_type_employee = 0;
	CString new_responsability = _T("");
	afx_msg void OnBnClickedNewmanagertype();
	afx_msg void OnBnClickedNewkeepertype();
	afx_msg void OnBnClickedNewveterinariantype();
	CString new_employee_phone;
	afx_msg void OnCbnSelchangeComboemployees();
	afx_msg void OnBnClickedResponsiblefood();
	afx_msg void OnBnClickedResponsiblemedicine();
	afx_msg void OnBnClickedResponsiblenone();
	CString birth_day;
	CString begin_day;
	CString end_day;
	CString birth_year;
	CString begin_year;
	CString end_year;
	CString birth_month;
	CString begin_month;
	CString end_month;
};
