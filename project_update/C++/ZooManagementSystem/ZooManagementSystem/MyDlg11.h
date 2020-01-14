#pragma once


// MyDlg11 dialog

class MyDlg11 : public CDialogEx
{
	DECLARE_DYNAMIC(MyDlg11)

public:
	MyDlg11(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MyDlg11();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MedicineDialog };
#endif

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CString medicine_history_list;
	BOOL see_history_food_list;
	afx_msg void OnBnClickedOrderfoodbutton();
	CString order_stock_description;
	CString order_stock_quantity;
	CString new_order_stock_description;
	CString new_order_unit_value;
	CString userID_confirm;
	CComboBox c_combodescriptionsmed;
	CString v_combodescriptionsmed;
	afx_msg void OnCbnSelchangestockdescriptioncombo();
	CString order_stock_ID;
	CString order_today_date;
	CString new_stock_description;
	CString first_quantity;
	afx_msg void OnBnClickedNewitemorderbutton();

	CString curr_stock_med;
	CComboBox c_consumption_med;
	CString v_consumption_med;
	CString consumend_quant_med;
	CString consume_animal_med;
	CString consumption_history_med;
	afx_msg void OnCbnSelchangeComboConsumptionmed();
	afx_msg void OnBnClickedRegconsmed();
};