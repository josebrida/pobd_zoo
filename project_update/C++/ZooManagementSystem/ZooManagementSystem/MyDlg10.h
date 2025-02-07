#pragma once


// MyDlg10 dialog

class MyDlg10 : public CDialogEx
{
	DECLARE_DYNAMIC(MyDlg10)

public:
	MyDlg10(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MyDlg10();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FoodDialog };
#endif

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CString food_history_list;
	BOOL see_history_food_list;
	afx_msg void OnBnClickedOrderfoodbutton();
	CString order_stock_description;
	CString order_stock_quantity;
	CString new_order_stock_description;
	CString new_order_unit_value;
	CString userID_confirm;
	CComboBox c_combodescriptions;
	CString v_combodescriptions;
	afx_msg void OnCbnSelchangestockdescriptioncombo();
	CString order_stock_ID;
	CString order_today_date;
	CString first_quantity;
	afx_msg void OnBnClickedNewitemorderbutton();
	CString consumption_histoty;
	CString consumption_quantity;
	CString consumption_animal;
	CComboBox c_combo_consumption;
	CString v_combo_consumption;
	CString curr_stock;
	afx_msg void OnBnClickedConsumptionbutton();
	afx_msg void OnCbnSelchangeComboConsumption();
	CString new_stock_description;
};
