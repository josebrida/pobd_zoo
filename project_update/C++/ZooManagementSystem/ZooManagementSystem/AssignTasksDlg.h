#pragma once


// AssignTasksDlg dialog

class AssignTasksDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AssignTasksDlg)

public:
	AssignTasksDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AssignTasksDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Assign_Tasks };
#endif

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	
	CComboBox c_combo_task_type;
	CString v_combo_task_type;
	CString new_task_description;
	afx_msg void OnBnClickedAddtaskButton();
	afx_msg void OnCbnSelchangeCombotasktype();
	CString new_task_year;
	CString new_task_month;
	CString new_task_day;
	CComboBox c_combo_keeper;
	CString v_combo_keeper;
	CComboBox c_combo_tasks;
	CString v_combo_tasks;
	CComboBox c_combo_zones;
	CString v_combo_zones;
	afx_msg void OnBnClickedAssigntaskButton();
	afx_msg void OnCbnSelchangeCombokeeper();
	afx_msg void OnCbnSelchangeCombotasks();
	afx_msg void OnCbnSelchangeCombozones();
};
