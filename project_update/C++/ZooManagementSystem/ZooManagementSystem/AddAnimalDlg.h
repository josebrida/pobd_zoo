#pragma once


// AddAnimalDlg dialog

class AddAnimalDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddAnimalDlg)

public:
	AddAnimalDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AddAnimalDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AddAnimalDialog };
#endif

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CString new_animal_name;
	CComboBox c_combo_gender;
	CString v_combo_gender;
	CComboBox c_combo_species;
	CString v_combo_species;
	CString v_combo_zone;
	CComboBox c_combo_zone;
	afx_msg void OnBnClickedAddAnimalButton();
	CString new_birth_year;
	CString new_birth_month;
	CString new_birth_day;
	afx_msg void OnCbnSelchangeComboGender();
	afx_msg void OnCbnSelchangeComboSpecies();
	afx_msg void OnCbnSelchangeComboZone();
	CString new_animal_origin;
	CString Photo;
	CStatic c_new_animal_photo;
};
