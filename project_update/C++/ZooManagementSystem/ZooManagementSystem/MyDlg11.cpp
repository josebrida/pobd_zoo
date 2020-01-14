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
	, v_combodescriptionsmed(_T(""))
	, order_stock_ID(_T(""))
	, order_today_date(_T(""))
	, new_stock_description(_T(""))
	, first_quantity(_T(""))

	, curr_stock_med(_T(""))
	, v_consumption_med(_T(""))
	, consumend_quant_med(_T(""))
	, consume_animal_med(_T(""))
	, consumption_history_med(_T(""))
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
	DDX_Control(pDX, IDC_stock_description_combo, c_combodescriptionsmed);
	DDX_CBString(pDX, IDC_stock_description_combo, v_combodescriptionsmed);
	DDX_Text(pDX, IDC_Stock_Description2, new_stock_description);

	DDX_Text(pDX, IDC_CurrStockMedicine, curr_stock_med);
	DDX_Control(pDX, IDC_Combo_Consumption_med, c_consumption_med);
	DDX_CBString(pDX, IDC_Combo_Consumption_med, v_consumption_med);
	DDX_Text(pDX, IDC_Consumed_Quant_med, consumend_quant_med);
	DDX_Text(pDX, IDC_Consume_Animal_med, consume_animal_med);
	DDX_Text(pDX, IDC_HistoryStockMed, consumption_history_med);
}





