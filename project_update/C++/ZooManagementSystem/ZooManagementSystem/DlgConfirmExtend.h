#pragma once


// DlgConfirmExtend dialog

class DlgConfirmExtend : public CDialogEx
{
	DECLARE_DYNAMIC(DlgConfirmExtend)

public:
	DlgConfirmExtend(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DlgConfirmExtend();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ConfirmExtend };
#endif

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString confirm_name;
	CString confirm_fee;
	CString confirm_end;
	CString user_ID;
	CString animal_ID;
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonYes();
};
