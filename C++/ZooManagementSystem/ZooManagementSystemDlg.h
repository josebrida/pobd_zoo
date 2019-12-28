
// ZooManagementSystemDlg.h : header file
//

#pragma once


// CZooManagementSystemDlg dialog
class CZooManagementSystemDlg : public CDialogEx
{
// Construction
public:
	CZooManagementSystemDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZOOMANAGEMENTSYSTEM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString username;
	CString password;
	afx_msg void OnBnClickedButtonlogin();
	afx_msg void OnBnClickedApplygodfather();
};