BEGIN_MESSAGE_MAP(MyDlg11, CDialogEx)
	ON_BN_CLICKED(IDC_OrderFoodButton, &MyDlg11::OnBnClickedOrderfoodbutton)
	ON_CBN_SELCHANGE(IDC_stock_description_combo, &MyDlg11::OnCbnSelchangestockdescriptioncombo)
	ON_BN_CLICKED(IDC_New_item_order_button, &MyDlg11::OnBnClickedNewitemorderbutton)
	ON_CBN_SELCHANGE(IDC_Combo_Consumption_med, &MyDlg11::OnCbnSelchangeComboConsumptionmed)
	ON_BN_CLICKED(IDC_RegConsMed, &MyDlg11::OnBnClickedRegconsmed)
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
	vector<CString> medicine_IDs = MyConnection.VectorQuery(_T("stock_ID"), _T("stock"), _T("stock_type = 'Medicine'"));

	vector<CString> medicine_order_date = MyConnection.CheckMedicineOrderDate();
	vector<CString> medicine_order_quantity = MyConnection.CheckMedicineOrderQuantity();
	vector<CString> medicine_description = MyConnection.CheckMedicineDescription();
	CString str_list = _T("User ID | Stock ID | Order Date | Order Quantity | Description \r\n ------ \r\n");
	for (size_t i = 0; i < medicine_user_ID.size(); i++) {

		str_list = str_list + medicine_user_ID[i] + _T(" | ") + medicine_stock_ID[i] + _T(" | ") + medicine_order_date[i] + _T(" | ") + medicine_order_quantity[i] + _T(" | ") + medicine_description[i] + _T("\r\n");
	}
	medicine_history_list = str_list;

	CString str_list_2 = _T("Animal ID | Stock ID | Consumption Date | Consumption Quantity \r\n ------ \r\n");
	for (size_t i = 0; i < medicine_IDs.size(); i++) {
		vector<CString> info_consumption = MyConnection.CheckConsumption(medicine_IDs[i]);
		int k = 0;
		for (size_t j = 0; j < info_consumption.size(); j++) {
			if (k != 0) {
				str_list_2 = str_list_2 + _T(" | ") + info_consumption[j];
			}
			else {
				str_list_2 = str_list_2 + info_consumption[j];
			}
			if (k == 3) {
				str_list_2 = str_list_2 + _T("\r\n");
				k = 0;
			}
			else {
				k++;
			}
		}
	}
	consumption_history_med = str_list_2;

	CString str_list_3 = _T("Stock ID | Stock description | Unit value | Units in stock \r\n ------ \r\n");
	for (size_t i = 0; i < medicine_IDs.size(); i++) {
		CString s_description = MyConnection.SimpleQuery(_T("stock_description"), _T("stock"), _T("stock_ID"), medicine_IDs[i]);
		CString s_unit_value = MyConnection.SimpleQuery(_T("unit_value"), _T("stock"), _T("stock_ID"), medicine_IDs[i]);
		int sum_orders = _ttoi(MyConnection.Sum(_T("order_quantity"), _T("orders"), _T("stock_ID = ") + medicine_IDs[i]));
		int sum_consumes = _ttoi(MyConnection.Sum(_T("consume_quantity"), _T("consume"), _T("stock_ID = ") + medicine_IDs[i]));
		CString in_stock;
		in_stock.Format(_T("%d"), sum_orders + sum_consumes);
		str_list_3 = str_list_3 + medicine_IDs[i] + _T(" | ") + s_description + _T(" | ") + s_unit_value + _T(" | ") + in_stock + _T("\r\n");
	}
	curr_stock_med = str_list_3;

	UpdateData(FALSE);

	for (size_t i = 0; i < MyConnection.MedicineDescriptions().size(); i++)
	{
		CString medicinedescriptions = MyConnection.MedicineDescriptions()[i];
		c_combodescriptionsmed.AddString(medicinedescriptions);
		c_consumption_med.AddString(medicinedescriptions);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void MyDlg11::OnBnClickedOrderfoodbutton()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString msg_order;

	myconnectorclassDB MyConnection;
	MyConnection.connect();

	CString order_today_date = MyConnection.ReturnCurrentDate();

	if (!v_combodescriptionsmed.IsEmpty() && !order_stock_quantity.IsEmpty()) {
		vector<CString> orders_dates = MyConnection.VectorQuery(_T("order_date"), _T("orders"), _T("stock_ID = ") + MyConnection.SimpleQuery(_T("stock_ID"), _T("stock"), _T("stock_description"), v_combodescriptionsmed));
		if (std::find(orders_dates.begin(), orders_dates.end(), order_today_date) == orders_dates.end()) {
			int is_number = TRUE;
			for (int i = 0; i < order_stock_quantity.GetLength(); i++) {
				if (!isdigit(order_stock_quantity[i])) {
					is_number = FALSE;
				}
			}
			if (is_number) {

				CString order_stock_ID = MyConnection.CheckNewStockID(v_combodescriptionsmed);

				MyConnection.NewOrderOldDescription(userID_confirm, order_stock_ID, order_today_date, order_stock_quantity);

				CString pending_msg;
				pending_msg.Format(_T("Ordered!"));
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

				vector<CString> medicine_IDs = MyConnection.VectorQuery(_T("stock_ID"), _T("stock"), _T("stock_type = 'Medicine'"));
				CString str_list_3 = _T("Stock ID | Stock description | Unit value | Units in stock \r\n ------ \r\n");
				for (size_t i = 0; i < medicine_IDs.size(); i++) {
					CString s_description = MyConnection.SimpleQuery(_T("stock_description"), _T("stock"), _T("stock_ID"), medicine_IDs[i]);
					CString s_unit_value = MyConnection.SimpleQuery(_T("unit_value"), _T("stock"), _T("stock_ID"), medicine_IDs[i]);
					int sum_orders = _ttoi(MyConnection.Sum(_T("order_quantity"), _T("orders"), _T("stock_ID = ") + medicine_IDs[i]));
					int sum_consumes = _ttoi(MyConnection.Sum(_T("consume_quantity"), _T("consume"), _T("stock_ID = ") + medicine_IDs[i]));
					CString in_stock;
					in_stock.Format(_T("%d"), sum_orders + sum_consumes);
					str_list_3 = str_list_3 + medicine_IDs[i] + _T(" | ") + s_description + _T(" | ") + s_unit_value + _T(" | ") + in_stock + _T("\r\n");
				}
				curr_stock_med = str_list_3;

				new_stock_description = _T("");
				new_order_unit_value = _T("");

				UpdateData(FALSE);
			}
			else {
				msg_order.Format(_T("Error! Quantity should be an integer!"));
				AfxMessageBox(msg_order);
			}
		}
		else {
			msg_order.Format(_T("Error! Today's order has already been placed!"));
			AfxMessageBox(msg_order);
		}
	}
	else {
		msg_order.Format(_T("Error! Invalid input!"));
		AfxMessageBox(msg_order);
	}
}


void MyDlg11::OnCbnSelchangestockdescriptioncombo()
{
	// TODO: Add your control notification handler code here
	c_combodescriptionsmed.GetLBText(c_combodescriptionsmed.GetCurSel(), v_combodescriptionsmed);
	UpdateData(FALSE);
}


