#pragma once


// MyDlg6 dialog

class MyDlg6 : public CDialogEx
{
	DECLARE_DYNAMIC(MyDlg6)

public:
	MyDlg6(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MyDlg6();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ManageAnimalsDialog };
#endif

protected:

	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CString animals_with_species_list;
	afx_msg void OnBnClickedAddAnimalButton();
	CString wild_year;
	CString wild_month;
	CString wild_day;
	afx_msg void OnBnClickedWilddateButton();
	CListBox c_listbox_animal;
	CString v_listbox_animal;
	afx_msg void OnLbnSelchangeanimallistbox();
};
