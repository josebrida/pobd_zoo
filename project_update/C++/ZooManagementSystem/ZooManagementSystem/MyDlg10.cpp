// MyDlg10.cpp : implementation file
//
// MyDlg10.cpp : implementation file


#include "stdafx.h"
#include "ZooManagementSystem.h"
#include "ZooManagementSystemDlg.h"
#include "MyDlg10.h"
#include "MyDlg4.h"
#include "afxdialogex.h"
#include "myconnectorclassDB.h"
#include <stdlib.h>
#include <list>




// MyDlg10 dialog

IMPLEMENT_DYNAMIC(MyDlg10, CDialogEx)

MyDlg10::MyDlg10(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FoodDialog, pParent)
	, food_history_list(_T(""))
	, see_history_food_list(FALSE)
	, order_stock_description(_T(""))
	, order_stock_quantity(_T(""))
	, new_order_stock_description(_T(""))
	, new_order_unit_value(_T(""))
	, userID_confirm(_T(""))
	, v_combodescriptions(_T(""))
	, order_stock_ID(_T(""))
	, new_stock_description(_T(""))
	, first_quantity(_T(""))

	, consumption_histoty(_T(""))
	, consumption_quantity(_T(""))
	, consumption_animal(_T(""))
	, v_combo_consumption(_T(""))
	, curr_stock(_T(""))
{

}



MyDlg10::~MyDlg10()
{
}

void MyDlg10::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_food_history_list, food_history_list);
	DDX_Text(pDX, IDC_Order_Quantity, order_stock_quantity);
	DDX_Text(pDX, IDC_new_stock_unitvalue, new_order_unit_value);
	DDX_Control(pDX, IDC_stock_description_combo, c_combodescriptions);
	DDX_CBString(pDX, IDC_stock_description_combo, v_combodescriptions);
	DDX_Text(pDX, IDC_Stock_Description2, new_stock_description);

	DDX_Text(pDX, IDC_food_consumption, consumption_histoty);
	DDX_Text(pDX, IDC_ConsumptionQuantity, consumption_quantity);
	DDX_Text(pDX, IDC_AnimalConsumption, consumption_animal);
	DDX_Control(pDX, IDC_COMBO_Consumption, c_combo_consumption);
	DDX_CBString(pDX, IDC_COMBO_Consumption, v_combo_consumption);
	DDX_Text(pDX, IDC_CurrentStock, curr_stock);
	DDX_Text(pDX, IDC_Stock_Description2, new_stock_description);
}





BEGIN_MESSAGE_MAP(MyDlg10, CDialogEx)
	ON_BN_CLICKED(IDC_OrderFoodButton, &MyDlg10::OnBnClickedOrderfoodbutton)
	ON_CBN_SELCHANGE(IDC_stock_description_combo, &MyDlg10::OnCbnSelchangestockdescriptioncombo)
	ON_BN_CLICKED(IDC_New_item_order_button, &MyDlg10::OnBnClickedNewitemorderbutton)
	ON_BN_CLICKED(IDC_ConsumptionButton, &MyDlg10::OnBnClickedConsumptionbutton)
	ON_CBN_SELCHANGE(IDC_COMBO_Consumption, &MyDlg10::OnCbnSelchangeComboConsumption)
END_MESSAGE_MAP()


// MyDlg10 message handlers



