#pragma once
#include "afxdialogex.h"
#include "manager_h/MA_010101_NC_wheel_data.h"
#include "manager_h/MA_010101_MFC_CustomControl.h"

#include "pch.h"
#include "framework.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// dialog_Ping_shalun 对话框

class AFX_EXT_CLASS dialog_Ping_shalun : public CDialogEx
{
	DECLARE_DYNAMIC(dialog_Ping_shalun)

public:
	dialog_Ping_shalun(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~dialog_Ping_shalun();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Ping_shalun };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	int buff_wheel_pos = -1;
	bool is_open = 0;
	wheel_dialog* wheel_ptr = nullptr;
	wheel_dialog_namespace::canshu_Ping_shalun canshu;
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
private:
	bool name_flag = 0;
	CButton daozhuang_1;
	CButton daozhuang_2;
	CEdit m_Dadaun_D;
	CEdit m_Xiaoduan_D;
	CEdit m_Daduan_yuanjiao_r;
	CEdit m_Xiaoduan_yuanjiao_r;
	CEdit m_Jiaodu;
	CEdit m_Kuandu;
	CButton Celiang_Daduan;
	CButton Celiang_Xiaoduan;
	CEdit m_name;

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit_name();

	void set_draw();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnEnKillfocusEdit2();
	afx_msg void OnEnKillfocusEdit3();
	afx_msg void OnEnKillfocusEdit4();
	afx_msg void OnEnKillfocusEdit5();
	afx_msg void OnEnKillfocusEdit6();
	DrawCtrl m_draw;
	afx_msg void OnBnClickedRadiodaozhuang1();
	afx_msg void OnBnClickedRadiodaozhuang2();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
