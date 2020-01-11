// AssignTasksDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZooManagementSystem.h"
#include "AssignTasksDlg.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"
#include "MyDlg4.h"
#include <stdlib.h>
#include <vector>
#include <cstring>

// AssignTasksDlg dialog

IMPLEMENT_DYNAMIC(AssignTasksDlg, CDialogEx)

AssignTasksDlg::AssignTasksDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Assign_Tasks, pParent)
	, v_combo_task_type(_T(""))
	, new_task_description(_T(""))
	, new_task_year(_T(""))
	, new_task_month(_T(""))
	, new_task_day(_T(""))
	, v_combo_keeper(_T(""))
	, v_combo_tasks(_T(""))
	, v_combo_zones(_T(""))
{

}

AssignTasksDlg::~AssignTasksDlg()
{
}

void AssignTasksDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_task_type, c_combo_task_type);
	DDX_CBString(pDX, IDC_COMBO_task_type, v_combo_task_type);
	DDX_Text(pDX, IDC_Task_to_add, new_task_description);
	DDX_Text(pDX, IDC_EditTaskYear, new_task_year);
	DDX_Text(pDX, IDC_EditTaskMonth, new_task_month);
	DDX_Text(pDX, IDC_EditTaskDay, new_task_day);
	DDX_Control(pDX, IDC_COMBO_keeper, c_combo_keeper);
	DDX_CBString(pDX, IDC_COMBO_keeper, v_combo_keeper);
	DDX_Control(pDX, IDC_COMBO_tasks, c_combo_tasks);
	DDX_CBString(pDX, IDC_COMBO_tasks, v_combo_tasks);
	DDX_Control(pDX, IDC_COMBO_zones, c_combo_zones);
	DDX_CBString(pDX, IDC_COMBO_zones, v_combo_zones);
}


BEGIN_MESSAGE_MAP(AssignTasksDlg, CDialogEx)
	ON_BN_CLICKED(IDC_AddTask_Button, &AssignTasksDlg::OnBnClickedAddtaskButton)
	ON_CBN_SELCHANGE(IDC_COMBO_task_type, &AssignTasksDlg::OnCbnSelchangeCombotasktype)
	ON_BN_CLICKED(IDC_AssignTask_Button, &AssignTasksDlg::OnBnClickedAssigntaskButton)
	ON_CBN_SELCHANGE(IDC_COMBO_keeper, &AssignTasksDlg::OnCbnSelchangeCombokeeper)
	ON_CBN_SELCHANGE(IDC_COMBO_tasks, &AssignTasksDlg::OnCbnSelchangeCombotasks)
	ON_CBN_SELCHANGE(IDC_COMBO_zones, &AssignTasksDlg::OnCbnSelchangeCombozones)
END_MESSAGE_MAP()


// AssignTasksDlg message handlers


BOOL AssignTasksDlg::OnInitDialog()
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

	CString Periodic = _T("Periodic");
	CString Exceptional = _T("Exceptional");
	c_combo_task_type.AddString(Periodic);
	c_combo_task_type.AddString(Exceptional);


	for (size_t i = 0; i < MyConnection.CheckZoneName().size(); i++)
	{
		CString zone_names = MyConnection.CheckZoneName()[i];
		c_combo_zones.AddString(zone_names);
	}


	for (size_t i = 0; i < MyConnection.CheckTasksNames().size(); i++)
	{
		CString tasks_names = MyConnection.CheckTasksNames()[i];
		c_combo_tasks.AddString(tasks_names);
	}

	for (size_t i = 0; i < MyConnection.CheckKeeperIDs().size(); i++)
	{
		CString keepers_names = MyConnection.CheckUserName(MyConnection.CheckKeeperIDs()[i]);
		c_combo_keeper.AddString(keepers_names);
	}


	return TRUE;  // return TRUE  unless you set the focus to a control
}





void AssignTasksDlg::OnBnClickedAddtaskButton()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString str;
	myconnectorclassDB MyConnection;
	MyConnection.connect();

	int new_task_ID = _ttoi(MyConnection.LastTaskID()) + 1;
	CString new_task_ID_str;
	new_task_ID_str.Format(_T("%d"), new_task_ID);

	MyConnection.NewTask(new_task_ID_str, v_combo_task_type, new_task_description);

}


void AssignTasksDlg::OnCbnSelchangeCombotasktype()
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	c_combo_task_type.GetLBText(c_combo_task_type.GetCurSel(), v_combo_task_type);
}





void AssignTasksDlg::OnCbnSelchangeCombokeeper()
{
	// TODO: Add your control notification handler code here
	c_combo_keeper.GetLBText(c_combo_keeper.GetCurSel(), v_combo_keeper);
}


void AssignTasksDlg::OnCbnSelchangeCombotasks()
{
	// TODO: Add your control notification handler code here
	c_combo_tasks.GetLBText(c_combo_tasks.GetCurSel(), v_combo_tasks);
}


void AssignTasksDlg::OnCbnSelchangeCombozones()
{
	// TODO: Add your control notification handler code here
	c_combo_zones.GetLBText(c_combo_zones.GetCurSel(), v_combo_zones);
}


CString new_task_msg;


void AssignTasksDlg::OnBnClickedAssigntaskButton()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString str;
	myconnectorclassDB MyConnection;
	MyConnection.connect();

	CString task_ID = MyConnection.CheckTaskID(v_combo_tasks);
	CString zones_ID = MyConnection.SelectZoneID(v_combo_zones);
	CString keeper_ID = MyConnection.CheckUserID(v_combo_keeper);

	bool is_year;
	bool is_month;
	bool is_day;
	if (1900 <= _ttoi(new_task_year)) {
		is_year = TRUE;
		if ((_ttoi(new_task_year) % 4 == 0 && _ttoi(new_task_year) % 100 != 0) || _ttoi(new_task_year) % 400 == 0) {
			vector<int> days_of_month{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
			if (1 <= _ttoi(new_task_month) && _ttoi(new_task_month) <= 12) {
				is_month = TRUE;
				if (1 <= _ttoi(new_task_day) && _ttoi(new_task_day) <= days_of_month[_ttoi(new_task_month) - 1]) {
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
			if (1 <= _ttoi(new_task_month) && _ttoi(new_task_month) <= 12) {
				is_month = TRUE;
				if (1 <= _ttoi(new_task_day) && _ttoi(new_task_day) <= days_of_month[_ttoi(new_task_month) - 1]) {
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

	CString new_task_date = new_task_year + _T("-") + new_task_month + _T("-") + new_task_day;

	if (!new_task_year.IsEmpty() && !new_task_month.IsEmpty() && !new_task_day.IsEmpty() && is_year && is_month && is_day 
		&& !v_combo_keeper.IsEmpty() && !v_combo_tasks.IsEmpty() && !v_combo_zones.IsEmpty()  ) {
		
		MyConnection.AssignTask(task_ID, zones_ID, new_task_date, keeper_ID);

		new_task_msg.Format(_T("Task assigned!"));
		AfxMessageBox(new_task_msg);

	}
	else {
		new_task_msg.Format(_T("Error! Please check that all fields are filled correctly."));
		AfxMessageBox(new_task_msg);
	}

	
}