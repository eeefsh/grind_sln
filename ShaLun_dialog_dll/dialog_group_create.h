#pragma once
#include "afxdialogex.h"
#include "manager_h/MA_010101_NC_wheel_data.h"

// 需要导出的类需要添加宏定义：AFX_EXT_CLASS

#include "pch.h"
#include "framework.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// dialog_group_create 对话框

class AFX_EXT_CLASS dialog_group_create : public CDialogEx
{
	DECLARE_DYNAMIC(dialog_group_create)

public:
	dialog_group_create(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~dialog_group_create();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_group_create };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	bool name_flag = 0;
	int temp_row = -1;
	wheel_dialog_namespace::canshu_Shalun_group canshu;	//已安装砂轮
	int group_id = -1;
	void set_list_init();
	void set_Select_canshu(int nSelectedItem);
	wheel_dialog* wheel_ptr = nullptr;
	void insert_a_list(int wheel_pos);
	void No_Select(int nSelectedItem);
	void add_wheel_show();
	void get_canshu_wheel(int nSelectedItem);
	void open_Init();
	void save_data();
	CListCtrl m_list;
public:
	//是打开砂轮组
	void is_open_group(int pos);
	void input_wheel_ptr(wheel_dialog* _ptr);
	virtual BOOL OnInitDialog();
	//砂轮组上安装砂轮
	afx_msg void OnBnClickedButton_anzhuang();
	afx_msg void OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	CButton m_del;
	CButton m_cankao_nei;
	CButton m_cankao_wai;
	CEdit m_falan;
	CButton m_add_wheel;
	afx_msg void OnBnClickedRadio_cankao_nei();
	afx_msg void OnBnClickedRadio_cankao_wai();
	afx_msg void OnEnKillfocusEdit_falan();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	CEdit m_name;
	CEdit m_gan_D;
	CEdit m_luomao_D;
	CEdit m_luomao_L;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnChangeEdit_name();
};
