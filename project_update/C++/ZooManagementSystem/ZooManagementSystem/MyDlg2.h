#pragma once


// MyDlg2 dialog

class MyDlg2 : public CDialogEx
{
	DECLARE_DYNAMIC(MyDlg2)

public:
	MyDlg2(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MyDlg2();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KeeperDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString animal_ID_search;
	afx_msg void OnBnClickedSearch1();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeInformation();
	CString animal_name;
	CString animal_gender;
	CString animal_birth;
	CString animal_origin;
	CString animal_wild;
	CString results_zonesearch;
	afx_msg void OnBnClickedSearch2();
	CString zone_ID_search;
};
