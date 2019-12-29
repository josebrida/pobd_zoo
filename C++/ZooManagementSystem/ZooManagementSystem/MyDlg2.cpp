// MyDlg2.cpp : implementation file
//

#include "stdafx.h"
#include "ZooManagementSystem.h"
#include "MyDlg2.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"


// MyDlg2 dialog

IMPLEMENT_DYNAMIC(MyDlg2, CDialogEx)

MyDlg2::MyDlg2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KeeperDialog, pParent)
	, animal_ID_search(_T(""))
	, animal_name(_T(""))
	, animal_gender(_T(""))
	, animal_birth(_T(""))
	, animal_origin(_T(""))
	, animal_wild(_T(""))
	, results_zonesearch(_T(""))
	, zone_ID_search(_T(""))
{

}

MyDlg2::~MyDlg2()
{
}

void MyDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, animal_ID_search);
	DDX_Text(pDX, IDC_AnimalName, animal_name);
	DDX_Text(pDX, IDC_AnimalGender, animal_gender);
	DDX_Text(pDX, IDC_AnimalBirth, animal_birth);
	DDX_Text(pDX, IDC_AnimalOrigin, animal_origin);
	DDX_Text(pDX, IDC_AnimalWild, animal_wild);
	DDX_Text(pDX, IDC_ResultsZone, results_zonesearch);
	DDX_Text(pDX, IDC_ZoneSearch, zone_ID_search);
}


BEGIN_MESSAGE_MAP(MyDlg2, CDialogEx)
	ON_BN_CLICKED(IDC_Search1, &MyDlg2::OnBnClickedSearch1)
	ON_BN_CLICKED(IDC_Search2, &MyDlg2::OnBnClickedSearch2)
END_MESSAGE_MAP()


// MyDlg2 message handlers


void MyDlg2::OnBnClickedSearch1()
{
	UpdateData(TRUE);
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	animal_name = MyConnection.CheckAnimalName(animal_ID_search);
	animal_gender = MyConnection.CheckAnimalGender(animal_ID_search);
	animal_birth = MyConnection.CheckAnimalBirthDate(animal_ID_search);
	animal_origin = MyConnection.CheckAnimalOrigin(animal_ID_search);
	animal_wild = MyConnection.CheckAnimalWildDate(animal_ID_search);
	UpdateData(FALSE);
}


void MyDlg2::OnBnClickedSearch2()
{
	UpdateData(TRUE);
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	vector<CString> animal_IDs = MyConnection.CheckZoneAnimal(zone_ID_search);
	CString str = _T("");
	for (size_t i = 0; i < animal_IDs.size(); i++) {
		str = str + animal_IDs[i] + _T("\r\n");
	}
	results_zonesearch = str;
	UpdateData(FALSE);
}