BOOL MyDlg10::OnInitDialog()
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
	vector<CString> food_user_ID = MyConnection.CheckFoodUserID();
	vector<CString> food_stock_ID = MyConnection.CheckFoodStockID();
	vector<CString> food_IDs = MyConnection.VectorQuery(_T("stock_ID"), _T("stock"), _T("stock_type = 'Food'"));

	vector<CString> food_order_date = MyConnection.CheckFoodOrderDate();
	vector<CString> food_order_quantity = MyConnection.CheckFoodOrderQuantity();
	vector<CString> food_description = MyConnection.CheckFoodDescription();
	CString str_list = _T("User ID | Stock ID | Order Date | Order Quantity | Description \r\n ------ \r\n");
	for (size_t i = 0; i < food_user_ID.size(); i++) {

		str_list = str_list + food_user_ID[i] + _T(" | ") + food_stock_ID[i] + _T(" | ") + food_order_date[i] + _T(" | ") + food_order_quantity[i] + _T(" | ") + food_description[i] + _T("\r\n");
	}
	food_history_list = str_list;

	CString str_list_2 = _T("Animal ID | Stock ID | Consumption Date | Consumption Quantity \r\n ------ \r\n");
	for (size_t i = 0; i < food_IDs.size(); i++) {
		vector<CString> info_consumption = MyConnection.CheckConsumption(food_IDs[i]);
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
	consumption_histoty = str_list_2;

	CString str_list_3 = _T("Stock ID | Stock description | Unit value | Units in stock \r\n ------ \r\n");
	for (size_t i = 0; i < food_IDs.size(); i++) {
		CString s_description = MyConnection.SimpleQuery(_T("stock_description"), _T("stock"), _T("stock_ID"), food_IDs[i]);
		CString s_unit_value = MyConnection.SimpleQuery(_T("unit_value"), _T("stock"), _T("stock_ID"), food_IDs[i]);
		int sum_orders = _ttoi(MyConnection.Sum(_T("order_quantity"), _T("orders"), _T("stock_ID = ") + food_IDs[i]));
		int sum_consumes = _ttoi(MyConnection.Sum(_T("consume_quantity"), _T("consume"), _T("stock_ID = ") + food_IDs[i]));
		CString in_stock;
		in_stock.Format(_T("%d"), sum_orders + sum_consumes);
		str_list_3 = str_list_3 + food_IDs[i] + _T(" | ") + s_description + _T(" | ") + s_unit_value + _T(" | ") + in_stock + _T("\r\n");
	}
	curr_stock = str_list_3;

	UpdateData(FALSE);



	for (size_t i = 0; i < MyConnection.FoodDescriptions().size(); i++)
	{
		CString fooddescriptions = MyConnection.FoodDescriptions()[i];
		c_combodescriptions.AddString(fooddescriptions);
		c_combo_consumption.AddString(fooddescriptions);
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}


void MyDlg10::OnBnClickedOrderfoodbutton()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString msg_order;

	myconnectorclassDB MyConnection;
	MyConnection.connect();

	CString order_today_date = MyConnection.ReturnCurrentDate();

	if (!v_combodescriptions.IsEmpty() && !order_stock_quantity.IsEmpty()) {
		vector<CString> orders_dates = MyConnection.VectorQuery(_T("order_date"), _T("orders"), _T("stock_ID = ") + MyConnection.SimpleQuery(_T("stock_ID"), _T("stock"), _T("stock_description"), v_combodescriptions));
		if (std::find(orders_dates.begin(), orders_dates.end(), order_today_date) == orders_dates.end()) {
			int is_number = TRUE;
			for (int i = 0; i < order_stock_quantity.GetLength(); i++) {
				if (!isdigit(order_stock_quantity[i])) {
					is_number = FALSE;
				}
			}
			if (is_number) {

				CString order_stock_ID = MyConnection.CheckNewStockID(v_combodescriptions);

				MyConnection.NewOrderOldDescription(userID_confirm, order_stock_ID, order_today_date, order_stock_quantity);

				CString pending_msg;
				pending_msg.Format(_T("Ordered!"));
				AfxMessageBox(pending_msg);

				vector<CString> food_user_ID = MyConnection.CheckFoodUserID();
				vector<CString> food_stock_ID = MyConnection.CheckFoodStockID();
				vector<CString> food_order_date = MyConnection.CheckFoodOrderDate();
				vector<CString> food_order_quantity = MyConnection.CheckFoodOrderQuantity();
				vector<CString> food_description = MyConnection.CheckFoodDescription();
				CString str_list = _T("User ID | Stock ID | Order Date | Order Quantity | Description \r\n ------ \r\n");
				for (size_t i = 0; i < food_user_ID.size(); i++) {

					str_list = str_list + food_user_ID[i] + _T(" | ") + food_stock_ID[i] + _T(" | ") + food_order_date[i] + _T(" | ") + food_order_quantity[i] + _T(" | ") + food_description[i] + _T("\r\n");
				}
				food_history_list = str_list;

				vector<CString> food_IDs = MyConnection.VectorQuery(_T("stock_ID"), _T("stock"), _T("stock_type = 'Food'"));
				CString str_list_3 = _T("Stock ID | Stock description | Unit value | Units in stock \r\n ------ \r\n");
				for (size_t i = 0; i < food_IDs.size(); i++) {
					CString s_description = MyConnection.SimpleQuery(_T("stock_description"), _T("stock"), _T("stock_ID"), food_IDs[i]);
					CString s_unit_value = MyConnection.SimpleQuery(_T("unit_value"), _T("stock"), _T("stock_ID"), food_IDs[i]);
					int sum_orders = _ttoi(MyConnection.Sum(_T("order_quantity"), _T("orders"), _T("stock_ID = ") + food_IDs[i]));
					int sum_consumes = _ttoi(MyConnection.Sum(_T("consume_quantity"), _T("consume"), _T("stock_ID = ") + food_IDs[i]));
					CString in_stock;
					in_stock.Format(_T("%d"), sum_orders + sum_consumes);
					str_list_3 = str_list_3 + food_IDs[i] + _T(" | ") + s_description + _T(" | ") + s_unit_value + _T(" | ") + in_stock + _T("\r\n");
				}
				curr_stock = str_list_3;

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


void MyDlg10::OnCbnSelchangestockdescriptioncombo()
{
	// TODO: Add your control notification handler code here
	c_combodescriptions.GetLBText(c_combodescriptions.GetCurSel(), v_combodescriptions);
	UpdateData(FALSE);
}


void MyDlg10::OnBnClickedNewitemorderbutton()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString msg;

	myconnectorclassDB MyConnection;
	MyConnection.connect();

	vector<CString> StocksDescriptions = MyConnection.VectorQuery(_T("stock_description"), _T("stock"), _T("stock_type = 'Food'"));

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
				CString stock_type_new = _T("Food");

				int new_stock_ID = _ttoi(MyConnection.LastStockID()) + 1;
				CString new_stock_ID_str;
				new_stock_ID_str.Format(_T("%d"), new_stock_ID);

				MyConnection.NewOrderNewDescription(new_stock_ID_str, stock_type_new, new_stock_description, new_initial_quantity, new_order_unit_value);

				c_combodescriptions.ResetContent();
				c_combo_consumption.ResetContent();
				for (size_t i = 0; i < MyConnection.FoodDescriptions().size(); i++)
				{
					CString fooddescriptions = MyConnection.FoodDescriptions()[i];
					c_combodescriptions.AddString(fooddescriptions);
					c_combo_consumption.AddString(fooddescriptions);
				}

				vector<CString> food_IDs = MyConnection.VectorQuery(_T("stock_ID"), _T("stock"), _T("stock_type = 'Food'"));
				CString str_list_3 = _T("Stock ID | Stock description | Unit value | Units in stock \r\n ------ \r\n");
				for (size_t i = 0; i < food_IDs.size(); i++) {
					CString s_description = MyConnection.SimpleQuery(_T("stock_description"), _T("stock"), _T("stock_ID"), food_IDs[i]);
					CString s_unit_value = MyConnection.SimpleQuery(_T("unit_value"), _T("stock"), _T("stock_ID"), food_IDs[i]);
					int sum_orders = _ttoi(MyConnection.Sum(_T("order_quantity"), _T("orders"), _T("stock_ID = ") + food_IDs[i]));
					int sum_consumes = _ttoi(MyConnection.Sum(_T("consume_quantity"), _T("consume"), _T("stock_ID = ") + food_IDs[i]));
					CString in_stock;
					in_stock.Format(_T("%d"), sum_orders + sum_consumes);
					str_list_3 = str_list_3 + food_IDs[i] + _T(" | ") + s_description + _T(" | ") + s_unit_value + _T(" | ") + in_stock + _T("\r\n");
				}
				curr_stock = str_list_3;

				v_combodescriptions = _T("");
				order_stock_quantity = _T("");

				UpdateData(FALSE);

				vector<CString> responsible_IDs = MyConnection.VectorQuery(_T("user_ID"), _T("responsible"), _T("stock_ID = '") + food_IDs[0] + _T("'"));
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


void MyDlg10::OnBnClickedConsumptionbutton()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CString msg_consumption;

	myconnectorclassDB MyConnection;
	MyConnection.connect();

	vector<CString> available_animals = MyConnection.CheckAvailableAnimalIDs();

	CString consumption_date = MyConnection.ReturnCurrentDate();

	if (!v_combo_consumption.IsEmpty() && !consumption_quantity.IsEmpty() && !consumption_animal.IsEmpty()) {
		if (std::find(available_animals.begin(), available_animals.end(), consumption_animal) != available_animals.end()) {
			vector<CString> consumption_dates = MyConnection.VectorQuery(_T("consume_date"), _T("consume"), _T("stock_ID = ") + MyConnection.SimpleQuery(_T("stock_ID"), _T("stock"), _T("stock_description"), v_combo_consumption) + _T(" AND animal_ID = ") + consumption_animal);
			if (std::find(consumption_dates.begin(), consumption_dates.end(), consumption_date) == consumption_dates.end()) {
				int is_number = TRUE;
				for (int i = 0; i < consumption_quantity.GetLength(); i++) {
					if (!isdigit(consumption_quantity[i])) {
						is_number = FALSE;
					}
				}
				if (is_number) {
					int sum_orders = _ttoi(MyConnection.Sum(_T("order_quantity"), _T("orders"), _T("stock_ID = ") + MyConnection.SimpleQuery(_T("stock_ID"), _T("stock"), _T("stock_description"), v_combo_consumption)));
					int sum_consumes = _ttoi(MyConnection.Sum(_T("consume_quantity"), _T("consume"), _T("stock_ID = ") + MyConnection.SimpleQuery(_T("stock_ID"), _T("stock"), _T("stock_description"), v_combo_consumption)));
					int in_stock = sum_orders + sum_consumes;
					if (_ttoi(consumption_quantity) <= in_stock) {
						CString stock_ID = MyConnection.SimpleQuery(_T("stock_ID"), _T("stock"), _T("stock_description"), v_combo_consumption);

						CString c_consumption_quantity = _T("-") + consumption_quantity;

						MyConnection.SimpleInsert(_T("consume"), consumption_animal + _T(", ") + stock_ID + _T(", '") + consumption_date + _T("', ") + c_consumption_quantity);

						msg_consumption.Format(_T("Consumption registered!"));
						AfxMessageBox(msg_consumption);

						vector<CString> food_IDs = MyConnection.VectorQuery(_T("stock_ID"), _T("stock"), _T("stock_type = 'Food'"));

						CString str_list_2 = _T("Animal ID | Stock ID | Consumption Date | Consumption Quantity \r\n ------ \r\n");
						for (size_t i = 0; i < food_IDs.size(); i++) {
							vector<CString> info_consumption = MyConnection.CheckConsumption(food_IDs[i]);
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
						consumption_histoty = str_list_2;

						CString str_list_3 = _T("Stock ID | Stock description | Unit value | Units in stock \r\n ------ \r\n");
						for (size_t i = 0; i < food_IDs.size(); i++) {
							CString s_description = MyConnection.SimpleQuery(_T("stock_description"), _T("stock"), _T("stock_ID"), food_IDs[i]);
							CString s_unit_value = MyConnection.SimpleQuery(_T("unit_value"), _T("stock"), _T("stock_ID"), food_IDs[i]);
							int sum_orders = _ttoi(MyConnection.Sum(_T("order_quantity"), _T("orders"), _T("stock_ID = ") + food_IDs[i]));
							int sum_consumes = _ttoi(MyConnection.Sum(_T("consume_quantity"), _T("consume"), _T("stock_ID = ") + food_IDs[i]));
							CString in_stock;
							in_stock.Format(_T("%d"), sum_orders + sum_consumes);
							str_list_3 = str_list_3 + food_IDs[i] + _T(" | ") + s_description + _T(" | ") + s_unit_value + _T(" | ") + in_stock + _T("\r\n");
						}
						curr_stock = str_list_3;

						v_combo_consumption = _T("");
						consumption_animal = _T("");
						consumption_quantity = _T("");

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


void MyDlg10::OnCbnSelchangeComboConsumption()
{
	// TODO: Add your control notification handler code here
	c_combo_consumption.GetLBText(c_combo_consumption.GetCurSel(), v_combo_consumption);
	UpdateData(FALSE);
}
