#pragma once
#include "afxdialogex.h"
#include "manager_h/MA_010101_NC_wheel_data.h"

// 需要导出的类需要添加宏定义：AFX_EXT_CLASS

#include "pch.h"
#include "framework.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// dialog_group_list 对话框

class AFX_EXT_CLASS dialog_group_list : public CDialogEx
{
	DECLARE_DYNAMIC(dialog_group_list)

public:
	dialog_group_list(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~dialog_group_list();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_group_list };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	wheel_dialog* wheel_ptr = nullptr;
	bool is_xuanzhe_flag = 0;
	int group_pos = -1;
	CListCtrl m_group_list;
	void set_list_init();
	void update_list(int num = -1);
	void No_Select(int nSelectedItem);
public:
	void input_wheel_ptr(wheel_dialog* _ptr);
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	void is_Xuanzhe();
	int get_Xuanzhe_pos();
	afx_msg void OnBnClickedButton2();
	CButton m_open;
	CButton m_del;
	afx_msg void OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton3();
	CButton m_ok;
	afx_msg void OnBnClickedOk();
};