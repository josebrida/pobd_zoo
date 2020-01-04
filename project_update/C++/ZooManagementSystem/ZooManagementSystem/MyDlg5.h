#pragma once


// MyDlg5 dialog

class MyDlg5 : public CDialogEx
{
	DECLARE_DYNAMIC(MyDlg5)

public:
	MyDlg5(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MyDlg5();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ManageGodfathersDialog };
#endif

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString list_pending;
	CComboBox m_combopending;
	CString v_combopending;
	int v_decision_godfather = 0;
	afx_msg void OnCbnSelchangeCombopending();
	afx_msg void OnBnClickedRadioaccept();
	afx_msg void OnBnClickedRadiodecline();
	afx_msg void OnBnClickedButtonconfirm();
};