void MyDlg11::OnBnClickedNewitemorderbutton()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString msg;

	myconnectorclassDB MyConnection;
	MyConnection.connect();

	vector<CString> StocksDescriptions = MyConnection.VectorQuery(_T("stock_description"), _T("stock"), _T("stock_type = 'Medicine'"));

	if (!new_stock_description.IsEmpty() && !new_order_unit_value.IsEmpty()) {
		if (std::find(StocksDescriptions.begin(), StocksDescriptions.end(), new_stock_description) == StocksDescriptions.end()) {
			int is_number = TRUE;
			for (int i = 0; i < new_order_unit_value.GetLength(); i++) {
				if (!isdigit(new_order_unit_value[i])) {
					is_number = FALSE;
				}
			}
			if (is_number) {
				CString new_initial_quantity;
				new_initial_quantity = _T('0');
				CString stock_type_new = _T("Medicine");

				int new_stock_ID = _ttoi(MyConnection.LastStockID()) + 1;
				CString new_stock_ID_str;
				new_stock_ID_str.Format(_T("%d"), new_stock_ID);

				MyConnection.NewOrderNewDescription(new_stock_ID_str, stock_type_new, new_stock_description, new_initial_quantity, new_order_unit_value);

				c_combodescriptionsmed.ResetContent();
				c_consumption_med.ResetContent();
				for (size_t i = 0; i < MyConnection.FoodDescriptions().size(); i++)
				{
					CString fooddescriptions = MyConnection.FoodDescriptions()[i];
					c_combodescriptionsmed.AddString(fooddescriptions);
					c_consumption_med.AddString(fooddescriptions);
				}

				vector<CString> medicine_IDs = MyConnection.VectorQuery(_T("stock_ID"), _T("stock"), _T("stock_type = 'Medicine'"));
				CString str_list_3 = _T("Stock ID | Stock description | Unit value | Units in stock \r\n ------ \r\n");
				for (size_t i = 0; i < medicine_IDs.size(); i++) {
					CString s_description = MyConnection.SimpleQuery(_T("stock_description"), _T("stock"), _T("stock_ID"), medicine_IDs[i]);
					CString s_unit_value = MyConnection.SimpleQuery(_T("unit_value"), _T("stock"), _T("stock_ID"), medicine_IDs[i]);
					int sum_orders = _ttoi(MyConnection.Sum(_T("order_quantity"), _T("orders"), _T("stock_ID = ") + medicine_IDs[i]));
					int sum_consumes = _ttoi(MyConnection.Sum(_T("consume_quantity"), _T("consume"), _T("stock_ID = ") + medicine_IDs[i]));
					CString in_stock;
					in_stock.Format(_T("%d"), sum_orders + sum_consumes);
					str_list_3 = str_list_3 + medicine_IDs[i] + _T(" | ") + s_description + _T(" | ") + s_unit_value + _T(" | ") + in_stock + _T("\r\n");
				}
				curr_stock_med = str_list_3;

				v_combodescriptionsmed = _T("");
				order_stock_quantity = _T("");

				UpdateData(FALSE);

				vector<CString> responsible_IDs = MyConnection.VectorQuery(_T("user_ID"), _T("responsible"), _T("stock_ID = '") + medicine_IDs[0] + _T("'"));
				for (size_t i = 0; i < responsible_IDs.size(); i++) {
					MyConnection.SimpleInsert(_T("responsible"), _T("'") + responsible_IDs[i] + _T("', '") + new_stock_ID_str + _T("'"));
				}


				CString pending_msg;
				pending_msg.Format(_T("Item added!"));
				AfxMessageBox(pending_msg);
			}
			else {
				msg.Format(_T("Quantity should be an integer!"));
				AfxMessageBox(msg);
			}
		}
		else {
			msg.Format(_T("That description already exist!"));
			AfxMessageBox(msg);
		}
	}
	else {
		msg.Format(_T("Error! Invalid input!"));
		AfxMessageBox(msg);
	}
}

void MyDlg11::OnCbnSelchangeComboConsumptionmed()
{
	// TODO: Add your control notification handler code here
	c_consumption_med.GetLBText(c_consumption_med.GetCurSel(), v_consumption_med);
	UpdateData(FALSE);
}


