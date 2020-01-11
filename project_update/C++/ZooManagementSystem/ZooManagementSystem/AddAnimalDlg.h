#pragma once


// AddAnimalDlg dialog

class AddAnimalDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddAnimalDlg)

public:
	AddAnimalDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AddAnimalDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AddAnimalDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString new_animal_name;
};
