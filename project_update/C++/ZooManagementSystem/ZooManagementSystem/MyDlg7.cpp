// MyDlg7.cpp : implementation file
//

#include "stdafx.h"
#include "ZooManagementSystem.h"
#include "MyDlg7.h"
#include "afxdialogex.h"
#include "ZooManagementSystemDlg.h"
#include "myconnectorclassDB.h"
#include "DlgConfirmExtend.h"


// MyDlg7 dialog

IMPLEMENT_DYNAMIC(MyDlg7, CDialogEx)

BOOL MyDlg7::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	vector<CString> godanimals = MyConnection.AcceptedGodanimalsIDs(username);
	for (size_t i = 0; i < godanimals.size(); i++) {
		CString godanimals_name = MyConnection.CheckAnimalName(godanimals[i]);
		c_combo_godanimal.AddString(godanimals_name);
	}
	
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

MyDlg7::MyDlg7(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GodfatherDialog, pParent)
	, a_name(_T(""))
	, a_gender(_T(""))
	, a_age(_T(""))
	, a_origin(_T(""))
	, a_specie(_T(""))
	, a_phylum(_T(""))
	, a_class(_T(""))
	, a_order(_T(""))
	, a_suborder(_T(""))
	, a_family(_T(""))
	, a_subfamily(_T(""))
	, a_scientificname(_T(""))
	, a_status(_T(""))
	, v_combo_godanimal(_T(""))
	, a_startdate(_T(""))
	, a_enddate(_T(""))
	, a_fee(_T(""))
{

}

MyDlg7::~MyDlg7()
{
}

void MyDlg7::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Name, a_name);
	DDX_Text(pDX, IDC_Gender, a_gender);
	DDX_Text(pDX, IDC_Age, a_age);
	DDX_Text(pDX, IDC_Origin, a_origin);
	DDX_Text(pDX, IDC_CommonName, a_specie);
	DDX_Text(pDX, IDC_Phylum, a_phylum);
	DDX_Text(pDX, IDC_Class, a_class);
	DDX_Text(pDX, IDC_Order, a_order);
	DDX_Text(pDX, IDC_Suborder, a_suborder);
	DDX_Text(pDX, IDC_Family, a_family);
	DDX_Text(pDX, IDC_Subfamily, a_subfamily);
	DDX_Text(pDX, IDC_ScientificName, a_scientificname);
	DDX_Text(pDX, IDC_Conservation, a_status);
	DDX_Control(pDX, IDC_ComboGodanimal, c_combo_godanimal);
	DDX_CBString(pDX, IDC_ComboGodanimal, v_combo_godanimal);
	DDX_Text(pDX, IDC_StartDate, a_startdate);
	DDX_Text(pDX, IDC_EndDate, a_enddate);
	DDX_Text(pDX, IDC_Fee, a_fee);
}


BEGIN_MESSAGE_MAP(MyDlg7, CDialogEx)
	ON_CBN_SELCHANGE(IDC_ComboGodanimal, &MyDlg7::OnCbnSelchangeCombogodanimal)
	ON_BN_CLICKED(IDC_BUTTON_Extend, &MyDlg7::OnBnClickedButtonExtend)
END_MESSAGE_MAP()

// MyDlg7 message handlers


