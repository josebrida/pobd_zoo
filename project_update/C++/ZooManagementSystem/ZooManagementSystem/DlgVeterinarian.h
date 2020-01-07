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
};
