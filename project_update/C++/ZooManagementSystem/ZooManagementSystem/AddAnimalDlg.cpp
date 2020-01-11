// AddAnimalDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZooManagementSystem.h"
#include "AddAnimalDlg.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
// AddAnimalDlg dialog

IMPLEMENT_DYNAMIC(AddAnimalDlg, CDialogEx)

AddAnimalDlg::AddAnimalDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AddAnimalDialog, pParent)
	, new_animal_name(_T(""))
	, v_combo_gender(_T(""))
	, v_combo_species(_T(""))
	, v_combo_zone(_T(""))
	, new_birth_year(_T(""))
	, new_birth_month(_T(""))
	, new_birth_day(_T(""))
	, new_animal_origin(_T(""))
{

}

AddAnimalDlg::~AddAnimalDlg()
{
}

void AddAnimalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_New_AnimalName, new_animal_name);
	DDX_Control(pDX, IDC_COMBO_Gender, c_combo_gender);
	DDX_CBString(pDX, IDC_COMBO_Gender, v_combo_gender);
	DDX_Control(pDX, IDC_COMBO_Species, c_combo_species);
	DDX_CBString(pDX, IDC_COMBO_Species, v_combo_species);
	DDX_CBString(pDX, IDC_COMBO_Zone, v_combo_zone);
	DDX_Control(pDX, IDC_COMBO_Zone, c_combo_zone);
	DDX_Text(pDX, IDC_EditBirthYear, new_birth_year);
	DDX_Text(pDX, IDC_EditBirthMonth, new_birth_month);
	DDX_Text(pDX, IDC_EditBirthDay, new_birth_day);
	DDX_Text(pDX, IDC_New_AnimalOrigin, new_animal_origin);
	DDX_Control(pDX, IDC_New_Animal_Photo, c_new_animal_photo);
}


BEGIN_MESSAGE_MAP(AddAnimalDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ADD_Animal_Button, &AddAnimalDlg::OnBnClickedAddAnimalButton)
	ON_CBN_SELCHANGE(IDC_COMBO_Gender, &AddAnimalDlg::OnCbnSelchangeComboGender)
	ON_CBN_SELCHANGE(IDC_COMBO_Species, &AddAnimalDlg::OnCbnSelchangeComboSpecies)
	ON_CBN_SELCHANGE(IDC_COMBO_Zone, &AddAnimalDlg::OnCbnSelchangeComboZone)
END_MESSAGE_MAP()


// AddAnimalDlg message handlers

BOOL AddAnimalDlg::OnInitDialog()
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
	UpdateData(TRUE);
	CString str;
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	
	CString male = _T("Male");
	CString female = _T("Female");
	c_combo_gender.AddString(male);
	c_combo_gender.AddString(female);

	

	for (size_t i = 0; i < MyConnection.CheckSpeciesName().size(); i++)
	{
		CString species_names = MyConnection.CheckSpeciesName()[i];
		c_combo_species.AddString(species_names);
	}

	for (size_t i = 0; i < MyConnection.CheckZoneName().size(); i++)
	{
		CString zone_names = MyConnection.CheckZoneName()[i];
		c_combo_zone.AddString(zone_names);
	}





	return TRUE;  // return TRUE  unless you set the focus to a control
}


CString new_birth_msg;
CString wrong_animal_msg;

