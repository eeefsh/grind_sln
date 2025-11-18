#pragma once
#include "afxdialogex.h"
#include "manager_h/MA_010101_NC_wheel_data.h"

// 需要导出的类需要添加宏定义：AFX_EXT_CLASS

#include "pch.h"
#include "framework.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <afxeditbrowsectrl.h>

// dialog_DXF_shalun 对话框

class AFX_EXT_CLASS dialog_DXF_shalun : public CDialogEx
{
	DECLARE_DYNAMIC(dialog_DXF_shalun)

public:
	dialog_DXF_shalun(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~dialog_DXF_shalun();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DXF_shalun };
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
	wheel_dialog_namespace::canshu_DXF_shalun canshu;
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
	CMFCEditBrowseCtrl m_dir;
	CEdit m_Yuanjiao;
	CEdit m_Zhijing;
	CEdit m_Zhouxiang;
	afx_msg void OnBnClickedOk();
};
