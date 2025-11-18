#pragma once
#include "afxdialogex.h"
#include "manager_h/MA_010101_NC_wheel_data.h"

// 需要导出的类需要添加宏定义：AFX_EXT_CLASS

#include "pch.h"
#include "framework.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// dialog_wheel_list 对话框

class AFX_EXT_CLASS dialog_wheel_list : public CDialogEx
{
	DECLARE_DYNAMIC(dialog_wheel_list)

public:
	dialog_wheel_list(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~dialog_wheel_list();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_wheel_list };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	wheel_dialog* wheel_ptr = nullptr;
	CListCtrl m_wheel_list;
	void set_list_init();
	void update_list(bool is_edi = 0);
	void open_wheel_edit(int data_pos);
	CButton m_open;
	CButton m_del;
	CButton m_ok;
	bool anzhuang_flag = 0;
	int anzhuang_pos = -1;
public:
	//是安装到砂轮组打开
	void is_anzhuang();
	//选砂轮时调用
	void is_xuanzhe();
	int get_anzhuang_pos();
	int get_xuanzhe_pos();
	void input_wheel_ptr(wheel_dialog* _ptr);
	//新建砂轮按键
	afx_msg void OnBnClickedButton_create_wheel();
	
	virtual BOOL OnInitDialog();
	//删除按键
	afx_msg void OnBnClickedButtoncreatewheel3();
	afx_msg void OnNMClickwheelList(NMHDR* pNMHDR, LRESULT* pResult);
	void No_Select(int nSelectedItem);
	//打开砂轮按键
	afx_msg void OnBnClickedButtoncreatewheel2();
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
	afx_msg void OnBnClickedOk();
};
