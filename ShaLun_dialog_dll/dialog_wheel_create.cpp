// dialog_wheel_create.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "resource.h"
#include "dialog_wheel_create.h"
#include "dialog_Ping_shalun.h"
#include "dialog_Beixing_shalun.h"
#include "dialog_Diexing_shalun.h"
#include "dialog_Yuanjiao_shalun.h"
#include "dialog_DXF_shalun.h"
#include "dialog_Jianjiao_shalun.h"
// dialog_wheel_create 对话框

IMPLEMENT_DYNAMIC(dialog_wheel_create, CDialogEx)

dialog_wheel_create::dialog_wheel_create(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_wheel_create, pParent)
{

}

dialog_wheel_create::~dialog_wheel_create()
{
}

void dialog_wheel_create::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1_wheel, Ping_shalun);
	DDX_Control(pDX, IDC_RADIO2_wheel, Beixing_shalun);
	DDX_Control(pDX, IDC_RADIO3_wheel, Yuanjiao_shalun);
	DDX_Control(pDX, IDC_RADIO4_wheel, Diexing_shalun);
	DDX_Control(pDX, IDC_RADIO5_wheel, DXF_shalun);
	DDX_Control(pDX, IDC_RADIO6_wheel, Jianjiao_shalun);
}

void dialog_wheel_create::input_wheel_ptr(wheel_dialog* _ptr)
{
	wheel_ptr = _ptr;
}


BEGIN_MESSAGE_MAP(dialog_wheel_create, CDialogEx)
	ON_BN_CLICKED(IDOK, &dialog_wheel_create::OnBnClickedOk)
END_MESSAGE_MAP()


// dialog_wheel_create 消息处理程序

BOOL dialog_wheel_create::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Ping_shalun.SetCheck(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void dialog_wheel_create::OnBnClickedOk()
{
	int is_ok = 0;
	if (Ping_shalun.GetCheck() == BST_CHECKED)
	{
		dialog_Ping_shalun* Ping_shalun = new dialog_Ping_shalun;
		Ping_shalun->input_wheel_ptr(wheel_ptr);
		is_ok = Ping_shalun->DoModal();
		delete Ping_shalun;
	}
	else if (Beixing_shalun.GetCheck() == BST_CHECKED)
	{
		dialog_Beixing_shalun* Beixing_shalun = new dialog_Beixing_shalun;
		Beixing_shalun->input_wheel_ptr(wheel_ptr);
		is_ok = Beixing_shalun->DoModal();
		delete Beixing_shalun;
	}
	else if (Yuanjiao_shalun.GetCheck() == BST_CHECKED)
	{
		dialog_Yuanjiao_shalun* Yuanjiao_shalun = new dialog_Yuanjiao_shalun;
		Yuanjiao_shalun->input_wheel_ptr(wheel_ptr);
		is_ok = Yuanjiao_shalun->DoModal();
		delete Yuanjiao_shalun;
	}
	else if (Diexing_shalun.GetCheck() == BST_CHECKED)
	{
		dialog_Diexing_shalun* Diexing_shalun = new dialog_Diexing_shalun;
		Diexing_shalun->input_wheel_ptr(wheel_ptr);
		is_ok = Diexing_shalun->DoModal();
		delete Diexing_shalun;
	}
	else if (DXF_shalun.GetCheck() == BST_CHECKED)
	{
		dialog_DXF_shalun* DXF_shalun = new dialog_DXF_shalun;
		DXF_shalun->input_wheel_ptr(wheel_ptr);
		is_ok = DXF_shalun->DoModal();
		delete DXF_shalun;
	}
	else if (Jianjiao_shalun.GetCheck() == BST_CHECKED)
	{
		dialog_Jianjiao_shalun* Jianjiao_shalun = new dialog_Jianjiao_shalun;
		Jianjiao_shalun->input_wheel_ptr(wheel_ptr);
		is_ok = Jianjiao_shalun->DoModal();
		delete Jianjiao_shalun;
	}
	if (is_ok == IDOK)
	{
		CDialogEx::OnOK();
	}
}
