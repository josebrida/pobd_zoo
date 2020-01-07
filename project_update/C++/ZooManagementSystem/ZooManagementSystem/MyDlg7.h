#pragma once


// MyDlg7 dialog

class MyDlg7 : public CDialogEx
{
	DECLARE_DYNAMIC(MyDlg7)

public:
	MyDlg7(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MyDlg7();
	CStatic*  m_picture;    // pointer to a picture control
	CFileFind finder;       // for file loading
	BOOL      bLastFile;
	int       iFileAccount;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GodfatherDialog };
#endif

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString username;
	CString a_name;
	CString a_gender;
	CString a_age;
	CString a_origin;
	CString a_specie;
	CString a_phylum;
	CString a_class;
	CString a_order;
	CString a_suborder;
	CString a_family;
	CString a_subfamily;
	CString a_scientificname;
	CString a_status;
	CComboBox c_combo_godanimal;
	CString v_combo_godanimal;
	afx_msg void OnCbnSelchangeCombogodanimal();
	CStatic m_AnimalPicture;
	CString a_startdate;
	CString a_enddate;
	CString a_fee;
	afx_msg void OnBnClickedButtonExtend();
};
