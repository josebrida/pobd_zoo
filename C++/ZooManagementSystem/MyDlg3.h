#pragma once


// MyDlg3 dialog

class MyDlg3 : public CDialogEx
{
	DECLARE_DYNAMIC(MyDlg3)

public:
	MyDlg3(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MyDlg3();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FormApplyGodfather };
#endif

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString animal_list;
	CString apply_name;
	CString apply_email;
	CString apply_birth;
	CString apply_password;
	CComboBox m_comboAnimal;
	CString combo_animal;
	afx_msg void OnCbnSelchangeComboanimal();
	afx_msg void OnBnClickedApplynow();
};
