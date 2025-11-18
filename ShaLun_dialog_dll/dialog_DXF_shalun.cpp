// dialog_DXF_shalun.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "dialog_DXF_shalun.h"
#include "resource.h"

// dialog_DXF_shalun 对话框

IMPLEMENT_DYNAMIC(dialog_DXF_shalun, CDialogEx)

dialog_DXF_shalun::dialog_DXF_shalun(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DXF_shalun, pParent)
{

}

dialog_DXF_shalun::~dialog_DXF_shalun()
{
}

void dialog_DXF_shalun::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT7, m_name);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_dir);
	DDX_Control(pDX, IDC_EDIT1, m_Yuanjiao);
	DDX_Control(pDX, IDC_EDIT2, m_Zhijing);
	DDX_Control(pDX, IDC_EDIT3, m_Zhouxiang);
}


BEGIN_MESSAGE_MAP(dialog_DXF_shalun, CDialogEx)
	ON_BN_CLICKED(IDOK, &dialog_DXF_shalun::OnBnClickedOk)
END_MESSAGE_MAP()


// dialog_DXF_shalun 消息处理程序

BOOL dialog_DXF_shalun::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	init_canshu();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void dialog_DXF_shalun::init_canshu()
{
	CString strValue;
	if (is_open)
	{
		canshu.To_dialog_data(wheel_ptr->read_wheel(buff_wheel_pos));
		strValue = canshu.name.c_str();
		m_name.SetWindowTextW(strValue);
	}
	updata_show();
}

void dialog_DXF_shalun::updata_show()
{
	CString strValue;

	strValue.Format(_T("%.3f"), canshu.Yuanjiao_r);
	m_Yuanjiao.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.Zhijing_D);
	m_Zhijing.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.Zhouxiang);
	m_Zhouxiang.SetWindowTextW(strValue);
	
	strValue = canshu.dxf_dir.c_str();
	m_dir.SetWindowTextW(strValue);
}

void dialog_DXF_shalun::get_canshu()
{
	CString temp;

	m_Yuanjiao.GetWindowTextW(temp);
	canshu.Yuanjiao_r = _tstof(temp);

	m_Zhijing.GetWindowTextW(temp);
	canshu.Zhijing_D = _tstof(temp);

	m_Zhouxiang.GetWindowTextW(temp);
	canshu.Zhouxiang = _tstof(temp);

	m_name.GetWindowTextW(temp);
	CT2CA temp_str(temp);
	canshu.name = temp_str;

	m_dir.GetWindowTextW(temp);
	CT2CA temp_str1(temp);
	canshu.dxf_dir = temp_str1;
}

void dialog_DXF_shalun::jisuan_canshu()
{
}

void dialog_DXF_shalun::save_canshu()
{
	get_canshu();
	if (is_open)
	{
		auto w_data = wheel_ptr->read_wheel(buff_wheel_pos);

		wheel_ptr->edit_wheel(buff_wheel_pos, canshu.To_wheel_data(w_data));
	}
	else
	{
		wheel_ptr->add_wheel(canshu.To_wheel_data());
	}
}

void dialog_DXF_shalun::input_wheel_pos(int pos)
{
	buff_wheel_pos = pos;
	is_open = 1;
}

void dialog_DXF_shalun::input_wheel_ptr(wheel_dialog* _ptr)
{
	wheel_ptr = _ptr;
}

void dialog_DXF_shalun::OnBnClickedOk()
{
	save_canshu();
	CDialogEx::OnOK();
}