void AddAnimalDlg::OnBnClickedAddAnimalButton()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString str;
	myconnectorclassDB MyConnection;
	MyConnection.connect();


	bool is_year;
	bool is_month;
	bool is_day;
	if (1900 <= _ttoi(new_birth_year)) {
		is_year = TRUE;
		if ((_ttoi(new_birth_year) % 4 == 0 && _ttoi(new_birth_year) % 100 != 0) || _ttoi(new_birth_year) % 400 == 0) {
			vector<int> days_of_month{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
			if (1 <= _ttoi(new_birth_month) && _ttoi(new_birth_month) <= 12) {
				is_month = TRUE;
				if (1 <= _ttoi(new_birth_day) && _ttoi(new_birth_day) <= days_of_month[_ttoi(new_birth_month) - 1]) {
					is_day = TRUE;
				}
				else {
					is_day = FALSE;
				}
			}
			else {
				is_month = FALSE;
			}
		}
		else {
			vector<int> days_of_month{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
			if (1 <= _ttoi(new_birth_month) && _ttoi(new_birth_month) <= 12) {
				is_month = TRUE;
				if (1 <= _ttoi(new_birth_day) && _ttoi(new_birth_day) <= days_of_month[_ttoi(new_birth_month) - 1]) {
					is_day = TRUE;
				}
				else {
					is_day = FALSE;
				}
			}
			else {
				is_month = FALSE;
			}
		}
	}
	else {
		is_year = FALSE;
	}


	CString new_speciesID = MyConnection.SelectSpeciesID(v_combo_species);
	CString new_zonesID = MyConnection.SelectZoneID(v_combo_zone);

	CString new_birth_date = new_birth_year + _T("-") + new_birth_month + _T("-") + new_birth_day;

	CString new_wild_date = _T("NULL");

	vector<CString> AllAnimalsIDs = MyConnection.CheckAllAnimalIDs();

	CString possible_animal_ID = MyConnection.CheckAnimalID(new_animal_name);
	
	if ( std::find(AllAnimalsIDs.begin(), AllAnimalsIDs.end(), possible_animal_ID) != AllAnimalsIDs.end() ) {
		wrong_animal_msg.Format(_T("Error! Name already exists, please choose another one"));
		AfxMessageBox(wrong_animal_msg);
	}

		else if (!new_birth_year.IsEmpty() && !new_birth_month.IsEmpty() && !new_birth_day.IsEmpty() && is_year && is_month && is_day
			&& !new_animal_name.IsEmpty()  && !new_animal_origin.IsEmpty() && !v_combo_gender.IsEmpty() && !v_combo_species.IsEmpty() && !v_combo_zone.IsEmpty()  )
			 {
				CString Photo = _T("C:\\Users\\José Brida\\Desktop\\pobd_zoo\\Imagens\\") + new_animal_name + _T(".jpg");

				int new_animal_ID = _ttoi(MyConnection.LastAnimalID()) + 1;
				CString new_animal_ID_str;
				new_animal_ID_str.Format(_T("%d"), new_animal_ID);

				MyConnection.NewAnimal(new_animal_ID_str, new_animal_name, v_combo_gender, new_birth_date, new_wild_date,
									new_animal_origin, Photo, new_speciesID, new_zonesID);

				CFileDialog dlg(TRUE);

				CString sPath = _T("C:\\Users\\José Brida\\Desktop\\pobd_zoo\\Imagens\\") + new_animal_name + _T(".jpg");


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
				c_new_animal_photo.GetClientRect(rect);
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

				c_new_animal_photo.SetBitmap((HBITMAP)bmp.Detach());
				ReleaseDC(pScreenDC);

			 }
				else {
					new_birth_msg.Format(_T("Error! Please check that all fields are filled correctly."));
					AfxMessageBox(new_birth_msg);
				}


}


void AddAnimalDlg::OnCbnSelchangeComboGender()
{
	// TODO: Add your control notification handler code here
	c_combo_gender.GetLBText(c_combo_gender.GetCurSel(), v_combo_gender);
	
}


void AddAnimalDlg::OnCbnSelchangeComboSpecies()
{
	// TODO: Add your control notification handler code here
	c_combo_species.GetLBText(c_combo_species.GetCurSel(), v_combo_species);
	
}


void AddAnimalDlg::OnCbnSelchangeComboZone()
{
	// TODO: Add your control notification handler code here
	c_combo_zone.GetLBText(c_combo_zone.GetCurSel(), v_combo_zone);
	
}

