
// ZooManagementSystemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZooManagementSystem.h"
#include "ZooManagementSystemDlg.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"
#include "MyDlg2.h"
#include "MyDlg3.h"
#include "MyDlg4.h"
#include "MyDlg7.h"
#include <vector>
#include <list>
#include <string.h>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



// CZooManagementSystemDlg dialog



CZooManagementSystemDlg::CZooManagementSystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ZOOMANAGEMENTSYSTEM_DIALOG, pParent)
	, username(_T(""))
	, password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZooManagementSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Username, username);
	DDX_Text(pDX, IDC_Password, password);
}

BEGIN_MESSAGE_MAP(CZooManagementSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONLogin, &CZooManagementSystemDlg::OnBnClickedButtonlogin)
	ON_BN_CLICKED(IDC_ApplyGodfather, &CZooManagementSystemDlg::OnBnClickedApplygodfather)
END_MESSAGE_MAP()


// CZooManagementSystemDlg message handlers

BOOL CZooManagementSystemDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CZooManagementSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CZooManagementSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CZooManagementSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString welcome_msg;

void CZooManagementSystemDlg::OnBnClickedButtonlogin()
{
	myconnectorclassDB MyConnection;
	MyConnection.connect();
	UpdateData(TRUE);
	CString password_DB = MyConnection.CheckPassword(username);
	if (password_DB == password && !username.IsEmpty()) {
		welcome_msg.Format(_T("Welcome!"));
		AfxMessageBox(welcome_msg);
		vector<CString> keeper_IDs = MyConnection.CheckKeeperIDs();
		vector<CString> manager_IDs = MyConnection.CheckManagerIDs();
		vector<CString> veterinarian_IDs = MyConnection.CheckVeterinarianIDs();
		vector<CString> visitor_IDs = MyConnection.CheckVisitorIDs();
		vector<CString> accepted_godfather_IDs = MyConnection.CheckAcceptedGodfathersIDs();
		if (std::find(keeper_IDs.begin(), keeper_IDs.end(), username) != keeper_IDs.end()) {
			MyDlg2 dlg;
			dlg.DoModal();	
		}
		else if (std::find(manager_IDs.begin(), manager_IDs.end(), username) != manager_IDs.end()) {
			MyDlg4 dlg;
			dlg.DoModal();
		}
		else if (std::find(visitor_IDs.begin(), visitor_IDs.end(), username) != visitor_IDs.end()) {
			if (std::find(accepted_godfather_IDs.begin(), accepted_godfather_IDs.end(), username) != accepted_godfather_IDs.end()) {
				MyDlg7 dlg;
				dlg.username = username;
				dlg.DoModal();
			}
			else {
				CString pending_msg;
				pending_msg.Format(_T("Your request is pending!"));
				AfxMessageBox(pending_msg);
			}
		}
	}
	else {
		welcome_msg.Format(_T("Invalid login!"));
		AfxMessageBox(welcome_msg);
	}
	UpdateData(FALSE);
}


void CZooManagementSystemDlg::OnBnClickedApplygodfather()
{
	MyDlg3 dlg;
	dlg.DoModal();
}

