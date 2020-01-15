#pragma once


// NewGodAnimalDlg dialog

class NewGodAnimalDlg : public CDialogEx
{
	DECLARE_DYNAMIC(NewGodAnimalDlg)

public:
	NewGodAnimalDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~NewGodAnimalDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NewGodAnimal };
#endif

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox c_select_new_godanimal;
	CString v_select_new_godanimal;
	CString selected_specie;
	afx_msg void OnCbnSelchangeSelectnewgodanimal();
	CString username;
	CString selected_fee;
	afx_msg void OnBnClickedButtonsubmitrequest();
};
