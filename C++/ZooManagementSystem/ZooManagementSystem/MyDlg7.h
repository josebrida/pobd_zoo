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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
