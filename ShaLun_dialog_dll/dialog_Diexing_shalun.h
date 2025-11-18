#pragma once
#include "afxdialogex.h"
#include "manager_h/MA_010101_NC_wheel_data.h"
#include "manager_h/MA_010101_MFC_CustomControl.h"

// 需要导出的类需要添加宏定义：AFX_EXT_CLASS

#include "pch.h"
#include "framework.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// dialog_Diexing_shalun 对话框

class AFX_EXT_CLASS dialog_Diexing_shalun : public CDialogEx
{
	DECLARE_DYNAMIC(dialog_Diexing_shalun)

public:
	dialog_Diexing_shalun(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~dialog_Diexing_shalun();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Diexing_shalun };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	bool name_flag = 0;
	int buff_wheel_pos = -1;
	bool is_open = 0;
	wheel_dialog* wheel_ptr = nullptr;
	wheel_dialog_namespace::canshu_Diexing_shalun canshu;
	//初始化界面参数
	void init_canshu();
	void updata_show();
	//获取界面参数
	void get_canshu();
	//保存
	void save_canshu();
	void set_draw();
public:
	void input_wheel_pos(int pos);
	void input_wheel_ptr(wheel_dialog* _ptr);
	CEdit m_name;
	CEdit m_Zhijing;
	CEdit m_Yuanjiao;
	CEdit m_Jiaodu;
	CEdit m_Kuandu;
	CButton m_Nei;
	CButton m_Wai;
	afx_msg void OnBnClickedOk();
	DrawCtrl m_draw;
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnEnKillfocusEdit2();
	afx_msg void OnEnKillfocusEdit3();
	afx_msg void OnEnKillfocusEdit4();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnEnChangeEdit_name();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
