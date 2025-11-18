#pragma once
#include "afxdialogex.h"
#include "manager_h/MA_010101_MFC_CustomControl.h"
#include "manager_h/MA_010101_NC_wheel_data.h"

// 需要导出的类需要添加宏定义：AFX_EXT_CLASS

#include "pch.h"
#include "framework.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// dialog_Beixing_shalun 对话框

class AFX_EXT_CLASS dialog_Beixing_shalun : public CDialogEx
{
	DECLARE_DYNAMIC(dialog_Beixing_shalun)

public:
	dialog_Beixing_shalun(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~dialog_Beixing_shalun();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Beixing_shalun };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	bool name_flag = 0;
	int buff_wheel_pos = -1;
	bool is_open = 0;
	wheel_dialog* wheel_ptr = nullptr;
	wheel_dialog_namespace::canshu_Beixing_shalun canshu;

	void set_draw();
	//初始化界面参数
	void init_canshu();
	void updata_show();
	//获取界面参数
	void get_canshu();
	//计算参数
	void jisuan_canshu();
	//保存
	void save_canshu();
public:
	void input_wheel_pos(int pos);
	void input_wheel_ptr(wheel_dialog* _ptr);
	CEdit m_name;
	CEdit m_Zhijing_D;
	CEdit m_Yuanjiao;
	CEdit m_Kuandu;
	CEdit m_Neishen;
	CButton m_auto_Neishen;
	CEdit m_Moliao;
	CEdit m_Jiao_nei;
	CEdit m_Jiao_wai;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnEnKillfocusEdit3();
	DrawCtrl m_draw;
	afx_msg void OnEnChangeEdit_name();
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnEnKillfocusEdit2();
	afx_msg void OnEnKillfocusEdit4();
	afx_msg void OnEnKillfocusEdit5();
	afx_msg void OnEnKillfocusEdit6();
	afx_msg void OnEnKillfocusEdit8();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
