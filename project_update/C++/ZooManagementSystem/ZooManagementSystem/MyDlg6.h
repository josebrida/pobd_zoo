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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