void MyDlg7::OnCbnSelchangeCombogodanimal()
{
	// TODO: Add your control notification handler code here
	c_combo_godanimal.GetLBText(c_combo_godanimal.GetCurSel(), v_combo_godanimal);
	UpdateData(FALSE);
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	CString godanimal_ID = MyConnection.CheckAnimalID(v_combo_godanimal);
	a_name = v_combo_godanimal; 
	a_gender = MyConnection.CheckAnimalGender(godanimal_ID);
	CString a_birth = MyConnection.CheckAnimalBirthDate(godanimal_ID);
	CString today = MyConnection.ReturnCurrentDate();
	a_age.Format(_T("%d"),_ttoi(MyConnection.CalculateDateDiff(today, a_birth))/365);
	a_origin = MyConnection.CheckAnimalOrigin(godanimal_ID);
	CString specie_ID = MyConnection.SimpleQuery(_T("species_ID"), _T("belongs"), _T("animal_ID"), godanimal_ID);
	a_specie = MyConnection.SimpleQuery(_T("species_name"), _T("species"), _T("species_ID"), specie_ID);
	a_phylum = MyConnection.SimpleQuery(_T("phylum"), _T("species"), _T("species_ID"), specie_ID);
	a_class = MyConnection.SimpleQuery(_T("class"), _T("species"), _T("species_ID"), specie_ID);
	a_order = MyConnection.SimpleQuery(_T("species_order"), _T("species"), _T("species_ID"), specie_ID);
	a_suborder = MyConnection.SimpleQuery(_T("suborder"), _T("species"), _T("species_ID"), specie_ID);
	a_family = MyConnection.SimpleQuery(_T("family"), _T("species"), _T("species_ID"), specie_ID);
	a_subfamily = MyConnection.SimpleQuery(_T("subfamily"), _T("species"), _T("species_ID"), specie_ID);
	a_status = MyConnection.SimpleQuery(_T("conservation_status"), _T("species"), _T("species_ID"), specie_ID);
	a_scientificname = MyConnection.SimpleQuery(_T("genus"), _T("species"), _T("species_ID"), specie_ID) + _T(" ") + MyConnection.SimpleQuery(_T("scientific_name"), _T("species"), _T("species_ID"), specie_ID);
	a_startdate = MyConnection.DoubleQuery(_T("start_date"), _T("godfather"), _T("user_ID"), username, _T("animal_ID"), godanimal_ID);
	a_enddate = MyConnection.DoubleQuery(_T("ending_date"), _T("godfather"), _T("user_ID"), username, _T("animal_ID"), godanimal_ID);
	a_fee = MyConnection.DoubleQuery(_T("fee"), _T("godfather"), _T("user_ID"), username, _T("animal_ID"), godanimal_ID);

	int diff = _ttoi(MyConnection.DateDiff(a_enddate, today));
	if (diff < 31) {
		GetDlgItem(IDC_BUTTON_Extend)->EnableWindow(true);
	}
	else {
		GetDlgItem(IDC_BUTTON_Extend)->EnableWindow(false);
	}

	UpdateData(FALSE);

	// Show image.... (https://stackoverflow.com/questions/33366461/display-image-from-browse-button)
	/*CFileDialog dlg(TRUE);
	CString sPath = MyConnection.SimpleQuery(_T("photo"), _T("animal"), _T("animal_ID"), godanimal_ID);

	CImage img;
	HRESULT hr = img.Load(sPath);
	if (FAILED(hr))
	{
		CString sErrorMsg;
		sErrorMsg.Format(_T("Failed to load %s"), sPath);
		AfxMessageBox(sErrorMsg);
		return;
	}

	CRect rect;
	m_AnimalPicture.GetClientRect(rect);
	int nWidth = rect.Width();
	int nHeight = rect.Height();

	CDC* pScreenDC = GetDC();
	CDC MemDC;
	MemDC.CreateCompatibleDC(pScreenDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pScreenDC, nWidth, nHeight);

	CBitmap* pOldObj = MemDC.SelectObject(&bmp);
	img.StretchBlt(MemDC.m_hDC, 0, 0, nWidth, nHeight, 0, 0, img.GetWidth(), img.GetHeight(), SRCCOPY);
	MemDC.SelectObject(pOldObj);

	m_AnimalPicture.SetBitmap((HBITMAP)bmp.Detach());
	ReleaseDC(pScreenDC);
	*/
}


void MyDlg7::OnBnClickedButtonExtend()
{
	// TODO: Add your control notification handler code here
	if (!v_combo_godanimal.IsEmpty()) {
		DlgConfirmExtend dlg;
		dlg.user_ID = username;
		myconnectorclassDB MyConnection;
		MyConnection.connect();
		dlg.animal_ID = MyConnection.CheckAnimalID(v_combo_godanimal);
		dlg.DoModal();
		a_enddate = MyConnection.DoubleQuery(_T("ending_date"), _T("godfather"), _T("user_ID"), username, _T("animal_ID"), MyConnection.CheckAnimalID(v_combo_godanimal));
		a_fee = MyConnection.DoubleQuery(_T("fee"), _T("godfather"), _T("user_ID"), username, _T("animal_ID"), MyConnection.CheckAnimalID(v_combo_godanimal));
		UpdateData(FALSE);
	}
}