void MyDlg11::OnBnClickedRegconsmed()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString msg_consumption;

	myconnectorclassDB MyConnection;
	MyConnection.connect();

	vector<CString> available_animals = MyConnection.CheckAvailableAnimalIDs();

	CString consumption_date = MyConnection.ReturnCurrentDate();

	if (!v_consumption_med.IsEmpty() && !v_consumption_med.IsEmpty() && !v_consumption_med.IsEmpty()) {
		if (std::find(available_animals.begin(), available_animals.end(), consume_animal_med) != available_animals.end()) {
			vector<CString> consumption_dates = MyConnection.VectorQuery(_T("consume_date"), _T("consume"), _T("stock_ID = ") + MyConnection.SimpleQuery(_T("stock_ID"), _T("stock"), _T("stock_description"), v_consumption_med) + _T(" AND animal_ID = ") + consume_animal_med);
			if (std::find(consumption_dates.begin(), consumption_dates.end(), consumption_date) == consumption_dates.end()) {
				int is_number = TRUE;
				for (int i = 0; i < consumend_quant_med.GetLength(); i++) {
					if (!isdigit(consumend_quant_med[i])) {
						is_number = FALSE;
					}
				}
				if (is_number) {
					int sum_orders = _ttoi(MyConnection.Sum(_T("order_quantity"), _T("orders"), _T("stock_ID = ") + MyConnection.SimpleQuery(_T("stock_ID"), _T("stock"), _T("stock_description"), v_consumption_med)));
					int sum_consumes = _ttoi(MyConnection.Sum(_T("consume_quantity"), _T("consume"), _T("stock_ID = ") + MyConnection.SimpleQuery(_T("stock_ID"), _T("stock"), _T("stock_description"), v_consumption_med)));
					int in_stock = sum_orders + sum_consumes;
					if (_ttoi(consumend_quant_med) <= in_stock) {
						CString stock_ID = MyConnection.SimpleQuery(_T("stock_ID"), _T("stock"), _T("stock_description"), v_consumption_med);

						CString c_consumption_quantity = _T("-") + consumend_quant_med;

						MyConnection.SimpleInsert(_T("consume"), consume_animal_med + _T(", ") + stock_ID + _T(", '") + consumption_date + _T("', ") + c_consumption_quantity);

						msg_consumption.Format(_T("Consumption registered!"));
						AfxMessageBox(msg_consumption);

						vector<CString> medicine_IDs = MyConnection.VectorQuery(_T("stock_ID"), _T("stock"), _T("stock_type = 'Medicine'"));

						CString str_list_2 = _T("Animal ID | Stock ID | Consumption Date | Consumption Quantity \r\n ------ \r\n");
						for (size_t i = 0; i < medicine_IDs.size(); i++) {
							vector<CString> info_consumption = MyConnection.CheckConsumption(medicine_IDs[i]);
							int k = 0;
							for (size_t j = 0; j < info_consumption.size(); j++) {
								if (k != 0) {
									str_list_2 = str_list_2 + _T(" | ") + info_consumption[j];
								}
								else {
									str_list_2 = str_list_2 + info_consumption[j];
								}
								if (k == 3) {
									str_list_2 = str_list_2 + _T("\r\n");
									k = 0;
								}
								else {
									k++;
								}
							}
						}
						consumption_history_med = str_list_2;

						CString str_list_3 = _T("Stock ID | Stock description | Unit value | Units in stock \r\n ------ \r\n");
						for (size_t i = 0; i < medicine_IDs.size(); i++) {
							CString s_description = MyConnection.SimpleQuery(_T("stock_description"), _T("stock"), _T("stock_ID"), medicine_IDs[i]);
							CString s_unit_value = MyConnection.SimpleQuery(_T("unit_value"), _T("stock"), _T("stock_ID"), medicine_IDs[i]);
							int sum_orders = _ttoi(MyConnection.Sum(_T("order_quantity"), _T("orders"), _T("stock_ID = ") + medicine_IDs[i]));
							int sum_consumes = _ttoi(MyConnection.Sum(_T("consume_quantity"), _T("consume"), _T("stock_ID = ") + medicine_IDs[i]));
							CString in_stock;
							in_stock.Format(_T("%d"), sum_orders + sum_consumes);
							str_list_3 = str_list_3 + medicine_IDs[i] + _T(" | ") + s_description + _T(" | ") + s_unit_value + _T(" | ") + in_stock + _T("\r\n");
						}
						curr_stock_med = str_list_3;

						v_consumption_med = _T("");
						consume_animal_med = _T("");
						consumend_quant_med = _T("");

						UpdateData(FALSE);
					}
					else {
						msg_consumption.Format(_T("Not enough units in stock!"));
						AfxMessageBox(msg_consumption);
					}
				}
				else {
					msg_consumption.Format(_T("Error! Quantity should be a positive integer!"));
					AfxMessageBox(msg_consumption);
				}
			}
			else {
				msg_consumption.Format(_T("Today's consumption has already been registed."));
				AfxMessageBox(msg_consumption);
			}
		}
		else {
			msg_consumption.Format(_T("Error! Invalid animal!"));
			AfxMessageBox(msg_consumption);
		}
	}
	else {
		msg_consumption.Format(_T("Error! Invalid input!"));
		AfxMessageBox(msg_consumption);
	}
}
