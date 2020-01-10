// MyDlg11.cpp : implementation file
//

#include "stdafx.h"
#include "ZooManagementSystem.h"
#include "ZooManagementSystemDlg.h"
#include "MyDlg10.h"
#include "MyDlg4.h"
#include "MyDlg11.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"
#include <stdlib.h>
#include <list>




// MyDlg11 dialog

IMPLEMENT_DYNAMIC(MyDlg11, CDialogEx)

MyDlg11::MyDlg11(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MedicineDialog, pParent)
	, medicine_history_list(_T(""))
	, see_history_food_list(FALSE)
	, order_stock_description(_T(""))
	, order_stock_quantity(_T(""))
	, new_order_stock_description(_T(""))
	, new_order_unit_value(_T(""))
	, userID_confirm(_T(""))
	, v_combodescriptions(_T(""))
	, order_stock_ID(_T(""))
	, order_today_date(_T(""))
	, new_stock_description(_T(""))
	, first_quantity(_T(""))

{

}



MyDlg11::~MyDlg11()
{
}

void MyDlg11::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_medicine_history_list, medicine_history_list);
	DDX_Text(pDX, IDC_Order_Quantity, order_stock_quantity);
	DDX_Text(pDX, IDC_new_stock_unitvalue, new_order_unit_value);
	DDX_Control(pDX, IDC_stock_description_combo, c_combodescriptions);
	DDX_CBString(pDX, IDC_stock_description_combo, v_combodescriptions);
	DDX_Text(pDX, IDC_Stock_Description2, new_stock_description);

}





BEGIN_MESSAGE_MAP(MyDlg11, CDialogEx)
	ON_BN_CLICKED(IDC_OrderFoodButton, &MyDlg11::OnBnClickedOrderfoodbutton)
	ON_CBN_SELCHANGE(IDC_stock_description_combo, &MyDlg11::OnCbnSelchangestockdescriptioncombo)
	ON_BN_CLICKED(IDC_New_item_order_button, &MyDlg11::OnBnClickedNewitemorderbutton)
END_MESSAGE_MAP()


// MyDlg11 message handlers



BOOL MyDlg11::OnInitDialog()
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
	vector<CString> medicine_user_ID = MyConnection.CheckMedicineUserID();
	vector<CString> medicine_stock_ID = MyConnection.CheckMedicineStockID();
	vector<CString> medicine_order_date = MyConnection.CheckMedicineOrderDate();
	vector<CString> medicine_order_quantity = MyConnection.CheckMedicineOrderQuantity();
	vector<CString> medicine_description = MyConnection.CheckMedicineDescription();
	CString str_list = _T("User ID | Stock ID | Order Date | Order Quantity | Description \r\n ------ \r\n");
	for (size_t i = 0; i < medicine_user_ID.size(); i++) {

		str_list = str_list + medicine_user_ID[i] + _T(" | ") + medicine_stock_ID[i] + _T(" | ") + medicine_order_date[i] + _T(" | ") + medicine_order_quantity[i] + _T(" | ") + medicine_description[i] + _T("\r\n");
	}
	medicine_history_list = str_list;
	UpdateData(FALSE);



	for (size_t i = 0; i < MyConnection.MedicineDescriptions().size(); i++)
	{
		CString medicinedescriptions = MyConnection.MedicineDescriptions()[i];
		c_combodescriptions.AddString(medicinedescriptions);
	}





	return TRUE;  // return TRUE  unless you set the focus to a control
}


void MyDlg11::OnBnClickedOrderfoodbutton()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	myconnectorclassDB MyConnection;
	MyConnection.connect();

	CString order_today_date = MyConnection.ReturnCurrentDate();


	CString order_stock_ID = MyConnection.CheckNewStockID(v_combodescriptions);

	MyConnection.NewOrderOldDescription(userID_confirm, order_stock_ID, order_today_date, order_stock_quantity);

	CString pending_msg;
	pending_msg.Format(_T("Ordered"));
	AfxMessageBox(pending_msg);




	vector<CString> medicine_user_ID = MyConnection.CheckMedicineUserID();
	vector<CString> medicine_stock_ID = MyConnection.CheckMedicineStockID();
	vector<CString> medicine_order_date = MyConnection.CheckMedicineOrderDate();
	vector<CString> medicine_order_quantity = MyConnection.CheckMedicineOrderQuantity();
	vector<CString> medicine_description = MyConnection.CheckMedicineDescription();
	CString str_list = _T("User ID | Stock ID | Order Date | Order Quantity | Description \r\n ------ \r\n");
	for (size_t i = 0; i < medicine_user_ID.size(); i++) {

		str_list = str_list + medicine_user_ID[i] + _T(" | ") + medicine_stock_ID[i] + _T(" | ") + medicine_order_date[i] + _T(" | ") + medicine_order_quantity[i] + _T(" | ") + medicine_description[i] + _T("\r\n");
	}
	medicine_history_list = str_list;
	UpdateData(FALSE);


}












void MyDlg11::OnCbnSelchangestockdescriptioncombo()
{
	// TODO: Add your control notification handler code here
	c_combodescriptions.GetLBText(c_combodescriptions.GetCurSel(), v_combodescriptions);
	UpdateData(FALSE);
}


void MyDlg11::OnBnClickedNewitemorderbutton()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	myconnectorclassDB MyConnection;
	MyConnection.connect();


	CString new_initial_quantity;
	new_initial_quantity = _T('0');
	CString stock_type_new = _T("Medicine");

	int new_stock_ID = _ttoi(MyConnection.LastStockID()) + 1;
	CString new_stock_ID_str;
	new_stock_ID_str.Format(_T("%d"), new_stock_ID);
	CString order_stock_type = MyConnection.CheckMedicineType()[1];

	vector<CString> StocksIDs = MyConnection.CheckMedicineStockID();

	CString new_order_stock_ID = MyConnection.CheckStockID(new_stock_description);

	if (std::find(StocksIDs.begin(), StocksIDs.end(), new_order_stock_ID) != StocksIDs.end()) {

		CString pending_msg;
		pending_msg.Format(_T("That description already exist!"));
		AfxMessageBox(pending_msg);


	}
	else {


		MyConnection.NewOrderNewDescription(new_stock_ID_str, stock_type_new, new_stock_description, new_initial_quantity, new_order_unit_value);
		c_combodescriptions.ResetContent();
		for (size_t i = 0; i < MyConnection.MedicineDescriptions().size(); i++)
		{
			CString medicinedescriptions = MyConnection.MedicineDescriptions()[i];
			c_combodescriptions.AddString(medicinedescriptions);
		}
		UpdateData(FALSE);
		CString pending_msg;
		pending_msg.Format(_T("Item added!"));
		AfxMessageBox(pending_msg);

	}
}