#pragma once
#include "afxdialogex.h"
#include"manager_h/MA_010101_NC_wheel_data.h"

// 需要导出的类需要添加宏定义：AFX_EXT_CLASS

#include "pch.h"
#include "framework.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// dialog_wheel_create 对话框

class AFX_EXT_CLASS dialog_wheel_create : public CDialogEx
{
	DECLARE_DYNAMIC(dialog_wheel_create)

public:
	dialog_wheel_create(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~dialog_wheel_create();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_wheel_create };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	wheel_dialog* wheel_ptr = nullptr;
public:
	void input_wheel_ptr(wheel_dialog* _ptr);
private:
	CButton Ping_shalun;
	CButton Beixing_shalun;
	CButton Yuanjiao_shalun;
	CButton Diexing_shalun;
	CButton DXF_shalun;
	CButton Jianjiao_shalun;
	
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
