#pragma once


// MyDlg4 dialog

class MyDlg4 : public CDialogEx
{
	DECLARE_DYNAMIC(MyDlg4)

public:
	MyDlg4(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MyDlg4();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ManagerDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedManagegodfathers();
	afx_msg void OnBnClickedButtonmanageanimals();
	afx_msg void OnBnClickedManageemployees();
	afx_msg void OnBnClickedOrderbutton();
	CString username_2;
};
