// AddAnimalDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZooManagementSystem.h"
#include "AddAnimalDlg.h"
#include "afxdialogex.h"


// AddAnimalDlg dialog

IMPLEMENT_DYNAMIC(AddAnimalDlg, CDialogEx)

AddAnimalDlg::AddAnimalDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AddAnimalDialog, pParent)
	, new_animal_name(_T(""))
{

}

AddAnimalDlg::~AddAnimalDlg()
{
}

void AddAnimalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_New_AnimalName, new_animal_name);
}


BEGIN_MESSAGE_MAP(AddAnimalDlg, CDialogEx)
END_MESSAGE_MAP()


// AddAnimalDlg message handlers
