#pragma once


// DlgVeterinarian dialog

class DlgVeterinarian : public CDialogEx
{
	DECLARE_DYNAMIC(DlgVeterinarian)

public:
	DlgVeterinarian(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgVeterinarian();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VeterinarianDialog };
#endif

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox c_combo_animal;
	CString v_combo_animal;
	CString history_records;
	afx_msg void OnCbnSelchangeComboanimal();
	CString a_ID;
	CString a_gender;
	CString a_birth;
	CString a_age;
	CString a_origin;
	CString a_specie;
	CString a_phylum;
	CString a_class;
	CString a_order;
	CString a_suborder;
	CString a_family;
	CString a_subfamily;
	CString a_scientific;
	CString a_conservation;
	CString new_year;
	CString new_month;
	CString new_day;
	CString new_description;
	CString new_prescription;
	CString record_type = _T("");
	afx_msg void OnBnClickedTypeRoutine();
	afx_msg void OnBnClickedTypeEmergency();
	afx_msg void OnBnClickedAddRecord();
	CString username;
	CString record_msg = _T("Invalid");
	afx_msg void OnBnClickedinserttoday();
};
